import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("neuron_output.txt")
steps = data[:, 0]  # Time steps
neurons = data[:, 1]  # Neuron IDs
potentials = data[:, 2]  # Membrane potentials

plt.figure(figsize=(10, 5))
plt.scatter(steps, neurons, c=potentials, cmap='coolwarm', s=1)
plt.colorbar(label='Membrane Potential')
plt.xlabel("Time Step")
plt.ylabel("Neuron ID")
plt.title("Neuron Activity Over Time")
plt.show()

summary_data = np.loadtxt("neuron_summary.txt", dtype=str)
# each line is like: "Neuron 0 fired 41 times" -> number is the second-to-last token
fire_counts = np.array([int(row[-2]) for row in summary_data])

plt.figure(figsize=(8, 5))
plt.hist(fire_counts, bins=20, color='blue', edgecolor='black')
plt.xlabel("Firing Count")
plt.ylabel("Number of Neurons")
plt.title("Distribution of Neuron Firings")
plt.show()