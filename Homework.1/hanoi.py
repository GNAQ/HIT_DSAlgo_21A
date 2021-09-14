# Author: GNAQ (HIT-120L022004)
# Date: 2021/09/14 12:04

def Hanoi(btnId: int, a: str, b: str, c: str):
	if btnId == 0:
		return
	Hanoi(btnId - 1, a, c, b)
	print("Move plate", btnId, "from", a, "to", c)
	Hanoi(btnId - 1, b, a, c)

def main():
	while True:
		try:
			n = int(input())
			Hanoi(n, "A", "B", "C")
			break
		except ValueError:
			print("请重试：请输入正整数")

if __name__ == "__main__":
	main()