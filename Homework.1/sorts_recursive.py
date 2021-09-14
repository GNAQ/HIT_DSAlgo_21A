from typing import List

# 冒泡排序算法 Bubble Sort
# 算法复杂度：空间复杂度 O(n)，时间复杂度 O(n^2)
def Bubble_Sort(arr: List[int], i: int) -> List[int]:
	n = len(arr)
	if i == n:
		return arr
	for j in range(0, n - i - 1):
		if (arr[j] > arr[j + 1]):
			# swap trick using tuple
			arr[j], arr[j + 1] = arr[j + 1], arr[j]
	return Bubble_Sort(arr, i + 1)

# 插入排序算法
# 算法复杂度：空间复杂度 O(n)，时间复杂度 O(n^2)
def Insert_Sort(arr: List[int], i: int) -> List[int]:
	if i == len(arr):
		return arr
	for j in range(i):
		if arr[j] > arr[i]:
			# slices tricks
			# 使用 slice 截取原数组 (list) 的片段，再拼接起来
			# 这是在模拟将 arr[i] 移动到 arr[j - 1] 和 arr[j] 之间的过程
			arr = arr[:j] + [arr[i]] + arr[j:i] + arr[i+1:]
			break
	return Insert_Sort(arr, i + 1)

# 选择排序算法
# 算法复杂度：空间复杂度 O(n)，时间复杂度 O(n^2)
def Select_Sort(arr: List[int], i: int) -> List[int]:
	if i == len(arr):
		return arr
	minVal = i
	for j in range(i, len(arr)):
		if arr[minVal] > arr[j]:
			minVal = j
	arr[minVal], arr[i] = arr[i], arr[minVal]
	return Select_Sort(arr, i + 1)

def Print_Result(arr: List[int], hint: str):
	print(hint)
	print(arr, sep=", ")

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

	Print_Result(Bubble_Sort(arr.copy(), 0), "（递归）冒泡排序结果：")
	Print_Result(Insert_Sort(arr.copy(), 0), "（递归）插入排序结果：")
	Print_Result(Select_Sort(arr.copy(), 0), "（递归）选择排序结果：")
	
if __name__ == "__main__":
	main()