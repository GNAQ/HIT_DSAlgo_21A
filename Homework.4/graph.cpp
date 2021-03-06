#include <bits/stdc++.h>
using std::cin; using std::cout;
using std::cerr; using std::endl;

class Graph
{
public:
	virtual void Ins(int, int) = 0;
	virtual std::vector<int> GetEdges(int) = 0;
	virtual int GetNext(int, int) = 0;
	virtual bool IsConn(int, int) = 0;
	virtual int vsize() = 0;
	virtual void clear() = 0;
};

class GraphMat : public Graph
{
private:
	int **mat;
	int ncnt;
	int *id, *od;
	
	inline void Check(int id)
	{
		if (id < 1 || id > ncnt)
			throw std::out_of_range("vertex index out of bound");
	}
public:
	GraphMat() {}
	GraphMat(int _ncnt)
	{
		ncnt = _ncnt;
		mat = new int*[_ncnt + 2];
		for (int i = 0; i < _ncnt + 2; i++)
			mat[i] = new int[_ncnt + 2];
		for (int i = 0; i < _ncnt + 2; i++)
			for (int j = 0; j < _ncnt + 2; j++)
				mat[i][j] = 0;
		id = new int[_ncnt + 2];
		od = new int[_ncnt + 2];
		for (int i = 0; i < _ncnt + 2; i++)
			od[i] = id[i] = 0;
	}
	~GraphMat()
	{
		for (int i = 0; i < ncnt + 2; i++)
			delete[] mat[i];
		delete[] mat;
		delete[] id;
		delete[] od;
	}
	
	// Insert an edge of (u -> v)
	void Ins(int u, int v)
	{
		Check(u); Check(v);
		mat[u][v] = 1;
		id[v]++; od[u]++;
	}
	
	std::vector<int> GetEdges(int u)
	{
		Check(u);
		std::vector<int> ret;
		for (int i = 1; i <= ncnt; i++)
			if (mat[u][i] && i != u)
				ret.push_back(i);
		return ret;
	}
	
	int GetNext(int u, int v)
	{
		Check(u); Check(v);
		for (int i = v + 1; i <= ncnt; i++)
			if (mat[u][i] && i != u)
				return i;
		return 0;
	}
	
	bool IsConn(int u, int v)
	{
		Check(u); Check(v);
		return mat[u][v];
	}
	
	int vsize()
	{
		return ncnt;
	}
	
	void clear()
	{
		for (int i = 0; i < ncnt + 2; i++)
		{
			for (int j = 0; j < ncnt + 2; j++)
				mat[i][j] = 0;
			id[i] = od[i] = 0;
		}
	}
	
	int InDeg(int u)
	{
		Check(u);
		return id[u];
	}
	
	int OutDeg(int u)
	{
		Check(u);
		return od[u];
	}
};


class GraphList : public Graph
{
private:
	struct _Ed { int pre, to; };
	std::vector<_Ed> edge;
	std::vector<int> hd, deg;
	int ncnt, tail;
	
	inline void Check(int id)
	{
		if (id < 1 || id > ncnt)
			throw std::out_of_range("vertex index out of bound");
	}
public:
	GraphList() {}
	GraphList(int _ncnt)
	{
		edge.push_back({0, 0});
		hd.resize(_ncnt + 2, 0);
		deg.resize(_ncnt + 2, 0);
		tail = 0;
		ncnt = _ncnt;
	}
	
	void Ins(int u, int v)
	{
		Check(u); Check(v);
		tail++;
		edge.push_back({hd[u], v});
		hd[u] = tail;
		deg[u]++; deg[v]++;
	}
	
	std::vector<int> GetEdges(int u)
	{
		Check(u);
		std::vector<int> ret;
		for (int v = hd[u]; v; v = edge[v].pre)
			ret.push_back(edge[v].to);
		return ret;
	}
	
	int GetNext(int u, int v)
	{
		Check(u);
		if (v == 0) 
			return hd[u];
		v = edge[v].pre;
		return v;
	}
	
	bool IsConn(int u, int v)
	{
		Check(u); Check(v);
		for (int i = hd[u]; i; i = edge[i].pre)
			if (edge[i].to == v)
				return true;
		return false;
	}
	
	int vsize()
	{
		return ncnt;
	}
	
	void clear()
	{
		std::fill_n(hd.begin(), ncnt + 2, 0);
		std::fill_n(deg.begin(), ncnt + 2, 0);
		edge.clear();
		edge.shrink_to_fit();
		edge.push_back({0, 0});
		tail = 0;
	}
	
	int Deg(int u)
	{
		Check(u);
		return deg[u];
	}
};

// ?????? src ??? dest; 
// ??????????????? GraphMat ????????? GraphList
// ???????????????
// ??????????????????????????? Graph ????????????
void Conv(Graph &src, Graph &dest)
{
	dest.clear();
	int ncnt = src.vsize();
	for (int i = 1; i <= ncnt; i++)
	{
		std::vector<int> v = src.GetEdges(i);
		for (auto j: v)
			dest.Ins(i, j);
	}
}

void Output(Graph &now, std::ostream &os)
{
	os << "Graph with " << now.vsize() << " vertices: \n";
	for (int i = 1; i <= now.vsize(); i++)
	{
		os << "Vertex " << i << " : ";
		std::vector<int> tv = now.GetEdges(i);
		for (auto v: tv)
			os << v << " ";
		os << "\n";
	}
}

// ??????????????????STree ??????????????????Sseq ??????????????????
// ????????????????????????????????????????????????
std::vector<bool> dvis;
void DFS(int u, Graph &G, 
	Graph &STree, std::vector<int> &Sseq)
{
	dvis[u] = true;
	std::vector<int> tv = G.GetEdges(u);
	for (auto v: tv)
	{
		if (dvis[v] == false)
		{
			Sseq.push_back(v);
			STree.Ins(u, v);
			STree.Ins(v, u);
			DFS(v, G, STree, Sseq);
		}
	}
}

void DFS_Recursive(
	Graph &G, Graph &STree, std::vector<int> &Sseq)
{
	dvis.clear();
	dvis.shrink_to_fit();
	dvis.resize(G.vsize() + 2, 0);
	
	STree.clear();
	for (int i = 1; i <= G.vsize(); i++)
		if (dvis[i] == false)
		{
			Sseq.push_back(i);
			DFS(i, G, STree, Sseq);
		}
}

void DFS_NonRecursive(
	Graph &G, Graph &STree, std::vector<int> &Sseq)
{
	dvis.clear();
	dvis.shrink_to_fit();
	dvis.resize(G.vsize() + 2, 0);
	struct _Nd { int st, u; std::vector<int> vt; };
	
	for (int i = 1; i <= G.vsize(); i++)
		if (dvis[i] == false)
		{
			std::vector<_Nd> stk(G.vsize() + 10, _Nd());
			int head = 0;
			stk[++head] = {0, i, G.GetEdges(i)};
			while (head > 0)
			{
				_Nd cur = stk[head];
				dvis[cur.u] = true;
				for (; cur.st < (int)cur.vt.size(); cur.st++)
					if (dvis[cur.vt[cur.st]] == false)
					{
						stk[++head] = {0, cur.vt[cur.st], 
							G.GetEdges(cur.vt[cur.st])};
						STree.Ins(cur.u, cur.vt[cur.st]);
						STree.Ins(cur.vt[cur.st], cur.u);
						Sseq.push_back(cur.vt[cur.st]);
					}
			}
		}
}

void BFS(Graph &G, Graph &STree, std::vector<int> &Sseq)
{
	dvis.clear();
	dvis.shrink_to_fit();
	dvis.resize(G.vsize() + 2, 0);
	
	int ncnt = G.vsize();
	std::vector<int> que(ncnt * 2 + 10, 0);
	int head = 0, tail = -1;
	
	for (int i = 1; i <= ncnt; i++)
		if (dvis[i] == false)
		{
			Sseq.push_back(i);
			que[++tail] = i;
			dvis[i] = true;
			while (head <= tail)
			{
				int u = que[head++];
				std::vector<int> tv = G.GetEdges(u);
				for (auto v: tv) 
					if (dvis[v] == false)
					{
						que[++tail] = v;
						dvis[v] = true;
						STree.Ins(u, v);
						STree.Ins(v, u);
						Sseq.push_back(v);
					}
			}
		}
}

int main()
{
	int n, m;
	std::ifstream ifile("data.in");
	std::ofstream ofile("result.out");
	
	ifile >> n >> m;
	
	GraphMat A(n);
	GraphList B(n);
	
	int u, v;
	for (int i = 1; i <= m; i++)
	{
		ifile >> u >> v;
		A.Ins(u, v);
	}
	
	Conv(A, B);
	Output(B, ofile);
	
	GraphMat gentree(n);
	std::vector<int> srchseq;
	BFS(B, gentree, srchseq);
	
	for (auto v: srchseq)
		ofile << v << " ";
	ofile << '\n';
	Output(gentree, ofile);
	
	srchseq.clear();
	gentree.clear();
	DFS_Recursive(A, gentree, srchseq);
	
	for (auto v: srchseq)
		ofile << v << " ";
	ofile << '\n';
	Output(gentree, ofile);
	
}