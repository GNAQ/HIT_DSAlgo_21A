#include<bits/stdc++.h>
using namespace std;

int main()
{
	vector<int> vec;
	for (int i=1;i<=2000;i+=2)
	{
		vec.push_back(i);
		
	}
	
	srand(time(NULL));
	random_shuffle(vec.begin(), vec.end());
	
	freopen("data.in", "w", stdout);

	printf("%llu\n", vec.size());
	for (auto v: vec)
		printf("%d ", v);
	puts("");
	
	mt19937 mtgen(time(NULL));
	uniform_int_distribution<int> dist(1, 2000);
	
	puts("100");
	for (int i=1;i<=100;i++)
	{
		int w = dist(mtgen);
		while (w%2==0)
			w = dist(mtgen);
		printf("%d\n", w);
	}
	
}