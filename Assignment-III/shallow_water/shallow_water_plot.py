from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np


def plot_file(input_path: Path, output_dir: Path) -> Path:
	data = np.loadtxt(input_path)

	fig, ax = plt.subplots(figsize=(8, 6))
	im = ax.imshow(data, cmap="viridis", origin="lower")
	fig.colorbar(im, ax=ax, label="Water Height")

	init_name = input_path.stem.replace("output_", "")
	ax.set_title(f"Shallow Water: {init_name}")
	ax.set_xlabel("x")
	ax.set_ylabel("y")

	output_path = output_dir / f"{input_path.stem}.png"
	fig.tight_layout()
	fig.savefig(output_path, dpi=200)
	plt.close(fig)
	return output_path


def main() -> None:
	workdir = Path(__file__).resolve().parent
	output_dir = workdir / "plots"
	output_dir.mkdir(exist_ok=True)

	txt_files = sorted(workdir.glob("output_*.txt"))
	if not txt_files:
		print("No output_*.txt files found.")
		return

	for txt_file in txt_files:
		saved = plot_file(txt_file, output_dir)
		print(saved.name)


if __name__ == "__main__":
	main()