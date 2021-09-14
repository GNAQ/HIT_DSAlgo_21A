from typing import List, Tuple

def Print_Move(src: str, dest: str, plateId: int):
	print("Move plate", plateId, "from", src, "to", dest)

def Make_Move(src: Tuple[List[int], str], dest: Tuple[List[int], str]):
	# For rubust, we DON'T care which pole is the real destination
	plate1 = src[0].pop()
	plate2 = dest[0].pop()
	
	# Stack src is empty
	if plate1 == -1:
		src[0].append(-1)
		src[0].append(plate2)
		Print_Move(dest[1], src[1], plate2)
	# Stack dest is empty
	elif plate2 == -1:
		dest[0].append(-1)
		dest[0].append(plate1)
		Print_Move(src[1], dest[1], plate1)
	# put on dest
	elif plate2 > plate1:
		dest[0].append(plate2)
		dest[0].append(plate1)
		Print_Move(src[1], dest[1], plate1)
	# put on src
	elif plate1 > plate2:
		src[0].append(plate1)
		src[0].append(plate2)
		Print_Move(dest[1], src[1], plate2)
	# print("Move once:", src, dest)
	
def Hanoi_norecursive(btnId: int, a: str, b: str, c: str):
	stkA, stkB, stkC = [-1], [-1], [-1]
	stkA += reversed(list(x for x in range(1, btnId + 1)))
	
	if btnId % 2 == 0:
		b, c = c, b
	for i in range(1, 2 ** btnId): # Time complexity: O(2^n); main consumption in this loop
		if i % 3 == 1:
			Make_Move((stkA, a), (stkC, c))
		elif i % 3 == 2:
			Make_Move((stkA, a), (stkB, b))
		elif i % 3 == 0:
			Make_Move((stkB, b), (stkC, c))
	
def main():
	while True:
		try:
			n = int(input())
			Hanoi_norecursive(n, "A", "B", "C")
			break
		except ValueError:
			print("请重试：请输入正整数")

if __name__ == "__main__":
	main()