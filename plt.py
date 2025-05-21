## \file plt.py
## \brief Parses timing data and plots performance of sorting algorithms.

import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('times.csv')

plt.figure(figsize=(12, 7))

plt.plot(data['size'], data['std::sort'], marker='o', label='std::sort')
plt.plot(data['size'], data['quickSort'], marker='o', label='quickSort')
plt.plot(data['size'], data['heapSort'], marker='o', label='heapSort')
plt.plot(data['size'], data['shakerSort'], marker='o', label='shakerSort')


plt.xlabel('Размер массива (элементы)', fontsize=12)
plt.ylabel('Время сортировки (мс)', fontsize=12)
plt.title('Сравнение алгоритмов сортировки', fontsize=14)
plt.legend()

plt.savefig("sort_comparison.png", dpi=300, bbox_inches='tight')

plt.show()

# --- Graph with logarithmic scale Y ---
plt.figure(figsize=(12, 7))

plt.plot(data['size'], data['std::sort'], marker='o', label='std::sort')
plt.plot(data['size'], data['quickSort'], marker='o', label='quickSort')
plt.plot(data['size'], data['heapSort'], marker='o', label='heapSort')
plt.plot(data['size'], data['shakerSort'], marker='o', label='shakerSort')

plt.yscale('log')  # logarithmic scale Y

plt.xlabel('Размер массива (элементы)', fontsize=12)
plt.ylabel('Время сортировки (мс, логарифмически)', fontsize=12)
plt.title('Сравнение алгоритмов сортировки (логарифмическая шкала)', fontsize=14)
plt.legend()

plt.savefig("sort_comparison_log.png", dpi=300, bbox_inches='tight')
plt.show()