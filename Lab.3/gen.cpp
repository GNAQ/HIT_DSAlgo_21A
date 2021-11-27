#include <bits/stdc++.h>
using namespace std;

bool vis[100][100];

int main()
{
	freopen("data.in", "w", stdout);
	
	int n = 10;
	int m = 16;
	
	printf("%d %d\n", n, m);
	
	mt19937 mtgen(time(NULL));
	uniform_int_distribution<int> dist(1, n);
	uniform_int_distribution<int> distW(1, 6);
	int u, v, w;
	for (int i=1;i<=m;i++)
	{
		w = distW(mtgen);
		u = dist(mtgen);
		v = dist(mtgen);
		while (u == v || vis[u][v])
		{
			u = dist(mtgen);
			v = dist(mtgen);
		}
		vis[u][v] = vis[v][u] = 1;
		printf("%d %d %d\n", u, v, w);
	}
}