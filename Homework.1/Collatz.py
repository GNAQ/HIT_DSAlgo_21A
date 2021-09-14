# 角谷猜想（又名考拉兹猜想，Collatz conjecture）
from typing import List, Tuple

# 对于正整数 x 检查角谷猜想
# 返回操作序列的长度
def Check_Collatz(x: int) -> List[int]:
	res = [x]
	while x != 1:
		if len(res) > 50000:
			return []
		if x % 2 == 0:
			x //= 2
		else:
			x = x * 3 + 1
		res.append(x)
	return res

def main():
	flag = True
	ans = []
	for i in range(1, 101):
		res = Check_Collatz(i)
		if res == []:
			flag = False
			print("数字", i, "不符合角谷猜想")
		if (len(res) > len(ans)):
			ans = res.copy()
	
	if flag == True:
		print("1 - 100 的所有整数均符合角谷猜想。")
		print("其中最长的操作序列是：", end="")
		print(*ans, sep=" -> ")

if __name__ == "__main__":
	main()