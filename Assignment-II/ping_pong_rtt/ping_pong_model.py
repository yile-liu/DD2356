import csv
import math
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


def fit_linear(x, y):
    n = len(x)
    x_mean = sum(x) / n
    y_mean = sum(y) / n

    sxx = sum((xi - x_mean) ** 2 for xi in x)
    sxy = sum((xi - x_mean) * (yi - y_mean) for xi, yi in zip(x, y))

    beta = sxy / sxx
    alpha = y_mean - beta * x_mean

    y_hat = [alpha + beta * xi for xi in x]
    ss_res = sum((yi - ypi) ** 2 for yi, ypi in zip(y, y_hat))
    ss_tot = sum((yi - y_mean) ** 2 for yi in y)
    r2 = 1.0 - ss_res / ss_tot

    return alpha, beta, r2


def fit_loglog(x, y):
    """Fit log(RTT) = A + B*log(size), i.e. RTT = C * size^D."""
    lx = [math.log(xi) for xi in x]
    ly = [math.log(yi) for yi in y]

    n = len(lx)
    lx_mean = sum(lx) / n
    ly_mean = sum(ly) / n

    sxx = sum((xi - lx_mean) ** 2 for xi in lx)
    sxy = sum((xi - lx_mean) * (yi - ly_mean) for xi, yi in zip(lx, ly))

    B = sxy / sxx
    A = ly_mean - B * lx_mean

    C = math.exp(A)  # RTT = C * size^D
    D = B

    ly_hat = [A + B * xi for xi in lx]
    ss_res = sum((yi - ypi) ** 2 for yi, ypi in zip(ly, ly_hat))
    ss_tot = sum((yi - ly_mean) ** 2 for yi in ly)
    r2 = 1.0 - ss_res / ss_tot  # R² in log space

    return C, D, r2


def main():
    base_dir = Path(__file__).resolve().parent
    data_dir = base_dir / "formatted_data"

    train_files = ["dardel_1.csv", "school_cluster_1.csv"]

    for fname in train_files:
        path = data_dir / fname
        x, y = read_csv(path)

        alpha, beta, r2_lin = fit_linear(x, y)
        C, D, r2_log = fit_loglog(x, y)

        print(f"Dataset: {path.stem}")

        print("  [Linear]  RTT(us) = alpha + beta * size")
        print(f"    alpha = {alpha:.6f} us")
        print(f"    beta  = {beta:.9f} us/byte")
        print(f"    R^2   = {r2_lin:.6f}")

        print("  [Log-log] RTT(us) = C * size^D")
        print(f"    C     = {C:.6f}")
        print(f"    D     = {D:.6f}")
        print(f"    R^2   = {r2_log:.6f}  (in log space)")
        print()


if __name__ == "__main__":
    main()
