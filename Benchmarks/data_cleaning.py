import csv
import math
import sys
from collections import defaultdict
from statistics import median

FILES = [
    "results/x86_64_gcc_20261125_174052.csv",
    "results/x86_64_gcc_20261118_161037.csv",
    "results/aarch64_gcc_20261111_222204.csv",
    "results/aarch64_gcc_20261118_223601.csv",
]
ARCHS = ("x86_64", "aarch64")
TOP_K = ("pred1", "pred2", "pred3")  # best-of-top-k, as in the paper
OUT = "cleaned_data.csv"
REFERENCE = "reference.tsv"  # name<TAB>speedup, in the order to output

# cBench rows are named program$hot_file (hot_file from the predictions JSON)
HOT_FILES = {
    "automotive_bitcount": "bitcnts.c",
    "telecom_gsm": "short_term.c",
    "network_dijkstra": "dijkstra_large.c",
    "security_sha": "sha.c",
    "security_blowfish_d": "bf_enc.c",
    "security_blowfish_e": "bf_enc.c",
    "consumer_jpeg_c": "jcphuff.c",
    "automotive_susan_s": "susan.c",
    "network_patricia": "patricia.c",
    "telecom_CRC32": "crc_32.c",
}


def load_reference(path):
    with open(path) as f:
        return dict(line.split() for line in f if line.strip())


def name_for(bench, suite):
    return f"{bench}${HOT_FILES[bench]}" if suite == "cbench" else bench


def load(paths):
    """times[benchmark][arch][config] -> list of run times; also returns non-ok runs."""
    times = defaultdict(lambda: defaultdict(lambda: defaultdict(list)))
    bad = defaultdict(set)
    suites = {}
    for path in paths:
        with open(path, newline="") as f:
            for row in csv.DictReader(f):
                bench, arch, cfg = row["benchmark"], row["arch"], row["config"]
                suites[bench] = row["suite"]
                times[bench][arch][cfg].append(float(row["time_s"]))
                if row["status"] != "ok":
                    bad[bench].add(f"{arch}:{cfg}:{row['status']}")
    return times, bad, suites


def summarise(name, runs, bad, ref):
    t = {arch: {cfg: median(v) for cfg, v in runs[arch].items()} for arch in ARCHS}
    row = {"program": name, "reference": float(ref[name]) if name in ref else ""}
    for arch in ARCHS:
        row[f"{arch}_O0/O3"] = t[arch]["O0"] / t[arch]["O3"]
    for arch in ARCHS:
        row[f"{arch}_O3/top3"] = max(t[arch]["O3"] / t[arch][k] for k in TOP_K)
    for arch in ARCHS:
        # <1: below the paper's top-3 speedup
        row[f"{arch}_top3/reference"] = row[f"{arch}_O3/top3"] / row["reference"] if row["reference"] else ""
    for arch in ARCHS:
        row[f"{arch}_best"] = min(TOP_K, key=lambda k: t[arch][k])
    # >1: top-3 helps more on x86_64 than on aarch64
    row["x86_64/aarch64_top3_gain"] = row["x86_64_O3/top3"] / row["aarch64_O3/top3"]
    row["issues"] = ";".join(sorted(bad))
    return row


def geomean_row(rows):
    """Geometric mean of each numeric column, skipping blanks."""
    out = {k: "" for k in rows[0]}
    out["program"] = "geomean"
    for k in rows[0]:
        vals = [r[k] for r in rows if isinstance(r[k], float)]
        if vals:
            out[k] = math.exp(sum(map(math.log, vals)) / len(vals))
    return out


def main(paths):
    times, bad, suites = load(paths)
    ref = load_reference(REFERENCE)
    rows = [
        summarise(name_for(b, suites[b]), runs, bad[b], ref)
        for b, runs in times.items()
        if all(arch in runs for arch in ARCHS)
    ]
    # Same order as the reference; anything not in it goes last
    order = {name: i for i, name in enumerate(ref)}
    rows.sort(key=lambda r: order.get(r["program"], len(order)))

    rows.append(geomean_row(rows))

    with open(OUT, "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=rows[0].keys())
        w.writeheader()
        for r in rows:
            w.writerow({k: round(v, 3) if isinstance(v, float) else v for k, v in r.items()})


if __name__ == "__main__":
    main(sys.argv[1:] or FILES)