import csv
from pathlib import Path


def read_csv(path):
    sizes = []
    rtts = []
    with path.open("r", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            sizes.append(float(row["message_size_bytes"]))
            rtts.append(float(row["rtt_microseconds"]))
    return sizes, rtts


def fit_weighted(x, y):
    """Weighted least squares with w_i = 1/y_i^2 (minimises sum of squared relative errors)."""
    w = [1.0 / (yi * yi) for yi in y]
    sw = sum(w)

    x_mean_w = sum(wi * xi for wi, xi in zip(w, x)) / sw
    y_mean_w = sum(wi * yi for wi, yi in zip(w, y)) / sw

    sxx_w = sum(wi * (xi - x_mean_w) ** 2 for wi, xi in zip(w, x))
    sxy_w = sum(wi * (xi - x_mean_w) * (yi - y_mean_w) for wi, xi, yi in zip(w, x, y))

    beta = sxy_w / sxx_w
    alpha = y_mean_w - beta * x_mean_w

    y_hat = [alpha + beta * xi for xi in x]
    # R² in relative terms
    ss_res = sum(wi * (yi - ypi) ** 2 for wi, yi, ypi in zip(w, y, y_hat))
    ss_tot = sum(wi * (yi - y_mean_w) ** 2 for wi, yi in zip(w, y))
    r2 = 1.0 - ss_res / ss_tot

    return alpha, beta, r2


def main():
    base_dir = Path(__file__).resolve().parent
    data_dir = base_dir / "formatted_data"

    train_files = ["dardel_1.csv", "school_cluster_1.csv"]

    for fname in train_files:
        path = data_dir / fname
        x, y = read_csv(path)
        alpha, beta, r2 = fit_weighted(x, y)

        print(f"Dataset: {path.stem}")
        print("Model (weighted, w=1/y^2): RTT(us) = alpha + beta * size(bytes)")
        print(f"alpha = {alpha:.6f} us")
        print(f"beta  = {beta:.9f} us/byte")
        print(f"R^2   = {r2:.6f}  (weighted, in relative space)")
        print()


if __name__ == "__main__":
    main()
