import subprocess

# 설정
EXECUTABLE = "../build/christofides_exec"
# 근데 테스트 4개 중 최소가 280
# 그래서 test4, test18, test22로 잘 작동하는 지 확인
INSTANCES = ["test4", "test18", "test20", "test22", "test24", "a280", "xql662", "kz9976", "mona-lisa_sample"]
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
