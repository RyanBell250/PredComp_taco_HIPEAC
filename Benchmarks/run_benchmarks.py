import hashlib
import os
import subprocess
import time
from pathlib import Path
import json
import platform
from datetime import datetime
import csv

BASELINES = {"O0": ["-O0"], "O3": ["-O3"]}
OUT_DIR = Path("build")
FIELDS = ["timestamp", "host", "arch", "compiler", "suite", "benchmark",
          "config", "run", "time_s", "status", "hash"]
LOG_DIR = Path("logs")
CC = "gcc"


def run_subprocess(cmd, timeout=120):
    try:
        r = subprocess.run(cmd, capture_output=True, text=True, timeout=timeout)
        return r.returncode == 0, r.stderr
    except subprocess.TimeoutExpired:
        return False, "timeout"


class ProgramInstance:

    def __init__(
        self, suite, name, hot_file, flag_predictions, root,
        num_choices=3,
        dependent_files=None,
        dependent_flags=None,
        compile_args=None,
        link_args=None,
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
        self.prog_dir = Path(root) / self.name
        self.src = self.prog_dir / self.hot_file

        self.args = None
        self.stdin = None
        self.stdout = None
        self.loop_count = None
        self.output_files = []
        self.cwd = self.src.parent

        self.configs = dict(BASELINES)
        for i in range(self.num_choices):
            self.configs[f"pred{i + 1}"] = self.flag_predictions[i]

        self.exes = {}                                   
        self.results = {cfg: [] for cfg in self.configs}


    def get_flags(self, config):
        if config not in self.configs:
            raise ValueError(f"Unknown config: {config}")
        return self.configs[config]


    def set_run_args(self, args, stdin=None, loop_count=None, output_files=None, cwd=None, stdout=None):
        self.args = args
        self.stdin = stdin
        self.loop_count = loop_count
        self.output_files = output_files or []
        if cwd is not None:
            self.cwd = Path(cwd)
        self.stdout = stdout


    def compile_benchmark(self, config, flags):
        out_dir = OUT_DIR / CC / config / self.name
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
            ok, err = run_subprocess([CC, *f, *self.compile_args, str(src), "-o", str(obj)])
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
        return statuses


    def run_program(self, exe, args, stdin, timeout=600):
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

        if p.returncode != 0:
            return elapsed, "runtime_error", None

        h = hashlib.sha256()
        for f in self.output_files:
            path = self.cwd / f
            if not path.exists():
                return elapsed, "missing_output", None
            h.update(path.read_bytes())
        return elapsed, "ok", h.hexdigest()


    def check_validity(self):
        ref_runs = self.results.get("O0", [])
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
                        "status": status,
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
        )
        run = p.get("run", {})
        prog.set_run_args(
            args=run.get("args", []),
            stdin=run.get("stdin"),
            loop_count=run.get("loop_count"),
            output_files=run.get("output_files"),
            cwd=run.get("cwd"),
            stdout=run.get("stdout"),
        )
        programs.append(prog)

    for name, reason in data.get("failed", {}).items():
        print(f"skipping {name}: {reason}")

    return programs


path = Path("test.json")
programs = load_programs(path)
print(programs[0].src, programs[0].src.exists())
stamp = datetime.now().strftime("%Y%m%d_%H%M%S")

for program in programs:
    program.build_all()
    program.measure_benchmark(5)
    program.write_results(Path("results") / f"{platform.machine()}_{CC}_{stamp}.csv" )
