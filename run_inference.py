#!/usr/bin/env python3
"""
Inference step of the PredComp reproduction.

Reads each benchmark program, runs the trained PredComp models on it and writes
the predicted GCC flags to a JSON file. Nothing is run or timed here: the
benchmark step does that, on whichever machine is being measured.

This has to run on an x86 machine, because feature extraction needs programl
and IR2Vec, which have no ARM or RISC-V builds.

Put this file in the repo root (next to main.py) and run it from the same
Python environment that main.py works in:

    python3 run_inference.py                       # cBench
    python3 run_inference.py --suite polybench     # PolyBench/C 4.2.1, LARGE dataset
    python3 run_inference.py --bin_path /opt/gcc-9.2.0/bin --out Benchmarks/flags_gcc9.json
    python3 run_inference.py --programs security_sha telecom_CRC32

The JSON is written in the format Benchmarks/run_benchmarks.py reads, by
default to Benchmarks/predicted_flags.json (cBench) or
Benchmarks/predicted_flags_polybench.json (PolyBench).

The prediction pipeline is the one in main.py: pick the best candidates in each
of the 5 option subspaces, combine them, then rank the combinations.
"""

import argparse
import hashlib
import json
import os
import platform
import shlex
import subprocess
import sys
import time
from dataclasses import dataclass
from datetime import datetime, timezone
from pathlib import Path

REPO = Path(__file__).absolute().parent

SUITES = ("cbench", "polybench")

# cBench: the programs and their hot files are listed in cbench.json, as
# {name: [hot_file, compile_args, link_args]}.
CBENCH_ROOT = REPO / "Dataset" / "cBench_V1.1"
CBENCH_LIST = REPO / "Dataset" / "process" / "cbench.json"

# PolyBench/C 4.2.1: every kernel listed in utilities/benchmark_list. Each one
# is a single .c file built together with utilities/polybench.c.
POLYBENCH_ROOT = REPO / "Dataset" / "PolyBenchC-4.2.1"
POLYBENCH_UTILITIES = POLYBENCH_ROOT / "utilities"
POLYBENCH_DATASETS = ("MINI", "SMALL", "MEDIUM", "LARGE", "EXTRALARGE")
POLYBENCH_DUMP = "polybench_dump.txt"

# Folder that holds each suite's benchmark programs, and default output file.
BENCHMARK_ROOTS = {"cbench": CBENCH_ROOT, "polybench": POLYBENCH_ROOT}
DEFAULT_OUT = {"cbench": "predicted_flags.json", "polybench": "predicted_flags_polybench.json"}


@dataclass
class Program:
    name: str
    dir: str           # program folder, relative to the suite's root folder
    src_dir: Path      # folder holding the hot file
    hot_file: str      # the file the predicted flags are applied to
    compile_args: str  # as the repo's feature extraction takes them: one string
    link_args: str

README = (
    "Input for Benchmarks/run_benchmarks.py. Predicted GCC flags per program, "
    "best first (rank 1 = Top-1). As in PredComp's own harness, the flags apply "
    "to hot_file only: the dependent_files are compiled with dependent_flags. "
    "meta.root is the folder holding the benchmark programs, relative to the "
    "folder this file is in (so fix it if you move this file). Each program "
    "lives in root/<dir>, and hot_file, dependent_files and include_dirs are "
    "relative to that folder; each include_dir is passed to every compile as "
    "-I. compile_args and link_args are the program's normal build arguments. "
    "run says how to run the built program from the hot file's folder: the "
    "binary with args, with stdin, stdout and stderr redirected from/to the "
    "named files (null = not redirected). If loop_count is not null, write it "
    "to the file _finfo_dataset in that folder before running (cBench programs "
    "read their repeat count from there). output_files are the files to "
    "compare between builds to check the program still gives the right "
    "answer. If check_compile_args is present, the output check uses a second "
    "build of each configuration with those extra compile args, run once "
    "(PolyBench: the timed build prints nothing, the check build dumps its "
    "arrays to stderr). run.compare 'numeric' means numbers may differ by one "
    "unit in the last printed digit; otherwise outputs must match exactly."
)


def parse_args():
    parser = argparse.ArgumentParser(
        description="Predict GCC flags for benchmark programs and save them as JSON."
    )
    parser.add_argument("--bin_path", default="/usr/bin",
                        help="folder containing the gcc to extract features with (default: /usr/bin)")
    parser.add_argument("--suite", default="cbench", choices=SUITES,
                        help="benchmark suite (default: cbench)")
    parser.add_argument("--dataset", default="LARGE", choices=POLYBENCH_DATASETS,
                        help="PolyBench dataset size (default: LARGE; ignored for cBench)")
    parser.add_argument("--programs", nargs="+", metavar="NAME",
                        help="only these programs (default: every program in the suite's list)")
    parser.add_argument("--topk", type=int, default=5,
                        help="how many ranked predictions to save per program (default: 5)")
    parser.add_argument("--subspace-topk", type=int, default=3,
                        help="candidates kept per option subspace before combining (default: 3, as in main.py)")
    parser.add_argument("--out",
                        help="output file (default: Benchmarks/predicted_flags.json for cBench, "
                             "Benchmarks/predicted_flags_polybench.json for PolyBench)")
    return parser.parse_args()


def first_line(command, cwd=None):
    """First line a command prints, or None if it could not be run."""
    try:
        result = subprocess.run(command, capture_output=True, text=True, timeout=30, cwd=cwd)
    except (OSError, subprocess.TimeoutExpired):
        return None
    lines = result.stdout.strip().splitlines()
    return lines[0] if result.returncode == 0 and lines else None


def load_evaluator(suite):
    """A function that builds the object which turns one program into model features."""
    from PredComp.Dataset.process.heads import cBench

    if suite == "cbench":
        return lambda program, bin_path: cBench(
            program.name, program.hot_file, program.compile_args, program.link_args, bin_path)

    class PolyBench(cBench):
        """The repo's cBench feature extraction, pointed at a PolyBench kernel.

        cBench.__init__ is not called: it hard-codes the cBench folder and opens
        a timing database, and feature extraction needs neither.
        """

        def __init__(self, program, bin_path):
            self.name, self.file = program.name, program.hot_file
            self.cmp_para, self.ld_para = program.compile_args, program.link_args
            self.bin_path, self.path = bin_path, str(program.src_dir)

        def gen_feature(self):
            # Kernels include <polybench.h>, so the compilers need the utilities
            # folder on their include path. The repo passes programl the compile
            # args as one string, and programl drops a -I given that way, so the
            # path goes in through CPATH, which gcc, clang and programl all read.
            saved = os.environ.get("CPATH")
            os.environ["CPATH"] = os.pathsep.join(filter(None, [str(POLYBENCH_UTILITIES), saved]))
            assembly = Path(self.path) / (Path(self.file).stem + ".s")
            had_assembly = assembly.exists()
            try:
                return super().gen_feature()
            finally:
                if saved is None:
                    del os.environ["CPATH"]
                else:
                    os.environ["CPATH"] = saved
                if not had_assembly:  # left behind by the inline-dump step
                    assembly.unlink(missing_ok=True)

    return PolyBench


def check_feature(feature):
    """Fail here, with a readable reason, rather than deep inside the model."""
    if not feature["inline_feature"]["node"]:
        raise ValueError("empty call graph: the GCC inline dump listed no functions")
    if not feature["loop_feature"]["node"]:
        raise ValueError("empty control-flow graph from programl")
    vector = feature["vec"]
    if vector is None or isinstance(vector, (int, float)) or len(vector) == 0:
        raise ValueError("IR2Vec returned no program vector: check that `clang` on PATH "
                         "is a version IR2Vec can read (clang 16 for IR2Vec 2.1.1)")


def cbench_programs():
    with open(CBENCH_LIST) as f:
        listed = json.load(f)
    return {name: Program(name, name, CBENCH_ROOT / name / "src", hot_file, compile_args, link_args)
            for name, (hot_file, compile_args, link_args) in listed.items()}


def polybench_programs(dataset):
    programs = {}
    for line in (POLYBENCH_UTILITIES / "benchmark_list").read_text().split():
        kernel = Path(line)  # e.g. ./linear-algebra/blas/gemm/gemm.c
        folder = kernel.parent.as_posix()
        # The dataset size is a -D define. programl only reads this string as a
        # single argument, so it must stay one option with no spaces.
        programs[kernel.stem] = Program(kernel.stem, folder, POLYBENCH_ROOT / folder, kernel.name,
                                        f"-D{dataset}_DATASET", "-lm")
    return programs


def other_sources(src_dir, hot_file):
    """The other .c files a cBench program needs, besides the hot file.

    The repo's harness compiles every .c file in the program's folder.
    """
    return sorted(path.name for path in Path(src_dir).glob("*.c") if path.name != hot_file)


def cbench_run_info(src_dir):
    """How to run a cBench program, read from the files cBench ships in its folder.

    This is what cBench's own `./__run 1` does: the command line and loop count
    of dataset 1 come from _ccc_info_datasets, and the files to compare
    afterwards from _ccc_check_output.diff.
    """
    src_dir = Path(src_dir)
    lines = (src_dir / "_ccc_info_datasets").read_text().splitlines()
    start = lines.index("=====")  # first block: dataset number, command line, loop count
    if lines[start + 1].strip() != "1":
        raise ValueError("_ccc_info_datasets does not start with dataset 1")
    command, loop_count = lines[start + 2], int(lines[start + 3])

    run = {"args": [], "stdin": None, "stdout": None, "stderr": None}
    redirects = {"<": "stdin", ">": "stdout", "2>": "stderr"}
    tokens = shlex.split(command)
    while tokens:
        token = tokens.pop(0)
        if token in redirects and tokens:
            run[redirects[token]] = tokens.pop(0)
        elif any(character in token for character in "<>|&;"):
            raise ValueError(f"cannot understand {token!r} in the run command: {command}")
        else:
            run["args"].append(token)
    run["loop_count"] = loop_count

    outputs = []
    check_script = src_dir / "_ccc_check_output.diff"
    if check_script.exists():
        for line in check_script.read_text().splitlines():
            parts = line.split()
            if len(parts) >= 3 and parts[0] == "diff":
                outputs.append(parts[1])
    run["output_files"] = outputs or [name for name in (run["stdout"], run["stderr"]) if name]
    return run


def json_entry(suite, program):
    """Everything the benchmark harness needs to build and run one program, except the flags."""
    program_dir = BENCHMARK_ROOTS[suite] / program.dir

    def in_program_folder(path):
        return Path(os.path.relpath(path, program_dir)).as_posix()

    entry = {"dir": program.dir,
             "hot_file": in_program_folder(program.src_dir / program.hot_file)}
    if suite == "cbench":
        entry.update(
            dependent_files=[in_program_folder(program.src_dir / other)
                             for other in other_sources(program.src_dir, program.hot_file)],
            dependent_flags=["-O3"],
            include_dirs=[],
            compile_args=shlex.split(program.compile_args),
            link_args=shlex.split(program.link_args),
            run=cbench_run_info(program.src_dir),
        )
    else:
        entry.update(
            dependent_files=[in_program_folder(POLYBENCH_UTILITIES / "polybench.c")],
            dependent_flags=["-O3"],
            include_dirs=[in_program_folder(POLYBENCH_UTILITIES)],
            compile_args=["-c", program.compile_args],
            link_args=shlex.split(program.link_args),
            # Dumping the arrays takes as long as many kernels themselves, so
            # it is done by a separate build, used only for the output check.
            check_compile_args=["-DPOLYBENCH_DUMP_ARRAYS"],
            run={"args": [], "stdin": None, "stdout": None, "stderr": POLYBENCH_DUMP,
                 "loop_count": None, "output_files": [POLYBENCH_DUMP], "compare": "numeric"},
        )
    return entry


def to_json(data):
    """json.dumps with indentation, but each list of strings stays on one line.

    Without this every flag gets a line of its own and the file runs to
    thousands of lines, which is hard to read and to diff.
    """
    one_line = {}

    def swap(value):
        if isinstance(value, list) and all(isinstance(item, str) for item in value):
            key = f"@@list{len(one_line)}@@"
            one_line[key] = json.dumps(value)
            return key
        if isinstance(value, list):
            return [swap(item) for item in value]
        if isinstance(value, dict):
            return {name: swap(item) for name, item in value.items()}
        return value

    text = json.dumps(swap(data), indent=2)
    for key, compact in one_line.items():
        text = text.replace(f'"{key}"', compact)
    return text


def main():
    args = parse_args()

    # --- Checks that are cheap to do before loading the models ---------------
    gcc = Path(args.bin_path) / "gcc"
    gcc_version = first_line([str(gcc), "--version"])
    if gcc_version is None:
        sys.exit(f"error: cannot run {gcc} (check --bin_path)")
    clang_version = first_line(["clang", "--version"])
    if clang_version is None:
        sys.exit("error: `clang` is not on PATH; it is needed to turn each program into LLVM IR")

    if args.suite == "polybench":
        if not (POLYBENCH_UTILITIES / "polybench.c").is_file():
            sys.exit(f"error: PolyBench not found at {POLYBENCH_ROOT}")
        programs = polybench_programs(args.dataset)
    else:
        programs = cbench_programs()
    if args.programs:
        unknown = [name for name in args.programs if name not in programs]
        if unknown:
            sys.exit(f"error: no {args.suite} program called: {', '.join(unknown)}\n"
                     f"available: {', '.join(programs)}")
        programs = {name: programs[name] for name in args.programs}

    if args.subspace_topk < 1 or args.topk < 1:
        sys.exit("error: --topk and --subspace-topk must be at least 1")
    combinations = args.subspace_topk ** 5
    if args.topk > combinations:
        sys.exit(f"error: --topk {args.topk} is more than the {combinations} combinations "
                 f"that --subspace-topk {args.subspace_topk} produces")

    # --- Import the repo's own code ------------------------------------------
    # The repo imports itself as the package "PredComp" (and so do the saved
    # models), so its parent folder has to be importable too.
    sys.path[:0] = [str(REPO), str(REPO.parent)]
    try:
        make_evaluator = load_evaluator(args.suite)
        from Inference.predict import pred_result_seq
        from util.seq import gen_comb_seq, gen_global_seq, op as option_groups
    except ModuleNotFoundError as error:
        if error.name == "PredComp":
            sys.exit('error: cannot import "PredComp". This script must sit in the repo root, '
                     'and the repo folder must be named "PredComp" (see CHANGES.md).')
        sys.exit(f"error: Python package {error.name!r} is missing. "
                 "Run this in the environment that main.py works in.")

    start = time.time()

    # --- Stage 0: turn each program into features ----------------------------
    features, failed, entries = {}, {}, {}
    for name, program in programs.items():
        print(f"[features] {name} ({program.hot_file})", flush=True)
        try:
            entry = json_entry(args.suite, program)
            feature = make_evaluator(program, args.bin_path).gen_feature()
            check_feature(feature)
        except Exception as error:  # one bad program should not stop the rest
            failed[name] = f"{type(error).__name__}: {error}"
            print(f"  FAILED: {failed[name]}", file=sys.stderr, flush=True)
            continue
        features[name] = feature
        entries[name] = entry
    if not features:
        sys.exit("error: feature extraction failed for every program, nothing to predict")

    # --- Stages 1-3: predict, exactly as main.py does ------------------------
    print(f"[predict] {len(features)} programs", flush=True)
    try:
        subspace = {group: pred_result_seq(features, group, topk=args.subspace_topk)
                    for group in ("1", "2", "3", "4", "5")}
    except RuntimeError as error:
        sys.exit(f"error: subspace prediction failed ({error}). "
                 "Is --subspace-topk larger than the candidate list in label_v1.json?")
    candidates = gen_comb_seq(subspace)
    ranked = pred_result_seq(features, "comb", topk=args.topk, comb_seq=candidates)
    flags = gen_global_seq(ranked)  # {program: ["-O3 -finline -fno-...", ...]}, best first

    elapsed = time.time() - start

    # --- Write the JSON -------------------------------------------------------
    # Paths are written the way Benchmarks/run_benchmarks.py reads them:
    # meta.root is relative to the JSON file's folder, each program is in
    # root/<dir>, and its files are relative to that program folder.
    if args.out:
        out_path = Path(args.out)
    elif (REPO / "Benchmarks").is_dir():
        out_path = REPO / "Benchmarks" / DEFAULT_OUT[args.suite]
    else:
        out_path = Path(DEFAULT_OUT[args.suite])
    benchmark_root = os.path.realpath(BENCHMARK_ROOTS[args.suite])

    predictions = {}
    for name in features:
        predictions[name] = dict(entries[name], predictions=[
            {"rank": rank, "flags": sequence.split()}
            for rank, sequence in enumerate(flags[name], start=1)])
    # Fingerprint of the predicted flags only, so two people can check they got
    # the same predictions by comparing one line.
    fingerprint = hashlib.sha256(json.dumps(
        {name: [p["flags"] for p in entry["predictions"]] for name, entry in predictions.items()},
        sort_keys=True).encode()).hexdigest()

    import torch
    output = {
        "_readme": README,
        "meta": {
            "created_utc": datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ"),
            "suite": args.suite,
            **({"dataset": args.dataset} if args.suite == "polybench" else {}),
            "root": Path(os.path.relpath(
                benchmark_root, os.path.realpath(out_path.absolute().parent))).as_posix(),
            "gcc_path": str(gcc),
            "gcc_version": gcc_version,
            "clang_version": clang_version,
            "python_version": platform.python_version(),
            "torch_version": torch.__version__,
            "machine": platform.machine(),
            "repo_commit": first_line(["git", "rev-parse", "--short", "HEAD"], cwd=REPO),
            "topk": args.topk,
            "subspace_topk": args.subspace_topk,
            "inference_seconds": round(elapsed, 1),
            "predictions_sha256": fingerprint,
        },
        # The 88 options by subspace, for analysing which group did the work.
        "option_groups": {group: list(options) for group, options in option_groups.items()
                          if group != "comb"},
        "failed": failed,
        "programs": predictions,
    }
    with open(out_path, "w") as f:
        f.write(to_json(output) + "\n")

    print(f"\nWrote {out_path}: {len(predictions)} programs, top {args.topk} each, "
          f"{elapsed:.1f} s")
    print(f"Predictions fingerprint: {fingerprint[:16]}")
    if failed:
        print(f"FAILED ({len(failed)}): {', '.join(failed)}", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
