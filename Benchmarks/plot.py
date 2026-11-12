import argparse
from pathlib import Path
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter, LogLocator, NullLocator

BASELINE = "O3"
PREDICTIONS = ["pred1", "pred2", "pred3"]
CONFIG_COLOURS = {
    "O3": "#8a8a8a",
    "pred1": "#2a78d6",
    "pred2": "#eb6834",
    "pred3": "#1baf7a",
}
FIGURE_SIZE = (7, 3.6)
DPI = 200


def load_median_times(csv_path):
    results = pd.read_csv(csv_path)
    successful_runs = results[results.status == "ok"]
    return successful_runs.groupby(["benchmark", "config"]).time_s.median().unstack()


def compute_speedups(median_times):
    return pd.DataFrame({
        prediction: median_times[BASELINE] / median_times[prediction]
        for prediction in PREDICTIONS
    })


def make_benchmark_keys(benchmark_names):
    return [f"B{number}" for number in range(1, len(benchmark_names) + 1)]


def style_axes(axes, y_label):
    axes.set_ylabel(y_label)
    axes.spines["top"].set_visible(False)
    axes.spines["right"].set_visible(False)
    axes.grid(axis="y", color="#eee")
    axes.set_axisbelow(True)


def draw_baseline(axes):
    axes.axhline(1, color="#333", linewidth=1.2, linestyle="--", label=f"-{BASELINE}")


def use_log_speedup_axis(axes):
    axes.set_yscale("log")
    tick_locator = LogLocator(base=10, subs=[1, 1.25, 1.5, 2, 2.5, 3, 4, 5, 6, 7, 8, 9])
    tick_formatter = FuncFormatter(lambda value, _: f"{value:g}×")
    axes.yaxis.set_major_locator(tick_locator)
    axes.yaxis.set_major_formatter(tick_formatter)
    axes.yaxis.set_minor_locator(NullLocator())


def save_figure(figure, filename):
    figure.tight_layout()
    figure.savefig(filename, dpi=DPI, bbox_inches="tight")
    plt.close(figure)


def plot_grouped_bars(axes, values_by_config, keys, bars_from_one=False,
                      colours=CONFIG_COLOURS):
    positions = np.arange(len(keys))
    group_count = len(values_by_config.columns)
    bar_width = 0.8 / group_count
    centre_offset = (group_count - 1) / 2

    for index, config in enumerate(values_by_config.columns):
        offset = (index - centre_offset) * bar_width
        values = values_by_config[config]
        heights = values - 1 if bars_from_one else values
        bottom = 1 if bars_from_one else 0
        axes.bar(positions + offset, heights, bar_width * 0.92, bottom=bottom,
                 color=colours[config], label=config)

    axes.set_xticks(positions, keys)


def plot_speedup_per_prediction(speedups, keys, filename):
    figure, axes = plt.subplots(figsize=FIGURE_SIZE)
    plot_grouped_bars(axes, speedups, keys, bars_from_one=True)
    draw_baseline(axes)
    use_log_speedup_axis(axes)
    style_axes(axes, f"Speedup vs -{BASELINE}")
    axes.legend(frameon=False, ncol=4, loc="upper left", fontsize=8)
    save_figure(figure, filename)


def plot_raw_times(median_times, keys, filename):
    figure, axes = plt.subplots(figsize=FIGURE_SIZE)
    plot_grouped_bars(axes, median_times[[BASELINE] + PREDICTIONS], keys)
    style_axes(axes, "Median time (s)")
    axes.legend(frameon=False, ncol=4, loc="lower left",
                bbox_to_anchor=(0, 1), fontsize=8)
    save_figure(figure, filename)


def label_winning_prediction(axes, position, speedup, winning_prediction):
    is_faster = speedup >= 1
    label_gap = 0.005 if is_faster else -0.005
    prediction_number = winning_prediction.removeprefix("pred")
    axes.text(position, speedup + label_gap, prediction_number,
              ha="center", va="bottom" if is_faster else "top",
              fontsize=7, color="#555")


def plot_best_speedup(speedups, keys, filename):
    best_speedups = speedups.max(axis=1)
    winning_predictions = speedups.idxmax(axis=1)
    positions = np.arange(len(keys))

    figure, axes = plt.subplots(figsize=FIGURE_SIZE)
    axes.bar(positions, best_speedups - 1, 0.6, bottom=1,
             color=CONFIG_COLOURS["pred1"])
    for position, speedup, winner in zip(positions, best_speedups, winning_predictions):
        label_winning_prediction(axes, position, speedup, winner)

    draw_baseline(axes)
    use_log_speedup_axis(axes)
    axes.set_xticks(positions, keys)
    style_axes(axes, f"Best-of-3 speedup vs -{BASELINE}")
    axes.legend(frameon=False, loc="upper left", fontsize=8)
    save_figure(figure, filename)


def plot_key_table(keys, benchmark_names, filename):
    rows = [[key, name] for key, name in zip(keys, benchmark_names)]
    figure, axes = plt.subplots(figsize=(3.2, 0.28 * (len(rows) + 1)))
    axes.axis("off")

    table = axes.table(cellText=rows, colLabels=["Key", "Benchmark"],
                       loc="center", cellLoc="left", colWidths=[0.2, 0.8])
    table.auto_set_font_size(False)
    table.set_fontsize(8)
    for (row, _), cell in table.get_celld().items():
        cell.set_edgecolor("#ddd")
        if row == 0:
            cell.set_text_props(weight="bold")

    save_figure(figure, filename)


def main():
    parser = argparse.ArgumentParser(description="Plot benchmark results against -O3.")
    parser.add_argument("csv_path", type=Path, help="results CSV, e.g. results/run1.csv")
    csv_path = parser.parse_args().csv_path

    output_dir = csv_path.parent / csv_path.stem
    output_dir.mkdir(exist_ok=True)

    median_times = load_median_times(csv_path)
    speedups = compute_speedups(median_times)
    benchmark_names = list(median_times.index)
    keys = make_benchmark_keys(benchmark_names)

    plot_speedup_per_prediction(speedups, keys, output_dir / "1_speedup.png")
    plot_raw_times(median_times, keys, output_dir / "2_raw_times.png")
    plot_best_speedup(speedups, keys, output_dir / "3_best_speedup.png")
    plot_key_table(keys, benchmark_names, output_dir / "4_key.png")


if __name__ == "__main__":
    main()