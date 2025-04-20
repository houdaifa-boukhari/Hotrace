# generate_50mb_test.py
import random
import string

def random_word(length=32):
    return ''.join(random.choices(string.ascii_lowercase, k=length))

def generate_50mb_test(filename="test_1024b.htr"):
    written = 0 
    target_bytes = 1024
    keys = []

    with open(filename, "w") as f:
        
        while written < target_bytes * 0.5:
            key = random_word()
            value = random_word()
            keys.append(key)
            line = f"{key}\n{value}\n"
            f.write(line)
            written += len(line)

        f.write("\n")  

        for i in range(len(keys)):
            f.write(f"{keys[i]}\n")
        for _ in range(len(keys) // 4):
            f.write(f"{random_word()}\n")

    print(f"[✔] file has been created: {filename}")

generate_50mb_test()