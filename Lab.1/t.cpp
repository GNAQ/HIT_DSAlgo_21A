#include <bits/stdc++.h>
using namespace std;

int main()
{
	int x = 7;
	
	x &= (~(1<<1));
	
	cout << x << endl;
}