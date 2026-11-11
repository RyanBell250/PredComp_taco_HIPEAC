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

    python3 run_inference.py --bin_path /usr/bin
    python3 run_inference.py --bin_path /opt/gcc-9.2.0/bin --out Benchmarks/flags_gcc9.json
    python3 run_inference.py --programs security_sha telecom_CRC32

The JSON is written in the format Benchmarks/run_benchmarks.py reads, by
default to Benchmarks/predicted_flags.json.

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
from datetime import datetime, timezone
from pathlib import Path

REPO = Path(__file__).absolute().parent

# Program lists per benchmark suite: {name: [hot_file, compile_args, link_args]}.
# To add PolyBench, add its list here and its evaluator class in load_evaluator().
PROGRAM_LISTS = {
    "cbench": REPO / "Dataset" / "process" / "cbench.json",
}

# Folder that holds each suite's benchmark programs.
BENCHMARK_ROOTS = {
    "cbench": REPO / "Dataset" / "cBench_V1.1",
}

README = (
    "Input for Benchmarks/run_benchmarks.py. Predicted GCC flags per program, "
    "best first (rank 1 = Top-1). As in PredComp's own harness, the flags apply "
    "to hot_file only: the dependent_files are compiled with dependent_flags. "
    "meta.root is the folder holding the benchmark programs, relative to the "
    "folder this file is in (so fix it if you move this file). Each program "
    "lives in root/<program name>, and hot_file and dependent_files are "
    "relative to that. compile_args and link_args are the program's normal "
    "build arguments. run says how to run the built program from the hot "
    "file's folder: the binary with args, with stdin, stdout and stderr "
    "redirected from/to the named files (null = not redirected). If loop_count "
    "is not null, write it to the file _finfo_dataset in that folder before "
    "running (cBench programs read their repeat count from there). "
    "output_files are the files to compare between builds to check the "
    "program still gives the right answer."
)


def parse_args():
    parser = argparse.ArgumentParser(
        description="Predict GCC flags for benchmark programs and save them as JSON."
    )
    parser.add_argument("--bin_path", default="/usr/bin",
                        help="folder containing the gcc to extract features with (default: /usr/bin)")
    parser.add_argument("--suite", default="cbench", choices=sorted(PROGRAM_LISTS),
                        help="benchmark suite (default: cbench)")
    parser.add_argument("--programs", nargs="+", metavar="NAME",
                        help="only these programs (default: every program in the suite's list)")
    parser.add_argument("--topk", type=int, default=5,
                        help="how many ranked predictions to save per program (default: 5)")
    parser.add_argument("--subspace-topk", type=int, default=3,
                        help="candidates kept per option subspace before combining (default: 3, as in main.py)")
    parser.add_argument("--out",
                        help="output file (default: Benchmarks/predicted_flags.json, "
                             "next to the benchmark harness)")
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
    """The class that knows how to turn one program of this suite into model features."""
    if suite == "cbench":
        from PredComp.Dataset.process.heads import cBench
        return cBench
    raise ValueError(f"no evaluator for suite {suite!r}")


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


def other_sources(src_dir, hot_file):
    """The other .c files needed to build the program, besides the hot file.

    For cBench the repo's harness compiles every .c file in the program's
    folder, so that is the list. PolyBench will need its own rule here
    (each kernel also needs utilities/polybench.c).
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


# How to run a program of each suite. PolyBench will need its own function here.
RUN_INFO = {
    "cbench": cbench_run_info,
}


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

    with open(PROGRAM_LISTS[args.suite]) as f:
        programs = json.load(f)
    if args.programs:
        unknown = [name for name in args.programs if name not in programs]
        if unknown:
            sys.exit(f"error: not in {PROGRAM_LISTS[args.suite].name}: {', '.join(unknown)}\n"
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
        Evaluator = load_evaluator(args.suite)
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
    features, failed, source_dirs, run_info = {}, {}, {}, {}
    for name, (hot_file, compile_args, link_args) in programs.items():
        print(f"[features] {name} ({hot_file})", flush=True)
        try:
            evaluator = Evaluator(name, hot_file, compile_args, link_args, args.bin_path)
            src_dir = os.path.realpath(evaluator.path)
            run = RUN_INFO[args.suite](src_dir)
            feature = evaluator.gen_feature()
            check_feature(feature)
        except Exception as error:  # one bad program should not stop the rest
            failed[name] = f"{type(error).__name__}: {error}"
            print(f"  FAILED: {failed[name]}", file=sys.stderr, flush=True)
            continue
        features[name] = feature
        source_dirs[name] = src_dir
        run_info[name] = run
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
    # root/<name>, and its source files are relative to that program folder.
    if args.out:
        out_path = Path(args.out)
    elif (REPO / "Benchmarks").is_dir():
        out_path = REPO / "Benchmarks" / "predicted_flags.json"
    else:
        out_path = Path("predicted_flags.json")
    benchmark_root = os.path.realpath(BENCHMARK_ROOTS[args.suite])

    def in_program_folder(name, src_dir, file_name):
        program_dir = os.path.join(benchmark_root, name)
        return Path(os.path.relpath(os.path.join(src_dir, file_name), program_dir)).as_posix()

    predictions = {}
    for name in features:
        hot_file, compile_args, link_args = programs[name]
        src_dir = source_dirs[name]
        predictions[name] = {
            "hot_file": in_program_folder(name, src_dir, hot_file),
            "dependent_files": [in_program_folder(name, src_dir, other)
                                for other in other_sources(src_dir, hot_file)],
            "dependent_flags": ["-O3"],
            "compile_args": shlex.split(compile_args),
            "link_args": shlex.split(link_args),
            "run": run_info[name],
            "predictions": [{"rank": rank, "flags": sequence.split()}
                            for rank, sequence in enumerate(flags[name], start=1)],
        }
    # Fingerprint of the predictions only, so two people can check they got the
    # same result by comparing one line.
    fingerprint = hashlib.sha256(json.dumps(predictions, sort_keys=True).encode()).hexdigest()

    import torch
    output = {
        "_readme": README,
        "meta": {
            "created_utc": datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ"),
            "suite": args.suite,
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
