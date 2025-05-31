import pandas as pd
import numpy as np

# 사용자 지정 순서
desired_order = [
    "test4", "test18", "test20", "test22", "test24",
    "a280", "xql662", "kz9976", "mona-lisa_sample"
]

# 파일 경로
input_file = "./result/my_tsp_result.csv"
output_file = "./result/my_tsp_summary.csv"

# CSV 불러오기
df = pd.read_csv(input_file)

# approx_ratio에서 'N/A' → np.nan으로 처리
df['approx_ratio'] = pd.to_numeric(df['approx_ratio'], errors='coerce')

# 평균 계산
summary = df.groupby('instance', as_index=False).agg({
    'cost': 'mean',
    'time_ms': 'mean',
    'approx_ratio': 'mean'
})

# 지정 순서대로 정렬
summary['order'] = summary['instance'].apply(lambda x: desired_order.index(x) if x in desired_order else float('inf'))
summary = summary.sort_values('order').drop(columns='order')

# 소수점 6자리로 포맷팅

summary['time_ms'] = summary['time_ms'].map(lambda x: f"{x: .6g}")
summary['approx_ratio'] = summary['approx_ratio'].map(lambda x: x if not pd.isna(x) else "N/A")

# 저장
summary.to_csv(output_file, index=False)
print(f"✔ 요약 완료: {output_file}")