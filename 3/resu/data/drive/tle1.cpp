#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> edges[50000];
int N;

int dist(int a,int b)
{
	return (b+N-a)%N;
}

int main()
{
	cin >> N;
	for(int i=0;i<N;i++)
	{
		edges[i].push_back((i+1)%N);
		edges[(i+1)%N].push_back(i);
	}
	int a,b;
	for(int i=0;i<N-3;i++)
	{
		cin >> a >> b;
		a--,b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	for(int i=0;i<N;i++)
		sort(edges[i].begin(),edges[i].end());
	int Q;
	int dest,aa,ab,ba,bb;
	int p;
	cin >> Q;
	for(int i=0;i<Q;i++)
	{
		cin >> a >> dest;
		a--,dest--;
		b = a;
		for(int k=0;;k++)
		{
			if(a==dest || b==dest)
			{
				cout << k << '\n';
				break;
			}
			p = upper_bound(edges[a].begin(),edges[a].end(),dest)-edges[a].begin();
			if(p>0)
				aa = edges[a][p-1];
			else
				aa = edges[a][edges[a].size()-1];
			if(p==edges[a].size()) p = 0;
			ab = edges[a][p];
			p = upper_bound(edges[b].begin(),edges[b].end(),dest)-edges[b].begin();
			if(p>0)
				ba = edges[b][p-1];
			else
				ba = edges[b][edges[b].size()-1];
			if(p==edges[b].size()) p = 0;
			bb = edges[b][p];
			a = aa;
			if(dist(a,dest) > dist(ba,dest))
				a = ba;
			b = ab;
			if(dist(dest,b) > dist(dest,bb))
				b = bb;
		}
	}
}
