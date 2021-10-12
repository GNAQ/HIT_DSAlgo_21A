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

const std::string CHARSET[10] 
	= {" ", "→", "↘", "↓", "↙", "←", "↖", "↑", "↗", "×"};

class Maze
{
private:
	int h, w;
	std::vector<std::vector<int>> brd;
	std::vector<std::vector<int>> path;
	std::vector<std::vector<int>> vis;
	std::vector<std::pair<int, int>> path_list;
	int min_step;
	
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
	
public:
	Maze(int height, int width) 
		: h(height), w(width) 
	{
		if (h * w > 2500)
			throw("Maze oversized.");
		brd.resize(height + 2, std::vector<int>(width + 2, 0));
		vis.resize(height + 2, std::vector<int>(width + 2, 0));
		path.resize(height + 2, std::vector<int>(width + 2, 0));
		path[h][w] = 9;
		min_step = -1;
	}
	
	inline void reset()
	{
		std::fill_n(vis.begin(), h + 2, std::vector<int> (w + 2, 0));
		std::fill_n(path.begin(), h + 2, std::vector<int> (w + 2, 0));
		path[h][w] = 9;
		path_list.clear();
	}
	
	inline bool get(int x, int y, int z)
	{
		if (!in(x, y, z))
			throw std::out_of_range(
				"Error: get() method out of index range.");
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
			throw std::out_of_range(
				"Error: fill targer (x, y, z) out of range.");
		
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
	
	void random_generate(std::istream &in_st)
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
		in_st >> d;
		for (int i = 1; i <= d; i++)
		{
			x = distx(mtgen);
			y = disty(mtgen);
			z = distz(mtgen);
			fill(x, y, z, 0);
		}
	}
	
	void input(std::istream &in_st)
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
			in_st >> x >> y >> z;
			if (x == -1 && y == -1)
			{
				puts("输入正常结束。");
				return;
			}
			fill(x, y, z, 1);
		}
	}
	
	void output(std::ostream &os, bool with_path)
	{
		if (with_path && path_list.size() == 0)
			os << "----(Path do not exist)----\n";
		if (min_step != -1)
			os << "Minimum Steps: " << min_step << '\n';
		
		os << "\nMaze:\n";
		for (int i = 1;i <= h; i++)
		{
			for (int j = 1; j <= w; j++)
				os << get(i, j, 5) << get(i, j, 6);
			os << get(i, w, 7) << '\n';
			for (int j = 1; j <= w; j++)
				(with_path == 1) ? 
					os << get(i, j, 4) << CHARSET[path[i][j]]:
					os << get(i, j, 4) << ' ';
			os << get(i, w, 0) << '\n';
		}
		for (int j = 1; j <= w; j++)
			os << get(h, j, 3) << get(h, j, 2);
		os << get(h, w, 1) << '\n';
		
		if (with_path)
		{
			for (int i = path_list.size() - 1; i >= 0; i--)
				os << '(' << path_list[i].first << ", " 
				   << path_list[i].second << ") ";
			os << endl;
		}
	}
	
	bool DFS(int x, int y)
	{
		vis[x][y] = 1;
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
				if (DFS(x + DIR[d][0], y + DIR[d][1]))
				{
					path_list.push_back({x, y});
					path[x][y] = d + 1;
					return true;
				}
			}
		}
		vis[x][y] = 0;
		return false;
	}
	
	void SearchWithStack()
	{
		struct _NR
		{
			int x, y, d;
			_NR() {}
			_NR(int inX, int inY, int inD)
				: x(inX), y(inY), d(inD)
			{}
		};
		std::vector<_NR> stk;
		int head = 1;
		stk.push_back(_NR(0, 0, 0));
		stk.push_back(_NR(1, 1, 0));
		vis[1][1] = 1;
		
		while (head >= 1)
		{
			_NR &tmp = stk[head];
			
			if (tmp.x == h && tmp.y == w)
			{
				for (int i = 1; i < head; i++)
				{
					path_list.push_back({stk[i].x, stk[i].y});
					path[stk[i].x][stk[i].y] = stk[i].d + 1;
				}
				path_list.push_back({h, w});
				break;
			}
			
			for (;tmp.d < 8; tmp.d++)
				if (in(tmp.x + DIR[tmp.d][0], tmp.y + DIR[tmp.d][1]) && 
					(!vis[tmp.x + DIR[tmp.d][0]][tmp.y + DIR[tmp.d][1]]) && 
					get(tmp.x, tmp.y, tmp.d))
				{
					vis[tmp.x + DIR[tmp.d][0]][tmp.y + DIR[tmp.d][1]] = 1;
					head++;
					stk.push_back(
						_NR(tmp.x + DIR[tmp.d][0], tmp.y + DIR[tmp.d][1], 0)
						);
					break;
				}
			
			if (stk[head].d >= 8)
			{
				vis[stk[head].x][stk[head].y] = 0;
				head--;
				stk.pop_back();
				stk[head].d++;
			}
		}
	}
	
	void BFS()
	{
		#define fst first
		#define snd second
		std::vector<std::pair<int, int>> que(8 * w * h, {0, 0});
		int head = 1, tail = 0;
		bool ans = 0;
		
		que[1] = {1, 1};
		tail++;
		vis[1][1] = -1;
		
		while (head <= tail)
		{
			std::pair<int, int> tmp = que[head++];
			
			if (tmp.fst == h && tmp.snd == w)
			{
				ans = 1;
				break;
			}
			
			for (int d = 0; d < 8; d++)
			{
				if (in(tmp.fst + DIR[d][0], tmp.snd + DIR[d][1]) && 
					vis[tmp.fst + DIR[d][0]][tmp.snd + DIR[d][1]] == 0 && 
					get(tmp.fst, tmp.snd, d))
				{
					std::pair<int, int> tmp2 = 
						{tmp.fst + DIR[d][0], tmp.snd + DIR[d][1]};
					vis[tmp2.fst][tmp2.snd] = head - 1;
					que[++tail] = tmp2;
				}
			}
		}
		
		if (!ans) return;
		
		min_step = 0;
		path_list.push_back({h, w});
		int tmp = vis[h][w], nx = h, ny = w;
		while (tmp != -1)
		{
			int x = que[tmp].fst, y = que[tmp].snd, d = 0;
			path_list.push_back({x, y});
			min_step++;
			
			for (; d < 8; d++)
				if (x + DIR[d][0] == nx && y + DIR[d][1] == ny)
				{
					path[x][y] = d + 1;
					break;
				}
			
			tmp = vis[x][y];
			nx = x; ny = y;
		}
		
		#undef fst
		#undef snd
	}
};

void TestRun(Maze &mz, std::ostream &os)
{
	mz.DFS(1, 1);
	mz.output(os, 1);
	
	mz.SearchWithStack();
	mz.output(os, 1);
	mz.reset();
	
	mz.BFS();
	mz.output(os, 1);
}

int main()
{
	int height, width;
	std::ifstream ifs;
	
	ifs.open("data.in");
	ifs >> height >> width;
	
	Maze mz(height, width);
	mz.random_generate(ifs);
	TestRun(mz, cout);
	
	return 0;
}