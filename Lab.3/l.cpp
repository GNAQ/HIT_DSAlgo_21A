#include <bits/stdc++.h>
using std::cin; using std::cout;
using std::cerr; using std::endl;

struct Ed
{
	int pre, to, w;
};
struct Graph
{
	Ed *edge;
	int *hd;
	int hcnt;
	int nsiz, msiz;
	Graph()
	{
		hd = nullptr;
		edge = nullptr;
		hcnt = nsiz = msiz = 0;
	}
	Graph(int _n, int _m)
		: nsiz(_n), msiz(_m)
	{
		edge = new Ed[_n * 2 + 10];
		hd = new int[_n + 10];
		memset(hd, 0, sizeof(int) * (_n + 10));
		memset(edge, 0, sizeof(Ed) * (_n * 2 + 10));
		hcnt = 0;
	}
	
	~Graph()
	{
		delete[] edge;
		delete[] hd;
	}
	
	void Is(int u, int v, int w)
	{
		hcnt++;
		edge[hcnt].pre = hd[u];
		edge[hcnt].to = v;
		edge[hcnt].w = w;
		hd[u] = hcnt;
	}
	
	void Ins(int u, int v, int w)
	{
		Is(u, v, w); 
		Is(v, u, w);
	}
};

template<typename ElemTyp>
struct Heap
{
	ElemTyp *hp;
	int hsiz;
	
	Heap() {}
	Heap(int s)
	{
		hsiz = 0;
		hp = new ElemTyp[s + 10];
		memset(hp, 0, sizeof(ElemTyp) * (s + 10));
	}
	
	~Heap() 
	{
		delete[] hp;
	}
	
	void Add(ElemTyp v)
	{
		hp[++hsiz] = v;
		int u = hsiz;
		while (u > 1)
		{
			if (hp[u / 2] < hp[u]) 
				break;
			std::swap(hp[u / 2], hp[u]);
			u /= 2;
		}
	}
	
	void Del()
	{
		hp[1] = hp[hsiz--];
		int u = 1, v = u * 2;
		while (v <= hsiz)
		{
			if (v < hsiz && hp[v + 1] < hp[v]) v++;
			if (hp[v] > hp[u]) break;
			std::swap(hp[u], hp[v]);
			u = v; v = u * 2;
		}
	}
};

struct _Nd
{
	int id, dis;
	bool operator < (const _Nd &b) const
		{ return this->dis < b.dis; }
};
void Dijkstra(const Graph &G, int s, int *dis, int *pre_v)
{
	int ncnt = G.nsiz;
	bool *vis = new bool[ncnt + 10];
	memset(vis, 0, sizeof(bool) * (ncnt + 10));
	memset(dis, 0x3f, sizeof(int) * (ncnt + 2));
	memset(pre_v, 0, sizeof(int) * (ncnt + 2));
	Heap<_Nd> h(ncnt * 2 + 10);
	
	dis[s] = 0;
	h.Add({s, 0});
	
	while (h.hsiz>=1)
	{
		_Nd tmp = h.hp[1];
		h.Del();
		if (vis[tmp.id]) 
			continue;
		vis[tmp.id] = 1;
		for (int v = G.hd[tmp.id]; v; v = G.edge[v].pre)
		{
			int vt = G.edge[v].to;
			if (dis[vt] > dis[tmp.id] + G.edge[v].w)
			{
				dis[vt] = dis[tmp.id] + G.edge[v].w;
				pre_v[vt] = tmp.id;
				_Nd newnd = {vt, dis[vt]};
				h.Add(newnd);
			}
		}
	}
}

void Floyd(const Graph &G, int **dis, int **pre_v)
{
	int ncnt = G.nsiz;
	memset(dis, 0x3f, sizeof(int) * (ncnt + 2) * (ncnt + 2));

	for (int i = 1; i <= ncnt; i++)
		for (int v = G.hd[i]; v; v = G.edge[v].pre)
			dis[i][G.edge[v].to] = G.edge[v].w;
	
	for (int k = 1; k <= ncnt; k++)
		for (int i = 1; i <= ncnt; i++)
			for (int j = 1; j <= ncnt; j++)
				if (dis[i][j] < dis[i][k] + dis[k][j])
				{
					dis[i][j] = dis[i][k] + dis[k][j];
					pre_v[i][j] = k;
				}
}

void Dij_Output(int u, int *pre_v, std::vector<int> &ve)
{
	ve.push_back(u);
	if (!pre_v[u]) return;
	Dij_Output(pre_v[u], pre_v, ve);
}

std::vector<int> Floyd_Output(int u, int v, int **pre_v)
{
	if (u==v)
		return std::vector<int> {u};
	std::vector<int> r1, r2;
	r1 = Floyd_Output(u, pre_v[u][v], pre_v);
	r2 = Floyd_Output(pre_v[u][v], v, pre_v);
	for (auto i: r2) r1.push_back(i);
	return r1;
}

int main()
{
	Graph G;
	int *dis = new int[100];
	int *pre_v = new int[100];
	
	int n, m;
	int u, v, w;
	std::ifstream ifile("data.in");
	
	ifile >> n >> m;
	G.msiz = m; G.nsiz = n;
	for (int i = 1; i <= m; i++)
	{
		ifile >> u >> v >> w;
		G.Ins(u, v, w);
	}
	Dijkstra(G, 1, dis, pre_v);
	
}