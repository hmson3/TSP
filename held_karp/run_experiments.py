import subprocess

# 설정
EXECUTABLE = "../build/held_karp_exec"
INSTANCES = ["test4", "test18", "test20", "test22", "test24"]
DATA_DIR = "../data"

for instance in INSTANCES:
    print(f"▶ Running: {instance}")

    process = subprocess.run(
        [EXECUTABLE, instance],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )

    # 출력 로그 보기
    print(process.stdout.strip())

print("\n✅ All instances executed.")
