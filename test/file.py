import subprocess
import time
import random
import string

def generate_data(num_pairs):
    lines = []
    keys = []

    # First section: key-value pairs
    for i in range(num_pairs):
        key = f"key{i}"
        value = f"value{i}"
        lines.append(f"{key}\n")
        lines.append(f"{value}\n")
        keys.append(key)

    lines.append("\n")  # Delimiter

    # Second section: some existing and some missing keys
    for i in range(num_pairs // 2):
        lines.append(f"{random.choice(keys)}\n")  # Existing
    for i in range(num_pairs // 4):
        lines.append(f"missing_key{i}\n")  # Not found

    return "".join(lines)

def run_program(executable, input_data):
    start_time = time.time()

    process = subprocess.run(
        [f"./{executable}"],
        input=input_data,
        text=True,
        capture_output=True
    )

    end_time = time.time()

    print("=== Output ===")
    print(process.stdout)

    if process.stderr:
        print("=== Errors ===")
        print(process.stderr)

    print(f"\nExecution Time: {end_time - start_time:.6f} seconds")

if __name__ == "__main__":
    NUM_PAIRS = 1000  # You can increase for stress testing
    EXECUTABLE = "hotrace"  # Change this if your binary is named differently

    input_data = generate_data(NUM_PAIRS)
    run_program(EXECUTABLE, input_data)