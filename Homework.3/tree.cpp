/*
Date: 2021/10/20
Author: ������ (120L022004)
Compile Flags: --std=c++11
Environment: MinGW-w64 G++ 8.1.0
*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
using std::cin; using std::cout;
using std::cerr; using std::endl;

struct _Node
{
	_Node *lch, *rch;
	int id;
	
	_Node(){}
	_Node(int _id = 0) 
		: id(_id)
	{
		lch = rch = nullptr;
	}
};

// ����
void Input(_Node *u)
{
	int tmp;
	cerr << "������ " << u->id << " �Ž�������ӱ�ţ�0 ��ʾ�գ�:";
	cin >> tmp;
	if (tmp != 0)
	{
		if (u->lch == nullptr)
			u->lch = new _Node(tmp);
		else
			u->lch->id = tmp;
	}
	cerr << "������ " << u->id << " �Ž����Ҷ��ӱ�ţ�0 ��ʾ�գ�:";
	cin >> tmp;
	if (tmp != 0)
	{
		if (u->rch == nullptr)
			u->rch = new _Node(tmp);
		else
			u->rch->id = tmp;
	}
	if (u->lch != nullptr) Input(u->lch);
	if (u->rch != nullptr) Input(u->rch);
}

void PreOrder_NoRec(_Node *u, std::vector<int> &seq)
{
	struct StackNode
	{ 
		_Node* f; 
		int st;
	};
	std::vector<StackNode> stk;
	int head = 0; 
	
	stk.push_back({u, 0});
	while (head >= 0)
	{
		_Node *u = stk[head].f;
		if (stk[head].st == 0)
		{
			cout << "Node " << u->id << '\n';
			seq.push_back(u->id);
			stk[head].st++;
			if (u->lch != nullptr)
			{
				head++;
				stk.push_back({u->lch, 0});
			}
		}
		if (stk[head].st == 1)
		{
			stk[head].st++;
			if (u->rch != nullptr)
			{
				head++;
				stk.push_back({u->rch, 0});
			}
		}
		if (stk[head].st == 2)
		{
			head--;
			stk.pop_back();
		}
	}
}

void MidOrder_NoRec(_Node *u, std::vector<int> &seq)
{
	struct StackNode
	{
		_Node* f; 
		int st;
	};
	std::vector<StackNode> stk;
	int head = 0; 
	
	stk.push_back({u, 0});
	while (head >= 0)
	{
		_Node *u = stk[head].f;
		
		if (stk[head].st == 0)
		{
			stk[head].st++;
			if (u->lch != nullptr)
				stk[++head] = {u->lch, 0};
		}
		if (stk[head].st == 1)
		{
			stk[head].st++;
			cout << "Node " << u->id << '\n';
			seq.push_back(u->id);
			if (u->rch != nullptr)
				stk[++head] = {u->rch, 0};
		}
		if (stk[head].st == 2)
			head--;
	}
}

void PostOrder_NoRec(_Node *u, std::vector<int> &seq)
{
	struct StackNode
	{ 
		_Node* f; 
		int st;
	};
	std::vector<StackNode> stk;
	int head = 0; 
	
	stk.push_back({u, 0});
	while (head >= 0)
	{
		_Node *u = stk[head].f;
		if (stk[head].st == 0)
		{
			stk[head].st++;
			if (u->lch != nullptr)
				stk[++head] = {u->lch, 0};
		}
		if (stk[head].st == 1)
		{
			stk[head].st++;
			if (u->rch != nullptr)
				stk[++head] = {u->rch, 0};
		}
		if (stk[head].st == 2)
		{
			cout << "Node " << u->id << '\n';
			seq.push_back(u->id);
			head--;
		}
	}
}

// ���һ������ǰ��
void Output(_Node *u)
{
	cout << "Node ID " << u->id << '\n';
	cout << "Childs: " << (u->lch == nullptr ? -1 : u->lch->id)
		 << " | " << (u->rch == nullptr ? -1 : u->rch->id) << '\n';
	
	if (u->lch != nullptr) Output(u->lch);
	if (u->rch != nullptr) Output(u->rch);
}

void PreOrder(_Node *u, std::vector<int> &seq)
{
	cout << "Node " << u->id << '\n';
	seq.push_back(u->id);
	if (u->lch != nullptr)
		PreOrder(u->lch, seq);
	if (u->rch != nullptr)
		PreOrder(u->rch, seq);
}

void MidOrder(_Node *u, std::vector<int> &seq)
{
	if (u->lch != nullptr)
		MidOrder(u->lch, seq);
	cout << "Node " << u->id << '\n';
	seq.push_back(u->id);
	if (u->rch != nullptr)
		MidOrder(u->rch, seq);
}

void PostOrder(_Node *u, std::vector<int> &seq)
{
	if (u->lch != nullptr)
		PostOrder(u->lch, seq);
	if (u->rch != nullptr)
		PostOrder(u->rch, seq);
	cout << "Node " << u->id << '\n';
	seq.push_back(u->id);
}

void LevOrder(_Node *u, std::vector<int> &seq)
{
	std::vector<_Node*> que;
	int head = 0, tail = -1;
	
	tail++; que.push_back(u);
	while (head <= tail)
	{
		_Node *u = que[head++];
		cout << "Node " << u->id << '\n';
		seq.push_back(u->id);
		if (u->lch != nullptr)
		{
			tail++;
			que.push_back(u->lch);
		}
		if (u->rch != nullptr)
		{
			tail++;
			que.push_back(u->rch);
		}
	}
}

int CaclWidth(_Node *u)
{
	struct QueNode
	{
		_Node *f;
		int lv;
	};
	std::vector<QueNode> que;
	int head = 0, tail = -1;
	
	tail++; que.push_back({u, 0});
	while (head <= tail)
	{
		_Node *u = que[head].f;
		int lvl  = que[head++].lv;
		if (u->lch != nullptr)
		{
			tail++;
			que.push_back({u->lch, lvl + 1});
		}
		if (u->rch != nullptr)
		{
			tail++;
			que.push_back({u->rch, lvl + 1});
		}
	}
	
	int ans = 0;
	for (int i = 0; i < (int)que.size(); i++)
	{
		int j = i;
		while (j < (int)que.size() - 1 && que[j + 1].lv == que[i].lv)
			j++;
		ans = std::max(ans, j - i + 1);
		i = j;
	}
	return ans;
}

bool IsComplete(_Node *u)
{
	struct QueNode
	{
		_Node *f;
		int lv;
	};
	std::vector<QueNode> que;
	int head = 0, tail = -1;
	
	if (u->lch == nullptr && u->rch == nullptr)
		return true;
	
	tail++; que.push_back({u, 0});
	while (head <= tail)
	{
		_Node *u = que[head].f;
		int lvl  = que[head++].lv;
		if (u->lch != nullptr)
		{
			tail++;
			que.push_back({u->lch, lvl + 1});
		}
		if (u->rch != nullptr)
		{
			tail++;
			que.push_back({u->rch, lvl + 1});
		}
	}
	
	std::vector<int> ap;
	for (int i = 0; i < (int)que.size(); i++)
	{
		if (que[i].f->lch == nullptr && que[i].f->rch == nullptr)
			ap.push_back(0);
		else if (que[i].f->lch != nullptr && que[i].f->rch != nullptr)
			ap.push_back(2);
		else if (que[i].f->lch != nullptr && que[i].f->rch == nullptr)
			ap.push_back(1);
		else
			return false;
	}
	
	int R2 = 0, L0 = ap.size() - 1;
	if (ap[R2] != 2) R2--;
	else 
		while (R2 < (int)ap.size() - 1 && ap[R2 + 1] == 2) R2++;
	
	if (ap[L0] != 0) L0++;
	else
		while (L0 > 0 && ap[L0 - 1] == 0) L0--;
	
	if (L0 == R2 + 1)
		return true;
	if (L0 == R2 + 2 && ap[R2 + 1] == 1)
		return true;
	return false;
}

/*
Test Sample:
2
3
0
4
5
6
0
0
0
0
7
8
0
0
0
0
*/

int main(void)
{
	_Node *root = new _Node(1);
	
	Input(root);
	
	std::vector<int> r1, r2, r3, r4, r5;
	cout << "���������" << '\n';
	PreOrder(root, r1);
	cout << "���������" << '\n';
	MidOrder(root, r2);
	cout << "���������" << '\n';
	PostOrder(root, r3);
	cout << "���������" << '\n';
	LevOrder(root, r4);
	cout << "�ǵݹ����������" << '\n';
	PreOrder_NoRec(root, r5);
	
	cout << "�Ƿ�Ϊ��ȫ��������" << '\n';
	cout << IsComplete(root) << endl;
	cout << "���Ŀ�ȣ�" << '\n';
	cout << CaclWidth(root) << endl;
	return 0;
}