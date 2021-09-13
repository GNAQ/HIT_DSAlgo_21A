// Use C++ 11 or higher and -O2 as compile options
#include <bits/stdc++.h>
using namespace std;


int main()
{
	mt19937 mtgen(time(NULL));
	uniform_int_distribution<int> dist(INT_MIN / 10000, INT_MAX / 10000);
	
	int n;
	cin >> n;
	
	ofstream os;
	try
	{
		os.open("data1.in", ios_base::out);
		for (int i = 1; i <= n; i++)
		{
			os << dist(mtgen) << " \n"[i == n];
		}
	}
	catch (exception ex)
	{
		cerr << "File write error." << endl;
	}
}