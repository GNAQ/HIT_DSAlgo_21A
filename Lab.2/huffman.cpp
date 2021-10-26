#include <bits/stdc++.h>
typedef long long ll;
using std::cin; using std::cout;
using std::cerr; using std::endl;

namespace BitIO
{
	const int BITC = 8;
	char buf;
	int st;
	void WriteBits(const std::string &src, 
		std::ofstream &ofile)
	{
		buf = 1;
		st = 0;
		for (auto c: src)
		{
			if (c != '0' && c != '1')
				throw("given string is not bit stream");
			buf = (buf << 1) | (c == '1');
			st++;
			if (st == 7)
			{
				ofile << buf;
				st = 0;
				buf = 1; 
			}
		}
		if (st)
		{
			buf = buf | (1 << st);
			ofile << buf;
		}
		buf = 0; st = 0;
		ofile << endl;
	}
	
	void ReadBits(std::string &dest, std::ifstream &ifile)
	{
		buf = 0;
		while (ifile >> buf)
		{
			int i = 7;
			while (!(buf & (1 << i)))
				i--;
			for (i--; i >= 0; i--)
				dest.push_back('0' + ((buf >> i) & 1));
		}
		buf = 0;
	}
};

template<typename DataTyp>
struct HTNode
{
	HTNode *lch, *rch;
	int id, val;
	DataTyp data;
	std::string encode;
	HTNode() {}
	HTNode(DataTyp _data, int _id, int _val,
		HTNode *_lch = nullptr, HTNode *_rch = nullptr)
		: data(_data), id(_id), val(_val), 
		  lch(_lch), rch(_rch) {}
};

template<typename DataTyp>
class Huffman_Tree
{
typedef std::pair<DataTyp, int> pair_dt_int;
typedef HTNode<DataTyp> HTNode_D;

private:
	HTNode_D *root;
	int _siz;

public:
	std::vector<std::pair<DataTyp, std::string>> Table;
	
	Huffman_Tree() 
		: _siz(0), root(nullptr) {}
	
	inline int Size() { return _siz; }
	
	HTNode_D* GetRoot() { return root; }
	
	void Build(std::vector<pair_dt_int> &src)
	{
		// spj
		if (src.size() == 1)
		{
			root = new HTNode_D(
				src[0].first, ++_siz, src[0].second);
			return;
		}
		//sort initial data
		std::sort(src.begin(), src.end(), 
			[](const pair_dt_int &a, const pair_dt_int &b) 
			{ return a.second > b.second; });
		// assign nodes
		int tot = src.size();
		std::vector<HTNode_D*> pvec(tot, nullptr);
		for (int i = tot - 1; i >= 0; i--)
		{
			pvec[i] = new HTNode_D(
				src[i].first, ++_siz, src[i].second);
		}
		// build tree 
		for (int i = tot - 1; i >= 1; i--)
		{
			HTNode_D *lt = pvec[i], 
				*rt = pvec[i - 1];
			
			HTNode_D *nroot = new HTNode_D(
					DataTyp(), ++_siz, lt->val + rt->val, lt, rt);
			
			// insert new node
			int nval = lt->val + rt->val;
			int pos = 0;
			for (;;pos++)
				if (src[pos].second < nval)
					break;
			
			tot -= 1;
			for (int j = tot - 2; j >= pos; j--)
			{
				src[j + 1] = src[j];
				pvec[j + 1] = pvec[j];
			}
			pvec[pos] = nroot;
			src[pos] = {DataTyp(), nval};
		}
		root = pvec[0];
	}
	
	void CalcEncode(HTNode_D *u, std::string nows)
	{
		if (u->lch == nullptr && u->rch == nullptr)
		{
			u->encode = nows;
			Table.push_back({u->data, nows});
			return;
		}
		if (u->lch != nullptr)
			CalcEncode(u->lch, nows + '0');
		if (u->rch != nullptr)
			CalcEncode(u->rch, nows + '1');
	}
};

void Encode(const std::string &text, 
	const std::vector<std::pair<char, std::string>> &table,
	std::string &rslt)
{
	for (auto c: text)
		for (int i = 0; i < table.size(); i++)
			if (table[i].first == c)
				rslt += table[i].second;
}

void Decode(std::string text, 
	Huffman_Tree<char> &T,
	std::string &rslt)
{
	HTNode<char> *u = T.GetRoot();
	for (auto c: text)
	{
		if (c == '0')
			u = u->lch;
		else
			u = u->rch;
		if (u->encode.size())
		{
			rslt += u->data;
			u = T.GetRoot();
		}
	}
}

double CalcZipRate(
	const std::string &src,
	const std::string &enc)
{
	return (double)enc.size() / (double)(src.size() * 8);
}

void Read(std::string file,
	std::string &deststr,
	std::vector<std::pair<char, int>> &dest)
{
	std::ifstream ifs(file);
	std::vector<int> cnt(140, 0);
	std::vector<char> inp;
	
	std::string istr;
	while (getline(ifs, istr)) 
	{
		deststr += istr;
		deststr.push_back('\n');
	}
	for (auto c: deststr)
	{
		cnt[c]++;
		inp.push_back(c);
	}
	
	std::sort(inp.begin(), inp.end());
	std::vector<char>::iterator endp = 
		std::unique(inp.begin(), inp.end());
	
	for (auto i = inp.begin(); i != endp; i++)
		dest.push_back({*i, cnt[*i]});
}

int main()
{
	// Read-in article
	std::vector<std::pair<char, int>> srcdata;
	std::string srcstr;
	Read("art2.in", srcstr, srcdata);
	
	// Build Huffman Tree 
	Huffman_Tree<char> ht;
	ht.Build(srcdata);
	ht.CalcEncode(ht.GetRoot(), std::string ());
	std::vector<std::pair<char, std::string>> &tb = ht.Table;
	
	// Encode source article
	std::string encstr;
	Encode(srcstr, tb, encstr);
	
	// Write Into Bitstream
	std::ofstream ofile;
	ofile.open("data.enc");
	BitIO::WriteBits(encstr, ofile);
	
	// Output zip rate
	cout << "Compression Rate: " 
		 << CalcZipRate(srcstr, encstr) 
		 << endl;
	
	// Read from binary file
	std::string finstr;
	std::ifstream ifile;
	ifile.open("data.enc");
	BitIO::ReadBits(finstr, ifile);
	
	// Decode string from file
	std::string decstr;
	Decode(finstr, ht, decstr);
	
	cout << "--- Decoded article: ---" << endl;
	cout << decstr << endl;
}