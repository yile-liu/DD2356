import argparse
import csv
from pathlib import Path

import matplotlib.pyplot as plt


def read_csv(path):
    x = []
    y = []
    with path.open("r", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            x.append(float(row["message_size_bytes"]))
            y.append(float(row["rtt_microseconds"]))
    return x, y


def point_errors(x, y, alpha, beta):
    rows = []
    for xi, yi in zip(x, y):
        y_pred = alpha + beta * xi
        abs_err_us = abs(yi - y_pred)
        abs_err_ms = abs_err_us / 1000.0
        rel_err = (abs_err_us / abs(y_pred) * 100.0) if y_pred != 0 else float("inf")
        rows.append((xi, yi, y_pred, rel_err, abs_err_ms))
    return rows


def plot_group(ax, x_model, y_model_vals, datasets, title):
    ax.plot(x_model, y_model_vals, "k-", linewidth=2, label="Model prediction")
    for label, (x, y) in datasets.items():
        ax.plot(x, y, "o-", markersize=3, label=label)
    ax.set_xscale("log", base=2)
    ax.set_yscale("log", base=10)
    ax.set_xlabel("Message Size (Bytes)")
    ax.set_ylabel("RTT (microseconds)")
    ax.set_title(title)
    ax.grid(True, which="both", linestyle="--", alpha=0.4)
    ax.legend()


def main():
    parser = argparse.ArgumentParser(
        description="Evaluate RTT model on validation runs and plot results."
    )
    parser.add_argument(
        "--alpha-dardel", type=float, required=True, help="Dardel model alpha (us)"
    )
    parser.add_argument(
        "--beta-dardel",
        type=float,
        required=True,
        help="Dardel model beta (us/byte)",
    )
    parser.add_argument(
        "--alpha-school",
        type=float,
        required=True,
        help="School cluster model alpha (us)",
    )
    parser.add_argument(
        "--beta-school",
        type=float,
        required=True,
        help="School cluster model beta (us/byte)",
    )
    parser.add_argument(
        "--out", default="fit_plot.png", help="Output plot file name (png)"
    )
    parser.add_argument(
        "--error-out",
        default="fit_errors.csv",
        help="Output CSV for per-point errors",
    )
    args = parser.parse_args()

    base_dir = Path(__file__).resolve().parent
    data_dir = base_dir / "formatted_data"

    groups = {
        "dardel": {
            "alpha": args.alpha_dardel,
            "beta": args.beta_dardel,
            "runs": [2, 3, 4, 5],
        },
        "school_cluster": {
            "alpha": args.alpha_school,
            "beta": args.beta_school,
            "runs": [2, 3, 4, 5],
        },
    }

    all_error_rows = []

    print(
        f"{'dataset':<30} {'size(B)':>12} {'measured(us)':>14} "
        f"{'predicted(us)':>14} {'rel_err(%)':>12} {'abs_err(ms)':>13}"
    )
    print("-" * 100)

    out_stem = Path(args.out).stem
    out_suffix = Path(args.out).suffix or ".png"
    saved_plots = []

    for group_name, cfg in groups.items():
        alpha, beta = cfg["alpha"], cfg["beta"]
        datasets = {}

        for run in cfg["runs"]:
            fname = f"{group_name}_{run}.csv"
            path = data_dir / fname
            x, y = read_csv(path)
            datasets[fname.replace(".csv", "")] = (x, y)

            err_rows = point_errors(x, y, alpha, beta)
            for xi, yi, y_pred, rel_err, abs_err_ms in err_rows:
                label = f"{group_name}_{run}"
                print(
                    f"{label:<30} {xi:>12.0f} {yi:>14.6f} "
                    f"{y_pred:>14.6f} {rel_err:>12.4f} {abs_err_ms:>13.9f}"
                )
                all_error_rows.append(
                    (label, xi, yi, y_pred, rel_err, abs_err_ms)
                )

        # Build model prediction curve over the union of all x values
        all_x = sorted({xi for x, _ in datasets.values() for xi in x})
        model_y = [alpha + beta * xi for xi in all_x]

        fig, ax = plt.subplots(figsize=(8, 5))
        plot_group(ax, all_x, model_y, datasets, f"{group_name} — model vs runs 2–5")
        group_out = base_dir / f"{out_stem}_{group_name}{out_suffix}"
        fig.tight_layout()
        fig.savefig(group_out, dpi=150)
        plt.close(fig)
        saved_plots.append(group_out)

    err_out_path = base_dir / args.error_out
    with err_out_path.open("w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        writer.writerow(
            [
                "dataset",
                "message_size_bytes",
                "measured_rtt_microseconds",
                "predicted_rtt_microseconds",
                "relative_error_percent",
                "absolute_error_milliseconds",
            ]
        )
        writer.writerows(all_error_rows)

    print()
    for p in saved_plots:
        print(f"Saved plot:   {p}")
    print(f"Saved errors: {err_out_path}")


if __name__ == "__main__":
    main()
