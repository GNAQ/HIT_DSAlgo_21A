// Author: 王子恺 (120L022004)
// Date: 2021/10/9
// Compiler flags: -Wall -Wextra -Werror -O2 -std=c++11

#include <bits/stdc++.h>
using std::cout; using std::cin;
using std::cerr; using std::endl;

const int DIR[8][2] = {
	{0, 1}, {1, 1}, {1, 0},
	{1, -1}, {0, -1}, {-1, -1},
	{-1, 0}, {-1, 1}
};
const int REV[8] = {4, 5, 6, 7, 0, 1, 2, 3};

const std::string CHARSET[10] = {" ", "→", "↘", "↓", "↙", "←", "↖", "↑", "↗", "×"};

class Maze
{
private:
	int h, w;
	std::vector<std::vector<int>> brd;
	std::vector<std::vector<int>> path;
	std::vector<std::vector<int>> vis;
	std::vector<std::pair<int, int>> path_list;
	
	
	inline bool in(int x, int y)
	{
		if (x >= 1 && x <= h && y >= 1 && y <= w)
			return true;
		return false;
	}
	
	inline void fill1(int x, int y, int z)
	{
		brd[x][y] |= (1 << z);
	}
	
	inline void fill0(int x, int y, int z)
	{
		brd[x][y] &= (~(1 << z));
	}
	
	inline void reset()
	{
		vis.resize(h + 2, std::vector<int>(w + 2, 0));
		path.resize(h + 2, std::vector<int>(w + 2, 0));
		path[h][w] = 9;
		path_list.clear();
	}
	
public:
	Maze() {}
	Maze(int height, int width) 
		: h(height), w(width) 
	{
		if (h * w > 2500)
			throw("Maze oversized.");
		brd.resize(height + 2, std::vector<int>(width + 2, 0));
		vis.resize(height + 2, std::vector<int>(width + 2, 0));
		path.resize(height + 2, std::vector<int>(width + 2, 0));
		path[h][w] = 9;
	}
	
	inline bool get(int x, int y, int z)
	{
		if (!in(x, y, z))
			throw std::out_of_range("Error: get() method out of index range.");
		return (brd[x][y] >> z) & 1;
	}
	
	inline bool in(int x, int y, int z)
	{
		if (in(x, y) && z >= 0 && z <= 7)
			return true;
		return false;
	}
	
	inline void fill(int x, int y, int z, int m)
	{
		if (!in(x, y, z))
			throw std::out_of_range("Error: (x, y, z) out of range.");
		
		(m == 1) ? 
			fill1(x, y, z) : fill0(x, y, z);
		if (in(x + DIR[z][0], y + DIR[z][1], REV[z]))
			(m == 1) ? 
				fill1(x + DIR[z][0], y + DIR[z][1], REV[z]):
				fill0(x + DIR[z][0], y + DIR[z][1], REV[z]);
		
		if (z%2 == 1)
		{
			int z1 = (z + 1) % 8, z2 = (z + 7) % 8;
			int zz1 = (z + 2) % 8, zz2 = (z + 6) % 8;
			if (in(x + DIR[z1][0], y + DIR[z1][1], REV[zz1]))
				(m == 1) ? 
					fill1(x + DIR[z1][0], y + DIR[z1][1], REV[zz1]):
					fill0(x + DIR[z1][0], y + DIR[z1][1], REV[zz1]);
			if (in(x + DIR[z2][0], y + DIR[z2][1], REV[zz2]))
				(m == 1) ? 
					fill1(x + DIR[z2][0], y + DIR[z2][1], REV[zz2]):
					fill0(x + DIR[z2][0], y + DIR[z2][1], REV[zz2]);
		}
	}
	
	void random_generate(std::istream &inp_stream)
	{
		for (int i = 1; i <= h; i++)
			for (int j= 1; j <= w; j++)
				for (int k = 0; k < 8; k++)
					fill(i, j, k, 1);
		
		std::mt19937 mtgen(time(NULL));
		std::uniform_int_distribution<int> distz(0, 7);
		std::uniform_int_distribution<int> distx(1, h);
		std::uniform_int_distribution<int> disty(1, w);
		
		puts("指定随机密度（至多有多少格被设为墙）：");
		int d, x, y, z;
		inp_stream >> d;
		for (int i = 1; i <= d; i++)
		{
			x = distx(mtgen);
			y = disty(mtgen);
			z = distz(mtgen);
			fill(x, y, z, 0);
		}
	}
	
	void input(std::istream &inp_stream)
	{
		puts("输入格式：x y z，代表坐标 (x, y) 的房间的 z 方向有墙。");
		puts("其中 z 方向表如下：");
		puts("  5  6  7 ");
		puts("   ↖ ↑ ↗  ");
		puts(" 4 ← · → 0");
		puts("   ↙ ↓ ↘  ");
		puts("  3  2  1 ");
		
		int x, y, z;
		while (1)
		{
			puts("请输入（输入 -1 -1 -1 以结束）：");
			inp_stream >> x >> y >> z;
			if (x == -1 && y == -1)
			{
				puts("输入正常结束。");
				return;
			}
			fill(x, y, z, 1);
		}
	}
	
	void output(std::ostream &out_stream, bool with_path)
	{
		out_stream << "\nMaze:\n";
		
		if (with_path && path_list.size() == 0)
			out_stream << "----(Path do not exist)----\n";
		for (int i = 1;i <= h; i++)
		{
			for (int j = 1; j <= w; j++)
				out_stream << get(i, j, 5) << get(i, j, 6);
			out_stream << get(i, w, 7) << '\n';
			for (int j = 1; j <= w; j++)
				(with_path == 1) ? 
					out_stream << get(i, j, 4) << CHARSET[path[i][j]]:
					out_stream << get(i, j, 4) << ' ';
			out_stream << get(i, w, 0) << '\n';
		}
		for (int j = 1; j <= w; j++)
			out_stream << get(h, j, 3) << get(h, j, 2);
		out_stream << get(h, w, 1) << '\n';
	}
	
	bool DFS(int x, int y)
	{
		if (x == h && y == w)
		{
			path_list.push_back({x, y});
			return true;
		}
		
		for (int d = 0; d < 8; d++)
		{
			if (in(x + DIR[d][0], y + DIR[d][1]) && 
				(!vis[x + DIR[d][0]][y + DIR[d][1]]) && 
				get(x, y, d))
			{
				vis[x][y] = 1;
				if (DFS(x + DIR[d][0], y + DIR[d][1]))
				{
					path_list.push_back({x, y});
					path[x][y]=d + 1;
					return true;
				}
				vis[x][y] = 0;
			}
		}
		return false;
	}
	
	void SearchWithStack()
	{
		std::vector<std::pair<int, int>> stk;
		
	}
	
	void BFS()
	{
		
	}
};

void TestIO()
{
	Maze mz(4, 4);
	
	mz.input(cin);
	mz.output(cout, 1);
	cerr << "output ok.";
}

int main()
{
	// TestIO();
	
	Maze mz(5, 5);
	mz.random_generate(cin);
	mz.DFS(1, 1);
	mz.output(cout, 1);
	cerr << "output ok.";
}