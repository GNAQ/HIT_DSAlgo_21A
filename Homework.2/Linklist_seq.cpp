// At Peace.
// Author: GNAQ (120L022004)
// Date: 2021/08/18
// Compile Flags: --std=c++11 -O2

#include <bits/stdc++.h>
using std::cin; using std::cout; using std::cerr;

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
		if (p > lst)
			throw std::out_of_range("index out of range");
		for (unsigned i = lst; i >= p; i--)
			elm[i + 1] = elm[i];
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
			swap(elm[i], elm[lst - i]);
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

public:
	
	LinkList(){}
	LinkList(unsigned size, ElemTyp val)
	{
		Elements *ptr;
		begin = ptr = new Elements(val);
		while (size > 1)
		{
			size--;
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
	
	void insert(unsigned p, ElemTyp val)
	{
		Elements *ptr = begin, *tmp;
		if (ptr == nullptr)
			throw("Error: Empty list");
		for (unsigned i = 1; i <= p; i++)
		{
			if (ptr->r == nullptr)
				throw std::out_of_range("index out of range");
			ptr = ptr->r;
		}
		tmp = new Elements();
		tmp->r = ptr;
		tmp->val = val;
		tmp->l = ptr->l;
		tmp->l->r = tmp;
		ptr->l = tmp;
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
			delete ptr;
		}
		else if (ptr == lst)
		{
			lst = lst->l;
			delete ptr;
		}
		else
		{
			ptr->l->r = ptr->r;
			ptr->r->l = ptr->l;
			delete ptr;
		}
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
		for (unsigned i = 0; i <= lst; i++)
			while (i < lst && elm[i] == elm[i + 1])
				this->remove(i + 1);
	}
	
	// 3. 线性表“逆置”算法
	void reverse()
	{
		for (unsigned i = 0; i <= lst / 2; i++)
			swap(elm[i], elm[lst - i]);
	}
};

int main()
{
	SeqList<int> slist(10, 7);
	LinkList<std::string> qwq(20, "22");
	
	
}