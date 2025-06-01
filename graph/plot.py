import pandas as pd
import matplotlib.pyplot as plt
import os

# ─────────────── 경로 설정 ───────────────
base_paths = {
    'Held-Karp': '../held_karp/result/held_karp_summary.csv',
    'Christofides-Greedy': '../christofides_greedy/result/christofides_greedy_summary.csv',
    'Christofides-2Approx': '../christofides_2approx/result/christofides_2approx_summary.csv',
    'My-TSP': '../my_tsp/result/my_tsp_summary.csv'
}
output_dir = 'graph'
os.makedirs(output_dir, exist_ok=True)

# ─────────────── 데이터 로딩 ───────────────
all_data = []
for name, path in base_paths.items():
    df = pd.read_csv(path)
    df['Algorithm'] = name
    all_data.append(df)
all_data = pd.concat(all_data)

algorithm_colors = {
    'Held-Karp': '#1f77b4',           # 파란색
    'Christofides-Greedy': '#ff7f0e', # 주황색
    'Christofides-2Approx': '#2ca02c',# 초록색
    'My-TSP': '#d62728'               # 빨간색
}

ordered_instances = ['test4', 'test18', 'test20', 'test22', 'test24', 'a280', 'xql662', 'kz9976', 'mona-lisa_sample']
all_data["instance"] = pd.Categorical(all_data["instance"], categories=ordered_instances, ordered=True)

# ─────────────── 그리기 함수 ───────────────
def plot_grouped_bar(df, value_col, ylabel, filename, ylim=None, log_scale=False):
    df_sorted = df.sort_values("instance")
    pivot = df_sorted.pivot(index='instance', columns='Algorithm', values=value_col)

     # 알고리즘 순서 지정
    algorithm_order = ['Christofides-2Approx', 'Christofides-Greedy', 'My-TSP','Held-Karp']
    pivot = pivot[ [alg for alg in algorithm_order if alg in pivot.columns] ]  # 열 순서 재정렬

    colors = [algorithm_colors[alg] for alg in pivot.columns]  # 순서에 맞춰 색상도 정렬

    ax = pivot.plot(kind='bar', figsize=(10, 6))
    plt.ylabel(ylabel)
    ax.set_ylabel(ylabel, fontsize=15)     # y축 라벨 폰트 크기
    ax.set_xlabel("")                      # x축 라벨 제거
    ax.tick_params(axis='x', labelsize=15) # x축 인스턴스 라벨 크기
    ax.tick_params(axis='y', labelsize=12)
    if ylim:
        plt.ylim(ylim)
    if log_scale:
        ax.set_yscale('log')
    plt.xticks(rotation=0)
    plt.legend(title='Algorithm')
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, filename))
    plt.close()

# ─────────────── 필터 및 출력 ───────────────
def filter_and_plot(instances, exclude_heldkarp=False, mona=False, ylim_time=None, ylim_ratio=None, log_time=False):
    df = all_data[all_data['instance'].isin(instances)]
    if exclude_heldkarp:
        df = df[df['Algorithm'] != 'Held-Karp']

    if mona:
        plot_grouped_bar(df, "time_ms", "Time (ms)", "mona_group_time.png", ylim=ylim_time)
        plot_grouped_bar(df, "cost", "Tour Cost", "mona_group_cost.png")
    else:
        plot_grouped_bar(df, "time_ms", "Time (ms)", f"{instances[0]}_group_time.png", ylim=ylim_time, log_scale=log_time)
        plot_grouped_bar(df, "approx_ratio", "Approximation Ratio", f"{instances[0]}_group_ratio.png", ylim=ylim_ratio)


# ─────────────── 그래프 실행 ───────────────
filter_and_plot(['test4', 'test18', 'test20', 'test22', 'test24'], ylim_time=(1e-2, 1e5), ylim_ratio=(0.0, 2.0), log_time=True)
filter_and_plot(['a280', 'xql662'], exclude_heldkarp=True, ylim_time=(0, 200), ylim_ratio=(1.0, 2.0))
filter_and_plot(['kz9976', 'mona-lisa_sample'], exclude_heldkarp=True, mona=True, ylim_time=(0, 40000))
