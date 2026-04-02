import subprocess
import csv
import os

# Konfigurasi Testbench
C_FILE = "ver2_test.c"
EXEC_FILE = "./run_arr"
OUTPUT_CSV = "metrics_arr.csv"
DATA_SIZES = {'Small': 1000, 'Medium': 50000, 'Large': 200000}

# Ukuran memori 64-bit Mac: Tree struct saja = 64 bytes.
TREE_SIZE_BYTES = 64

def compile_c():
    print(f"[*] Compiling {C_FILE}...")
    subprocess.run(["gcc", "-O3", C_FILE, "-o", EXEC_FILE], check=True)

def run_analysis():
    results = []
    
    for label, n in DATA_SIZES.items():
        print(f"[*] Analyzing Dynamic Array for {label} size (N={n})...")
        
        process = subprocess.run([EXEC_FILE, str(n)], capture_output=True, text=True)
        times = process.stdout.strip().split(',')
        
        time_add = float(times[0])
        time_view = float(times[1])
        time_delete = float(times[2])
        
        # Kalkulasi Metrics (Array lebih hemat RAM)
        memory_mb = (n * TREE_SIZE_BYTES) / (1024 * 1024)
        
        tp_add = n / time_add if time_add > 0 else float('inf')
        tp_view = n / time_view if time_view > 0 else float('inf')
        
        results.append({
            'Size': label,
            'N': n,
            'Memory_Usage (MB)': round(memory_mb, 4),
            'Time_Add (s)': f"{time_add:.6f}",
            'Throughput_Add (ops/s)': round(tp_add, 2),
            'Time_View (s)': f"{time_view:.6f}",
            'Throughput_View (ops/s)': round(tp_view, 2),
            'Time_Delete_1_Node (s)': f"{time_delete:.8f}"
        })
        
    return results

def save_to_csv(data):
    keys = data[0].keys()
    with open(OUTPUT_CSV, 'w', newline='') as output_file:
        dict_writer = csv.DictWriter(output_file, fieldnames=keys)
        dict_writer.writeheader()
        dict_writer.writerows(data)
    print(f"[+] Dynamic Array analysis complete! Saved to {OUTPUT_CSV}")

if __name__ == "__main__":
    compile_c()
    metrics = run_analysis()
    save_to_csv(metrics)
    if os.path.exists(EXEC_FILE):
        os.remove(EXEC_FILE)