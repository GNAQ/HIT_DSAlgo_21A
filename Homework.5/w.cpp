// Author: GNAQ 王子恺 120L022004
// Date: 2021/11/21
// 这周末打算法竞赛忙过头了，没怎么写作业
// 比较赶，求体谅

#include <bits/stdc++.h>
using std::cin; using std::cout;
using std::cerr; using std::endl;

template<typename DataT>
int Binary_Search(DataT *arr, int bg, int ed, DataT targ, int &timecost)
{
	timecost = 0;
	while (bg <= ed)
	{
		timecost++;
		int mid = (bg + ed) / 2;
		if (arr[mid] == targ)
		{
			return mid;
		}
		if (arr[mid] < targ)
		{
			bg = mid + 1;
		}
		else
		{
			ed = mid - 1;
		}
	}
	return -1;
}

template<typename DataT>
struct TNode
{
	DataT val;
	TNode *lch, *rch, *fa;
	
	TNode() {}
	TNode(DataT _val, TNode *_lch = nullptr, TNode *_rch = nullptr, TNode *_fa = nullptr)
		: val(_val), lch(_lch), rch(_rch), fa(_fa)  { }
};

template<typename DataT>
class BST
{
private:
	TNode<DataT> *rt;
	int siz;
public:

	BST()
	{
		rt = nullptr;
		siz = 0;
	}

	TNode<DataT> *GetRt()
	{
		return rt;
	}
	
	TNode<DataT>* Insert(DataT v)
	{
		if (!siz)
		{
			rt = new TNode<DataT>(v);
			siz++;
			return rt;
		}
		TNode<DataT> *u = rt;
		while (1)
		{
			if (v < u->val)
			{
				if (u->lch == nullptr)
				{
					u->lch = new TNode<DataT>(v);
					u->lch->fa = u;
					return u->lch;
				}
				else
				{
					u = u->lch;
				}
			}
			else
			{
				if (u->rch == nullptr)
				{
					u->rch = new TNode<DataT>(v);
					u->rch->fa = u;
					return u->rch;
				}
				else
				{
					u = u->rch;
				}
			}
		}
		siz++;
		return nullptr;
	}
	
	TNode<DataT>* Find(DataT v, int &timecost)
	{
		timecost = 0;
		TNode<DataT> *u = rt;
		while (u != nullptr)
		{
			timecost++;
			if (u->val == v)
				return u;
			else if (v < u->val)
				u = u->lch;
			else 
				u = u->rch;
		}
		return u;
	}
	
	void Delete(DataT v)
	{
		TNode<DataT> *u = this->Find(v);
		if (u == nullptr) return;
		
		siz--;
		if (siz == 0) 
		{
			rt = nullptr;
			return;
		}
		TNode<DataT> *u2 = u;
		
		while (u2->rch != nullptr) u2 = u2->rch;
		if (u == u2)
		{
			if (u->fa->lch == u)
				u->fa->lch = nullptr;
			else
				u->fa->rch = nullptr;
		}
		else
		{
			if (u->fa->lch == u)
				u->fa->lch = u2;
			else
				u->fa->rch = u2;
			u2->fa = u->fa;
		}
	}
	
	void Sort(std::vector<DataT> &rslt, TNode<DataT> *u)
	{
		if (u->lch != nullptr)
			Sort(rslt, u->lch);
		rslt.push_back(u->val);
		if (u->rch != nullptr)
			Sort(rslt, u->rch);
	}
};

int main()
{
	std::string srcfile;
	cin >> srcfile;
	std::ifstream ifile(srcfile);
	
	BST<int> tree;
	
	int n, tmp;
	ifile >> n;
	for (int i = 1; i <= n; i++)
	{
		ifile >> tmp;
		tree.Insert(tmp);
	}
	
	cout << "BST Search: " << endl;
	
	int m, cnt;
	long long avg_cnt = 0;
	std::vector<int> ops;
	ifile >> m;
	for (int i = 1; i <= m; i++)
	{
		ifile >> tmp;
		ops.push_back(tmp);
		
		TNode<int> *rslt = tree.Find(tmp, cnt);
		cout << tmp << " found in " << cnt << " operations\n";
		avg_cnt += cnt;
	}
	cout << "Average operations: " << (double)avg_cnt / (double)m << endl;
	
	// ------------------------------------
	
	cout << endl << endl << "Binary Search: " << endl;
	
	int *arr = new int[n];
	std::vector<int> vec;
	tree.Sort(vec, tree.GetRt());
	for (int i = 0; i < vec.size(); i++)
		arr[i + 1] = vec[i];
	
	avg_cnt = 0;
	for (int i = 1; i <= m; i++)
	{
		int rslt = Binary_Search(arr, 1, n, ops[i - 1], cnt);
		
		cout << tmp << " found in " << cnt << " operations\n";
		avg_cnt += cnt;
	}
	cout << "Average operations: " << (double)avg_cnt / (double)m << endl;
	
	return 0;
}