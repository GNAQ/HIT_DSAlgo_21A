# 冒泡排序算法 Bubble Sort
# 输入格式：一行 n 个正整数 a_1 .. a_n

def Bubble_Sort(arr):
	n = len(arr)

	for i in range(len(arr)):
		for j in range(0, n - i - 1):
			if (arr[j] > arr[j + 1]):
				arr[j], arr[j + 1] = arr[j + 1], arr[j]
def main():
	print("请输入 n 个整数：")
	arr = []
	while True:
		try:
			arr = [int(x) for x in input().split(" ")]
			break
		except ValueError:
			print("请重试：请输入整数")

	Bubble_Sort(arr)

	print("排序结果：")
	for x in arr:
		print(x, " ", end="")
	print("")
		
if __name__ == "__main__":
	main()