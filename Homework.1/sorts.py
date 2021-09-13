from typing import List, Tuple
from timeit import default_timer as timer

def Clone_1st_Arg(func):
	def inner(arg0, *args, **kwargs):
		return func(arg0.copy(), *args, **kwargs)
	return inner

# 冒泡排序算法 Bubble Sort
# 算法复杂度：空间复杂度 O(n)，时间复杂度 O(n^2)
@Clone_1st_Arg
def Bubble_Sort(arr: List[int]) -> Tuple[List[int], float]:
	beginTime = timer()
	n = len(arr)
	for i in range(n):
		for j in range(0, n - i - 1):
			if (arr[j] > arr[j + 1]):
				# swap trick using tuple
				arr[j], arr[j + 1] = arr[j + 1], arr[j]
	return arr, timer() - beginTime

# 插入排序算法
# 算法复杂度：空间复杂度 O(n)，时间复杂度 O(n^2)
@Clone_1st_Arg
def Insert_Sort(arr) -> Tuple[List[int], float]:
	beginTime = timer()
	for i in range(len(arr)):
		for j in range(i):
			if arr[j] > arr[i]:
				# slices tricks
				# 使用 slice 截取原数组 (list) 的片段，再拼接起来
				# 这是在模拟将 arr[i] 移动到 arr[j - 1] 和 arr[j] 之间的过程
				arr = arr[:j] + [arr[i]] + arr[j:i] + arr[i+1:]
				break
	return arr, timer() - beginTime

# 选择排序算法
# 算法复杂度：空间复杂度 O(n)，时间复杂度 O(n^2)
@Clone_1st_Arg
def Select_Sort(arr) -> Tuple[List[int], float]:
	beginTime = timer()
	result = []
	n = len(arr)
	for _i in range(n):
		minVal = 0
		for j in range(len(arr)):
			if arr[minVal] > arr[j]:
				minVal = j
		result.append(arr[minVal])
		del arr[minVal]
	return result, timer() - beginTime

def Print_Result(result: Tuple[List[int], float], hint: str):
	print(hint)
	print(result[0], sep=", ")
	print("Time Consumption:", "{:.5f}".format(result[1]), "second(s)")

# 输入格式：一行 n 个正整数 a_1 .. a_n
def main():
	print("请输入 n 个整数：")
	arr = []
	while True:
		try:
			arr = [int(x) for x in input().split(" ")]
			break
		except ValueError:
			print("请重试：请输入整数")

	Print_Result(Bubble_Sort(arr), "冒泡排序结果：")
	Print_Result(Insert_Sort(arr), "插入排序结果：")
	Print_Result(Select_Sort(arr), "选择排序结果：")
	
if __name__ == "__main__":
	main()