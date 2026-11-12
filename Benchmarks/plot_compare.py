import argparse
from pathlib import Path

import matplotlib.pyplot as plt
import pandas as pd
from scipy.stats import gmean

from plot import (
    FIGURE_SIZE,
    compute_speedups,
    draw_baseline,
    load_median_times,
    make_benchmark_keys,
    plot_grouped_bars,
    plot_key_table,
    save_figure,
    style_axes,
    use_log_speedup_axis,
)

RUN_COLOURS = ["#2a78d6", "#eb6834"]


def best_speedup_per_benchmark(csv_path):
    speedups = compute_speedups(load_median_times(csv_path))
    return pd.DataFrame({
        "speedup": speedups.max(axis=1),
        "winner": speedups.idxmax(axis=1),
    })


def check_same_benchmarks(first, second, first_name, second_name):
    only_in_first = set(first.index) - set(second.index)
    only_in_second = set(second.index) - set(first.index)
    if only_in_first or only_in_second:
        raise SystemExit(
            f"Benchmarks differ.\n"
            f"  Only in {first_name}: {sorted(only_in_first)}\n"
            f"  Only in {second_name}: {sorted(only_in_second)}"
        )


def build_comparison(first_csv, second_csv, first_name, second_name):
    first = best_speedup_per_benchmark(first_csv)
    second = best_speedup_per_benchmark(second_csv)
    check_same_benchmarks(first, second, first_name, second_name)

    comparison = pd.DataFrame({
        first_name: first.speedup,
        f"{first_name}_winner": first.winner,
        second_name: second.speedup,
        f"{second_name}_winner": second.winner,
    })
    comparison["change"] = comparison[second_name] / comparison[first_name]
    return comparison


def print_summary(comparison, first_name, second_name):
    print(comparison.round(3).to_string())
    print("\nGeometric mean of best speedup vs -O3:")
    for name in (first_name, second_name):
        print(f"  {name}: {gmean(comparison[name]):.3f}")
    print(f"  change ({second_name} / {first_name}): {gmean(comparison['change']):.3f}")


def plot_comparison(comparison, first_name, second_name, keys, filename):
    run_names = [first_name, second_name]
    colours = dict(zip(run_names, RUN_COLOURS))

    speedups_with_mean = comparison[run_names].copy()
    speedups_with_mean.loc["GM"] = [gmean(comparison[name]) for name in run_names]

    figure, axes = plt.subplots(figsize=FIGURE_SIZE)
    plot_grouped_bars(axes, speedups_with_mean, keys + ["GM"],
                      bars_from_one=True, colours=colours)
    axes.axvline(len(keys) - 0.5, color="#bbb", linewidth=0.8)
    draw_baseline(axes)
    use_log_speedup_axis(axes)
    style_axes(axes, "Best-of-3 speedup vs -O3")
    axes.legend(frameon=False, ncol=3, loc="lower left",
                bbox_to_anchor=(0, 1), fontsize=8)
    save_figure(figure, filename)


def parse_arguments():
    parser = argparse.ArgumentParser(
        description="Compare best-of-predictions speedup vs -O3 between two result CSVs.")
    parser.add_argument("first_csv", type=Path)
    parser.add_argument("second_csv", type=Path)
    parser.add_argument("--csv1_name", help="label for the first CSV (default: file name)")
    parser.add_argument("--csv2_name", help="label for the second CSV (default: file name)")
    return parser.parse_args()


def main():
    arguments = parse_arguments()
    first_name = arguments.csv1_name or arguments.first_csv.stem
    second_name = arguments.csv2_name or arguments.second_csv.stem

    comparison = build_comparison(
        arguments.first_csv, arguments.second_csv, first_name, second_name)
    print_summary(comparison, first_name, second_name)

    output_dir = arguments.first_csv.parent / (
        f"{arguments.first_csv.stem}_vs_{arguments.second_csv.stem}")
    output_dir.mkdir(exist_ok=True)

    benchmark_names = list(comparison.index)
    keys = make_benchmark_keys(benchmark_names)
    plot_comparison(comparison, first_name, second_name, keys,
                    output_dir / "comparison.png")
    plot_key_table(keys + ["GM"], benchmark_names + ["Geometric mean"],
                   output_dir / "key.png")
    print(f"\nGraphs saved to {output_dir}/")


if __name__ == "__main__":
    main()