import hashlib
import itertools
import math
import os
import shutil
import subprocess
import time
from pathlib import Path
import json
import platform
from datetime import datetime
import csv
import argparse

BASELINES = {"O0": ["-O0"], "O3": ["-O3"]}
# Outputs are checked against the -O3 build, not -O0: -O0 never fuses
# multiply-adds, which ARM and RISC-V builds do from -O1 up, so floating-point
# results can differ from every optimised build in the last bits.
REFERENCE = "O3"
OUT_DIR = Path("build")
FIELDS = [
        #"timestamp", "host", 
        "arch", "compiler", "suite", "benchmark",
        "config", "run", "time_s", "status", 
        #"hash"
        ]
LOG_DIR = Path("logs")
CC = os.environ.get("CC", "gcc")
USE_TEMP = False


def run_subprocess(cmd, timeout=120):
    try:
        r = subprocess.run(cmd, capture_output=True, text=True, timeout=timeout)
        return r.returncode == 0, r.stderr
    except subprocess.TimeoutExpired:
        return False, "timeout"

    
def same_output(reference, output, compare="exact"):
    """True if an output file matches the reference build's.

    compare="numeric" (PolyBench) lets a printed number differ by one unit in
    its last digit, or by one part in a million, which is as far as a fused
    multiply-add or different rounding moves it. Anything else must match.
    """
    if compare != "numeric":
        return reference.read_bytes() == output.read_bytes()
    with open(reference) as ref, open(output) as out:
        for ref_line, out_line in itertools.zip_longest(ref, out):
            if ref_line == out_line:
                continue
            if ref_line is None or out_line is None:
                return False
            ref_tokens, out_tokens = ref_line.split(), out_line.split()
            if len(ref_tokens) != len(out_tokens):
                return False
            for a, b in zip(ref_tokens, out_tokens):
                if a == b:
                    continue
                if "." not in a:          # integers and labels must match exactly
                    return False
                try:
                    x, y = float(a), float(b)
                except ValueError:
                    return False
                last_digit = 10.0 ** -len(a.partition(".")[2])  # 0.01 for "%0.2lf"
                if not math.isclose(x, y, rel_tol=1e-6, abs_tol=last_digit * 1.001):
                    return False
    return True


def cpu_temp():
    """Return CPU temp in °C, or None if unavailable."""
    p = Path("/sys/class/thermal/thermal_zone0/temp")
    try:
        return int(p.read_text()) / 1000   # value is in millidegrees
    except (OSError, ValueError):
        return None


class ProgramInstance:

    def __init__(
        self, suite, name, hot_file, flag_predictions, root,
        num_choices=3,
        dependent_files=None,
        dependent_flags=None,
        compile_args=None,
        link_args=None,
        dir=None,
        include_dirs=None,
        check_compile_args=None,
    ):
        self.suite = suite
        self.name = name
        self.hot_file = hot_file
        self.flag_predictions = [
            p["flags"] for p in sorted(flag_predictions, key=lambda p: p["rank"])
        ]
        self.num_choices = min(num_choices, len(self.flag_predictions))

        self.dependent_files = dependent_files or []
        self.dependent_flags = dependent_flags or ["-O3"]
        self.compile_args = compile_args or ["-c"]
        self.link_args = link_args or ["-lm"]
        # Program folder: root/<dir>, or root/<name> if the JSON gives no dir
        # (PolyBench kernels sit in nested folders such as linear-algebra/blas/gemm).
        self.prog_dir = Path(root) / (dir or self.name)
        self.src = self.prog_dir / self.hot_file
        # include_dirs are relative to the program folder; gcc gets them as absolute -I paths.
        self.include_args = [f"-I{(self.prog_dir / d).resolve()}" for d in include_dirs or []]
        # Extra compile args for a second build used only for the output check.
        self.check_compile_args = check_compile_args or []

        self.args = None
        self.stdin = None
        self.stdout = None
        self.stderr = None
        self.compare = "exact"
        self.loop_count = None
        self.output_files = []
        self.cwd = self.src.parent

        self.configs = dict(BASELINES)
        for i in range(self.num_choices):
            self.configs[f"pred{i + 1}"] = self.flag_predictions[i]

        self.exes = {}                                   
        self.check_exes = {}
        self.check_status = {}
        self.results = {cfg: [] for cfg in self.configs}


    def get_flags(self, config):
        if config not in self.configs:
            raise ValueError(f"Unknown config: {config}")
        return self.configs[config]


    def set_run_args(self, args, stdin=None, loop_count=None, output_files=None, cwd=None, stdout=None,
                     stderr=None, compare=None):
        self.args = args
        self.stdin = stdin
        self.loop_count = loop_count
        self.output_files = output_files or []
        if cwd is not None:
            self.cwd = Path(cwd)
        self.stdout = stdout
        self.stderr = stderr
        self.compare = compare or "exact"


    def compile_benchmark(self, config, flags, extra_args=(), variant=""):
        out_dir = OUT_DIR / CC / f"{config}{variant}" / self.name
        out_dir.mkdir(parents=True, exist_ok=True)
        exe = out_dir / self.name
        for f in out_dir.glob("*.o"):          
            f.unlink()
        exe.unlink(missing_ok=True)

        dep_flags = flags if config in BASELINES else self.dependent_flags

        jobs = [(self.src, flags)] + [(self.prog_dir / d, dep_flags) for d in self.dependent_files]
        objs = []
        for src, f in jobs:
            obj = out_dir / (Path(src).stem + ".o")   
            ok, err = run_subprocess([CC, *f, *self.compile_args, *extra_args, *self.include_args,
                                      str(src), "-o", str(obj)])
            if not ok:
                return None, "compile_error", f"{src}:\n{err}"
            objs.append(str(obj))

        ok, err = run_subprocess([CC, *flags, *objs, "-o", str(exe), *self.link_args])
        if not ok:
            return None, "link_error", err
        return exe, "ok", ""


    def build_all(self):
        statuses = {}
        for config in self.configs:
            exe, status, err = self.compile_benchmark(config, self.get_flags(config))
            statuses[config] = status
            print(f"{self.name:20} {config:6} {status}")
            if exe is not None:
                self.exes[config] = exe
            if err:
                LOG_DIR.mkdir(exist_ok=True)
                (LOG_DIR / f"{CC}_{config}_{self.name}.log").write_text(err)
            if self.check_compile_args and exe is not None:
                check_exe, check_status, err = self.compile_benchmark(
                    config, self.get_flags(config), self.check_compile_args, "_check")
                if check_exe is not None:
                    self.check_exes[config] = check_exe
                else:
                    print(f"{self.name:20} {config:6} check build: {check_status}")
                    LOG_DIR.mkdir(exist_ok=True)
                    (LOG_DIR / f"{CC}_{config}_check_{self.name}.log").write_text(err)
        return statuses

    def wait_cool(self, limit=60, max_wait=120):
        if USE_TEMP == False:
            return
        t0 = time.time()
        temp = cpu_temp()
        if temp is not None and temp > limit:
            print(f"Cooling off: temperature is {temp}!")
        while temp is not None and temp > limit:
            if time.time() - t0 > max_wait:
                print("Done cooling!")
                break       
            time.sleep(2)
            temp = cpu_temp()


    def run_program(self, exe, args, stdin, timeout=600):
        self.wait_cool(60, 10)
        if self.loop_count is not None:
            (self.cwd / "_finfo_dataset").write_text(f"{self.loop_count}\n")

        for f in self.output_files:
            (self.cwd / f).unlink(missing_ok=True)

        stdin_f = open(self.cwd / stdin) if stdin else subprocess.DEVNULL
        t0 = time.perf_counter()
        try:
            p = subprocess.run([str(exe.resolve()), *(args or [])], cwd=self.cwd,
                            stdin=stdin_f, capture_output=True, timeout=timeout)
        except subprocess.TimeoutExpired:
            return None, "run_timeout", None
        finally:
            if stdin_f is not subprocess.DEVNULL:
                stdin_f.close()
        elapsed = time.perf_counter() - t0

        if self.stdout:
            (self.cwd / self.stdout).write_bytes(p.stdout)
        if self.stderr:
            (self.cwd / self.stderr).write_bytes(p.stderr)

        if p.returncode != 0:
            return elapsed, "runtime_error", None

        h = hashlib.sha256()
        for f in self.output_files:
            path = self.cwd / f
            if not path.exists():
                return elapsed, "missing_output", None
            h.update(path.read_bytes())
        return elapsed, "ok", h.hexdigest()


    def check_outputs(self):
        """Run each check build once and compare its output with the reference build's.

        Only used when the JSON gives check_compile_args (PolyBench), so the
        timed builds don't spend time printing their results.
        """
        if not self.check_exes:
            return
        order = [REFERENCE] + [c for c in self.check_exes if c != REFERENCE]
        for config in order:
            exe = self.check_exes.get(config)
            if exe is None:
                continue
            _, status, _ = self.run_program(exe, self.args, self.stdin)
            if status == "ok":
                if config == REFERENCE:
                    for f in self.output_files:
                        shutil.copyfile(self.cwd / f, self.cwd / f"{f}.ref")
                elif self.check_status.get(REFERENCE) == "ok" and not all(
                        same_output(self.cwd / f"{f}.ref", self.cwd / f, self.compare)
                        for f in self.output_files):
                    status = "incorrect_output"
            self.check_status[config] = status
            print(f"{self.name:20} {config:6} output check: {status}")
        for f in self.output_files:
            (self.cwd / f"{f}.ref").unlink(missing_ok=True)


    def check_validity(self):
        if self.check_exes:                    # outputs were checked by check_outputs()
            if self.check_status.get(REFERENCE) != "ok":
                print(f"{self.name}: {REFERENCE} check build failed, outputs not checked")
                return False
            for config, runs in self.results.items():
                status = self.check_status.get(config, "check_failed")
                if status != "ok":
                    self.results[config] = [(t, status if s == "ok" else s, h) for t, s, h in runs]
            return True

        ref_runs = self.results.get(REFERENCE, [])
        if not ref_runs or ref_runs[0][1] != "ok":
            return False                       # no trustworthy reference

        correct = ref_runs[0][2]
        for config in self.configs:
            runs = self.results[config]
            for i, (t, status, h) in enumerate(runs):
                if status == "ok" and h != correct:
                    runs[i] = (t, "incorrect_output", h)
        return True


    def measure_benchmark(self, count, args=None, stdin=None):
        if args is None:
            args = self.args
        if stdin is None:
            stdin = self.stdin

        #warm up
        for config in self.configs:
            exe = self.exes.get(config)
            if exe is None:
                continue                            
            self.run_program(exe, args, stdin)

        for _ in range(count):
            for config in self.configs:
                exe = self.exes.get(config)
                if exe is None:
                    continue                            
                self.results[config].append(self.run_program(exe, args, stdin))

        self.check_validity()

    def write_results(self, csv_path):
        csv_path = Path(csv_path)
        csv_path.parent.mkdir(parents=True, exist_ok=True)
        new = not csv_path.exists()
        now = datetime.now().isoformat(timespec="seconds")

        with open(csv_path, "a", newline="") as f:
            w = csv.DictWriter(f, fieldnames=FIELDS)
            if new:
                w.writeheader()
            for config, runs in self.results.items():
                for run, (t, status, h) in enumerate(runs):
                    w.writerow({
                        #"timestamp": now,
                        #"host": platform.node(),
                        "arch": platform.machine(),
                        "compiler": CC,
                        "suite": self.suite,
                        "benchmark": self.name,
                        "config": config,
                        "run": run,
                        "time_s": t,
                        "status": status
                        #"hash": h,
                    })

def load_programs(json_path, num_choices=3, root=None):
    json_path = Path(json_path)
    data = json.loads(json_path.read_text())
    meta = data["meta"]

    if root is None:
        root = (json_path.parent / meta.get("root", ".")).resolve()

    programs = []
    for name, p in data["programs"].items():
        prog = ProgramInstance(
            suite=meta["suite"],
            name=name,
            hot_file=p["hot_file"],
            flag_predictions=p["predictions"],
            root=root,
            num_choices=num_choices,
            dependent_files=p.get("dependent_files"),
            dependent_flags=p.get("dependent_flags"),
            compile_args=p.get("compile_args"),
            link_args=p.get("link_args"),
            dir=p.get("dir"),
            include_dirs=p.get("include_dirs"),
            check_compile_args=p.get("check_compile_args"),
        )
        run = p.get("run", {})
        prog.set_run_args(
            args=run.get("args", []),
            stdin=run.get("stdin"),
            loop_count=run.get("loop_count"),
            output_files=run.get("output_files"),
            cwd=run.get("cwd"),
            stdout=run.get("stdout"),
            stderr=run.get("stderr"),
            compare=run.get("compare"),
        )
        programs.append(prog)

    for name, reason in data.get("failed", {}).items():
        print(f"skipping {name}: {reason}")

    return programs


parser = argparse.ArgumentParser()
parser.add_argument("--core", type=int, default=None, help="pin to this CPU core")
parser.add_argument("--temp", action="store_true", help="use temperature control")
parser.add_argument("--json", default="predicted_flags.json",
                    help="predictions file from run_inference.py (default: predicted_flags.json)")
parser.add_argument("--no-o0", action="store_true",
                    help="skip the -O0 build (the output check uses -O3)")
args = parser.parse_args()

if args.no_o0:
    del BASELINES["O0"]

path = Path(args.json)
programs = load_programs(path)
print(programs[0].src, programs[0].src.exists())
stamp = datetime.now().strftime("%Y%m%d_%H%M%S")

if args.core is not None:
    if hasattr(os, "sched_setaffinity"):     # Linux only
        os.sched_setaffinity(0, {args.core})
        print(f"pinned to core {args.core}")
    else:
        print("warning: pinning not supported on this OS, continuing unpinned")

if args.temp:
    USE_TEMP = True
    print("Max temperature is 60")

for program in programs:
    program.build_all()
    program.check_outputs()
    program.measure_benchmark(5)
    program.write_results(Path("results") / f"{platform.machine()}_{CC}_{stamp}.csv" )
