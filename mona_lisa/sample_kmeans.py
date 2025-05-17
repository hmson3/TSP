import numpy as np
from sklearn.cluster import KMeans

def read_tsp_file(filename):
    coords = []
    with open(filename, 'r') as f:
        lines = f.readlines()
    reading = False
    for line in lines:
        if line.startswith("NODE_COORD_SECTION"):
            reading = True
            continue
        if line.startswith("EOF"):
            break
        if reading:
            parts = line.strip().split()
            if len(parts) == 3:
                _, x, y = parts
                coords.append((float(x), float(y)))
    return np.array(coords)

def write_tsp_file(filename, coords):
    with open(filename, 'w') as f:
        f.write("NAME: sample_kmeans_10000\n")
        f.write("TYPE: TSP\n")
        f.write(f"DIMENSION: {len(coords)}\n")
        f.write("EDGE_WEIGHT_TYPE: EUC_2D\n")
        f.write("NODE_COORD_SECTION\n")
        for i, (x, y) in enumerate(coords, start=1):
            f.write(f"{i} {x:.6f} {y:.6f}\n")
        f.write("EOF\n")

# === Main ===
input_file = "mona-lisa100K.tsp"      # 원본 TSP 파일
output_file = "mona-lisa_sample.tsp"  # 저장할 TSP 파일
num_clusters = 10000

print("[+] Reading TSP file...")
points = read_tsp_file(input_file)

print(f"[+] Clustering {len(points)} points into {num_clusters} clusters...")
kmeans = KMeans(n_clusters=num_clusters, random_state=42, n_init="auto").fit(points)
centroids = kmeans.cluster_centers_

print(f"[+] Writing {num_clusters} centroid points to TSP file...")
write_tsp_file(output_file, centroids)

print(f"[✓] Done! Output written to {output_file}")
