// At Peace.
// Author: GNAQ (120L022004)
// Date: 2021/09/18
// Compile Flags: --std=c++11 -O2

#include <bits/stdc++.h>
using std::cin; using std::cout; using std::cerr; using std::endl;

// Interface Base
template<typename ElemTypBase>
class ListBase
{
private:
	// ElemTypBase *elm;
	
public:
	virtual ElemTypBase operator[] (unsigned p) = 0;
	virtual void remove(unsigned p) = 0;
	virtual void insert(unsigned p, ElemTypBase val) = 0;
	virtual unsigned find(ElemTypBase val) = 0;
	virtual ElemTypBase previous(unsigned p) = 0;
	virtual ElemTypBase next(unsigned p) = 0;
	virtual void clear() = 0;
	virtual ElemTypBase front() = 0;
	virtual ElemTypBase end() = 0;
	virtual unsigned size() = 0;
};

template<typename ElemTyp>
class SeqList : public ListBase<ElemTyp>
{
private:
	ElemTyp *elm;
	int lst, max_size;
	
public:
	SeqList() 
	{
		lst = -1;
		elm = nullptr;
		max_size = 0;
	}
	SeqList(unsigned size)
	{
		lst = -1;
		elm = new int[size];
		max_size = size;
	}
	SeqList(unsigned size, ElemTyp initVal)
	{
		lst = -1;
		elm = new int[size];
		std::fill_n(elm, size, initVal);
		max_size = size;
	}
	
	~SeqList()
	{
		delete[] elm;
		lst = -1;
	}
	
	ElemTyp operator[] (unsigned p) // this is retrive
	{
		if (p > lst) 
			throw std::out_of_range("index out of range");
		return elm[p];
	}
	
	unsigned size()
	{
		return lst + 1;
	}
	
	void remove(unsigned p)
	{
		if (p > lst) 
			throw std::out_of_range("index out of range");
		for (unsigned i = p + 1; i <= lst; i++)
			elm[i - 1] = elm[i];
		elm[lst] = ElemTyp();
		lst--;
	}
	
	void insert(unsigned p, ElemTyp val)
	{
		if (lst == max_size - 1 || max_size < 1)
			throw("Memory overflow");
		if (p > lst + 1)
			throw std::out_of_range("index out of range");
		for (unsigned i = lst + 1; i > p; i--)
			elm[i] = elm[i - 1];
		lst++;
		elm[p] = val;
		return;
	}
	
	unsigned find(ElemTyp val)
	{
		for (unsigned i = 0; i <= lst; i++)
			if (elm[i] == val)
				return i;
		return -1;
	}
	
	ElemTyp previous(unsigned p)
	{
		if (p > lst || p < 1) 
			throw std::out_of_range("index out of range");
		return elm[p - 1];
	}
	
	ElemTyp next(unsigned p)
	{
		if (p > lst - 1) 
			throw std::out_of_range("index out of range");
		return elm[p + 1];
	}
	
	// Make this link list a nullptr list
	void clear()
	{
		lst = -1;
		max_size = 0;
		delete[] elm;
	}
	
	ElemTyp front()
	{
		if (lst < 0)
			throw("Error: Empty list");
		return elm[0];
	}
	
	ElemTyp end()
	{
		if (lst < 0)
			throw("Error: Empty list");
		return elm[lst];
	}
	
	// 2. 对于已排好序的线性表，删除所有重复元素的算法。
	void unique()
	{
		for (unsigned i = 0; i <= lst; i++)
			while (i < lst && elm[i] == elm[i + 1])
				this->remove(i + 1);
	}
	
	// 3. 线性表“逆置”算法
	void reverse()
	{
		for (unsigned i = 0; i <= lst / 2; i++)
			std::swap(elm[i], elm[lst - i]);
	}
	
	// 4. 线性表循环左移/右移k位的算法。
	// dir =  1 -> 右移
	// dir = -1 -> 左移
	void turnK(unsigned k, int dir)
	{
		std::vector<ElemTyp> tvec;
		if (!k) return;
		k %= lst;
		
		if (dir == 1)
		{
			for (unsigned i = lst - k + 1; i <= lst; i++)
				tvec.push_back(elm[i]);
			for (unsigned i = 0; i <= lst - k; i++)
				tvec.push_back(elm[i]);
		}
		else
		{
			for (unsigned i = k; i <= lst; i++)
				tvec.push_back(elm[i]);
			for (unsigned i = 0; i < k; i++)
				tvec.push_back(elm[i]);
		}
		for (unsigned i = 0; i <= lst; i++)
			elm[i] = tvec[i];
	}
	
	// 5. 合并两个已排好序的线性表的算法。
	// sorted by "<" (may overrided)
	friend SeqList<ElemTyp> list_merge
		(const SeqList<ElemTyp> *a, const SeqList<ElemTyp> *b)
	{
		SeqList<ElemTyp> rslt(a->max_size + b->max_size, ElemTyp());
		while (a->lst >= 0 && b->lst >= 0)
		{
			if ((*a)[0] < (*b)[0])
			{
				rslt.insert((*a)[0]);
				a->remove(0);
			}
			else
			{
				rslt.insert((*b)[0]);
				b->remove(0);
			}
		}
		while (a->lst >= 0)
		{
			rslt.insert((*a)[0]);
			a->remove(0);
		}
		while (b->lst >= 0)
		{
			rslt.insert((*b)[0]);
			b->remove(0);
		}
		return rslt;
	}
};

template<typename ElemTyp>
class LinkList : public ListBase<ElemTyp>
{
private:
	struct Elements
	{
		Elements *l, *r;
		ElemTyp val;
		
		Elements() 
			: l(nullptr), r(nullptr), val(ElemTyp())
		{
		}
		Elements(const ElemTyp &_inval)
			: l(nullptr), r(nullptr), val(_inval)
		{
		}
	} *begin, *lst;
	unsigned inner_size;

public:
	
	LinkList(){}
	LinkList(unsigned _size, ElemTyp val)
	{
		Elements *ptr;
		begin = ptr = new Elements(val);
		inner_size = _size;
		while (_size > 1)
		{
			_size--;
			Elements *tmp = new Elements(val);
			ptr->r = tmp;
			tmp->l = ptr;
			ptr = tmp;
		}
		lst = ptr;
	}
	
	ElemTyp operator[] (unsigned p)
	{
		Elements *ptr = begin;
		if (ptr == nullptr)
			throw("Error: Empty list");
		for (unsigned i = 1; i <= p; i++)
		{
			if (ptr->r == nullptr) 
				throw std::out_of_range("index out of range");
			ptr = ptr->r;
		}
		return ptr->val;
	}
	
	unsigned size()
	{
		return inner_size;
	}
	
	void insert(unsigned p, ElemTyp val)
	{
		Elements *ptr = begin, *tmp;
		if (ptr == nullptr)
			throw("Error: Empty list");
		for (unsigned i = 1; i <= p; i++)
		{
			if (ptr->r == nullptr)
			{
				if (i != p)
					throw std::out_of_range("index out of range");
				else
				{
					ptr->r = new Elements();
					ptr->r->l = ptr;
					ptr = ptr->r;
					ptr->val = val;
					inner_size++;
					lst = ptr;
					return;
				}
			}
			ptr = ptr->r;
		}
		tmp = new Elements();
		tmp->r = ptr;
		tmp->val = val;
		tmp->l = ptr->l;
		tmp->l->r = tmp;
		ptr->l = tmp;
		inner_size++;
	}
	
	void remove(unsigned p)
	{
		Elements *ptr = begin;
		if (ptr == nullptr) 
			throw("Error: Empty List");
		for (unsigned i = 1; i <= p; i++)
		{
			if (ptr->r == nullptr)
				throw std::out_of_range("index out of range");
			ptr = ptr->r;
		}
		if (ptr == begin)
		{
			begin = begin->r;
			begin->l = nullptr;
			delete ptr;
		}
		else if (ptr == lst)
		{
			lst = lst->l;
			lst->r = nullptr;
			delete ptr;
		}
		else
		{
			ptr->l->r = ptr->r;
			ptr->r->l = ptr->l;
			delete ptr;
		}
		inner_size--;
	}
	
	unsigned find(ElemTyp val)
	{
		unsigned rslt = 0;
		Elements *ptr = begin;
		if (ptr == nullptr) 
			throw("Error: Empty list");
		do
		{
			if (ptr->val == val)
				return rslt;
			ptr = ptr->r;
			rslt++;
		} while (ptr != lst);
		return -1;
	}
	
	ElemTyp front()
	{
		if (begin == nullptr)
			throw("Error: Empty list");
		return begin->val;
	}
	
	ElemTyp end()
	{
		if (lst == nullptr)
			throw("Error: Empty list");
		return lst->val;
	}
	
	void clear()
	{
		Elements *ptr = begin;
		do
		{
			ptr = ptr->r;
			delete ptr->l;
		} while (ptr != lst);
		delete lst;
		begin = lst = nullptr;
		inner_size = 0;
	}
	
	ElemTyp previous(unsigned p)
	{
		if (!p) 
			throw std::out_of_range("index out of range");
		Elements *ptr = begin;
		for (unsigned i = 1; i < p; i++)
		{
			if (ptr->r == nullptr)
				throw std::out_of_range("index out of range");
			ptr = ptr->r;
		}
		return ptr->val;
	}
	
	ElemTyp next(unsigned p)
	{
		Elements *ptr = begin;
		if (ptr == nullptr)
			throw("Error: Empty list");
		for (unsigned i = 0; i <= p; i++)
		{
			if (ptr->r == nullptr)
				throw std::out_of_range("index out of range");
			ptr = ptr->r;
		}
		return ptr->val;
	}
	
	// 2. 对于已排好序的线性表，删除所有重复元素的算法。
	void unique()
	{
		Elements *ptr = begin;
		if (ptr == nullptr)
			throw("Error: Empty list");
		for (unsigned i = 0; ptr != lst; i++)
		{
			while (ptr->r != nullptr && ptr->val == ptr->r->val)
				remove(i + 1);
			ptr = ptr->r;
		}
	}
	
	// 3. 线性表“逆置”算法
	void reverse()
	{
		Elements *ptr = begin;
		if (ptr == nullptr)
			throw("Error: Empty list");
		for (unsigned i = 0; ptr != lst; i++)
		{
			swap(ptr->l, ptr->r);
			ptr = ptr->l;
		}
	}
	
	// 4. 线性表循环左移/右移k位的算法。
	// dir =  1 -> 右移
	// dir = -1 -> 左移
	void turnK(unsigned k, int dir)
	{
		if (begin == nullptr) 
			throw("Error: Empty list");
		Elements *b, *e;
		for (unsigned i = 1; i <= k; i++)
		{
			b = begin;
			e = lst;
			
			if (dir == 1)
			{
				begin = e;
				begin->r = b;
				b->l = begin;
				lst = e->l;
				begin->l = nullptr;
				lst->r = nullptr;
			}
			else
			{
				lst = b;
				lst->l = e;
				e->r = lst;
				begin = b->r;
				lst->r = nullptr;
				begin->l = nullptr;
			}
		}
	}
	
	// 5. 合并两个已排好序的线性表的算法。
	// sorted by "<" (may overrided)
	friend LinkList<ElemTyp> list_merge
		(const LinkList<ElemTyp> *a, const LinkList<ElemTyp> *b)
	{
		LinkList<ElemTyp> rslt(a->max_size + b->max_size, ElemTyp());
		while (a->lst >= 0 && b->lst >= 0)
		{
			if ((*a)[0] < (*b)[0])
			{
				rslt.insert((*a)[0]);
				a->remove(0);
			}
			else
			{
				rslt.insert((*b)[0]);
				b->remove(0);
			}
		}
		while (a->lst >= 0)
		{
			rslt.insert((*a)[0]);
			a->remove(0);
		}
		while (b->lst >= 0)
		{
			rslt.insert((*b)[0]);
			b->remove(0);
		}
		return rslt;
	}
};

int main()
{
	std::ifstream infile;
	infile.open("testdata.in");
	
	if (!infile.is_open())
	{
		cout << "Error: couldn't read test data file";
		return 0;
	}
	
	int iVal1, siz1, siz2; 
	std::string iVal2;
	
	infile >> siz1 >> iVal1;
	SeqList<int> slist(siz1, iVal1);
	
	for (int i = 0; i < siz1; i++)
	{
		int val, pos;
		infile >> pos >> val;
		slist.insert(pos, val);
	}
	
	cout << "Initial Status: " << endl;
	for (int i = 0; i < slist.size(); i++)
		cout << slist[i] << " \n"[i == slist.size() - 1];
	
	slist.reverse();
	
	cout << "Reversed:" << endl;
	for (int i = 0; i < slist.size(); i++)
		cout << slist[i] << " \n"[i == slist.size() - 1];
	
	infile >> siz2 >> iVal2;
	LinkList<std::string> llist(siz2, iVal2);
	
	for (int i = 0; i < siz2; i++)
	{
		int pos; std::string val;
		infile >> pos >> val;
		llist.insert(pos, val);
	}
	
	cout << "Initial Status: " << endl;
	for (int i = 0; i < llist.size(); i++)
		cout << llist[i] << " \n"[i == llist.size() - 1];
	
	llist.turnK(2, 1);
	
	cout << "Turned 3 times left:" << endl;
	for (int i = 0; i < llist.size(); i++)
		cout << llist[i] << " \n"[i == llist.size() - 1];
}