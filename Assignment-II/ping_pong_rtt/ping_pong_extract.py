import csv
import re
from pathlib import Path


section_re = re.compile(r"^#\s+(.+?)\s*$")
data_re = re.compile(
    r"^Size:\s*(\d+)\s*Bytes,\s*RTT:\s*([0-9]*\.?[0-9]+)\s*microseconds\s*$"
)


def safe_name(name):
    return re.sub(r"[^a-zA-Z0-9]+", "_", name.strip().lower()).strip("_")


def group_name(name):
    # "Dardel 3" -> "dardel", "School Cluster" -> "school_cluster"
    base = re.sub(r"\s+\d+$", "", name.strip())
    return safe_name(base)


def main():
    base_dir = Path(__file__).resolve().parent
    md_path = base_dir / "ping_pong_mpi_results.md"
    out_dir = base_dir / "formatted_data"
    out_dir.mkdir(exist_ok=True)

    current = None
    data = {}

    for line in md_path.read_text(encoding="utf-8").splitlines():
        line = line.strip()

        m1 = section_re.match(line)
        if m1:
            current = m1.group(1)
            data[current] = []
            continue

        m2 = data_re.match(line)
        if m2 and current:
            size = int(m2.group(1))
            rtt = float(m2.group(2))
            data[current].append((size, rtt))

    for name, points in data.items():
        if not points:
            continue

        out_path = out_dir / f"{safe_name(name)}.csv"
        with out_path.open("w", newline="", encoding="utf-8") as f:
            writer = csv.writer(f)
            writer.writerow(["message_size_bytes", "rtt_microseconds"])
            writer.writerows(points)

        print(f"Saved: {out_path} ({len(points)} rows)")

    # Save all raw points in one table: group, section, size, rtt
    all_rows = []
    for name, points in data.items():
        gname = group_name(name)
        for size, rtt in points:
            all_rows.append((gname, name, size, rtt))

    all_csv = out_dir / "all_sections.csv"
    with all_csv.open("w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        writer.writerow(["group", "section", "message_size_bytes", "rtt_microseconds"])
        writer.writerows(all_rows)
    print(f"Saved: {all_csv} ({len(all_rows)} rows)")

    # Average repeated runs inside each group by message size.
    grouped = {}
    for name, points in data.items():
        gname = group_name(name)
        grouped.setdefault(gname, {})
        for size, rtt in points:
            grouped[gname].setdefault(size, []).append(rtt)

if __name__ == "__main__":
    main()
