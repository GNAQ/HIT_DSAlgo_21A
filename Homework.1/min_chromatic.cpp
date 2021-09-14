// Author: GNAQ (HIT-120L022004)
// Date: 2021/09/14 21:00

// 对任意交叉路口的"交通管制问题"
// 本质是求一般（简单）图上的一个最小点染色（Minimum Vertex Coloring）
// 这个问题是 reduection from 3-SAT 问题的，后者是我们熟知的 NP-Complete 问题
// 所以目前求解这个问题的最优时间复杂度是 O(n*2^n) 的，该问题的优化形式也是 NP-Hard 的，计数形式到达了 #P-Complete。
// 该贪心算法很容易在若干图下得到差距较大的结果，例如皇冠图、完全二分图和正则图等。

// Note: compile with C++11 and -O2 option
#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::cerr;

int Greedy(const int n, const int colorId, 
	const std::vector< std::vector<int> > &edges, 
	std::vector<int> &color)
{
	std::set<int> vset;
	for (int i = 1; i <= n; i++)  
	{
		if (color[i] == 0)
		{
			bool ok = true;
			for (auto v: vset)
				if (edges[i][v])
					ok = false;
			if (ok)
				vset.insert(i);
		}
	}
	for (auto u: vset) 
		color[u] = colorId;
		
	return vset.size();
}

// Input format:
// first line two integers n and m standing for vertex number and edge number of graph
// then m lines with each line two number u, v standing for an edge (u, v) in graph
// vertex are numbered from 1 to n.

int main()
{
	int n, m, u, v;
	// 也可以用邻接表存边，此处根据伪代码，发现邻接矩阵比较方便
	std::vector< std::vector<int> > edges(n, std::vector<int>(n)); 
	std::vector<int> color(n, 0);
	
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> u >> v;
		edges[u][v] = edges[v][u] = 0;
	}
	
	int n2 = n, ans = 0;
	while (n2 > 0)
	{
		n2 -= Greedy(n, ans + 1, edges, color);
		ans++;
	}
	
	cout << ans << std::endl;
	return 0;
}