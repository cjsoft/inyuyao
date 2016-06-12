#include <string>
#include <vector>
#include <map>
#include <list>
#include <iterator>
#include <cassert>
#include <set>
#include <queue>
#include <iostream>
#include <sstream>
#include <stack>
#include <deque>
#include <cmath>
#include <memory.h>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <utility>
#include <time.h>
using namespace std;
 
#define FOR(i, a, b) for(int i=(a);i<(b);i++)
#define RFOR(i, b, a) for(int i=(b)-1;i>=(a);--i)
#define FILL(A,value) memset(A,value,sizeof(A))
 
#define ALL(V) V.begin(), V.end()
#define SZ(V) (int)V.size()
#define PB push_back
#define MP make_pair
#define Pi 3.14159265358979
#define x0 ikjnrmthklmnt
#define y0 lkrjhkltr
#define y1 ewrgrg
 
typedef long long Int;
typedef unsigned long long UInt;
typedef vector<int> VI;
typedef pair<int, int> PII;
typedef pair<Int, Int> PLL;
typedef pair<double, double> PDD;

const int INF = 1000000000;
const int BASE = 1000000000;
const int MAX = 50007;
const int MAXV = 1000;
const int MAXE = 100000;
const int ADD = 1000000;
const Int MOD = 1000000007;
const int CNT = 60;
 
const double eps = 1e-8;

VI g[MAX];
int d[MAX];
int q[MAX];
int clr[MAX];

void bfs(int v)
{
	d[v] = 0;
	int L = 0;
	int R = 0;
	q[R++] = v;
	while (L < R)
	{
		int v = q[L++];
		FOR(i,0,g[v].size())
		{
			int to = g[v][i];
			if (d[to] == INF)
			{
				d[to] = d[v] + 1;
				q[R++] = to;
			}
		}
	}
}

VI A[MAX * 47];
vector<PII> E[MAX * 47];
vector<pair<PII, int> > Q[MAX * 47];
int cnt = 0;
int res[MAX * 2];


void f(int id)
{

	if (Q[id].size() == 0) return;
	
	if (E[id].size() == 0)
	{
		FOR(i,0,Q[id].size())
		{
			if (Q[id][i].first.first == Q[id][i].first.second)
				res[Q[id][i].second] = 0;
			else
				res[Q[id][i].second] = 1;
		}
		return;
	}	
	
	PII p = E[id][rand() % E[id].size()];
	int cl = 0;
	FOR(i,0,A[id].size())
	{
		if (A[id][i] == p.first || A[id][i] == p.second)
		{
			clr[A[id][i]] = 2;
			cl ^= 1;
		}
		else
		{
			clr[A[id][i]] = cl;
		}
	}
	FOR(i,0,A[id].size())
	{
		g[A[id][i]].push_back(A[id][(i + 1) % A[id].size()]);
		g[A[id][(i + 1) % A[id].size()]].push_back(A[id][i]);
	}
	
	FOR(i,0,E[id].size())
	{
		g[E[id][i].first].push_back(E[id][i].second);
		g[E[id][i].second].push_back(E[id][i].first);
	}
	
	bfs(p.first);
	FOR(i,0,Q[id].size())
	{
		int u = Q[id][i].first.first;
		int v = Q[id][i].first.second;
		res[Q[id][i].second] = min(res[Q[id][i].second] , d[u] + d[v]);
	}
	FOR(i,0,A[id].size())
	{
		d[A[id][i]] = INF;
	}
	bfs(p.second);
	FOR(i,0,Q[id].size())
	{
		int u = Q[id][i].first.first;
		int v = Q[id][i].first.second;
		res[Q[id][i].second] = min(res[Q[id][i].second] , d[u] + d[v]);
	}
	FOR(i,0,A[id].size())
	{
		d[A[id][i]] = INF;
	}
	
	FOR(i,0,A[id].size())
	{
		if (clr[A[id][i]] >= 1)
		{
			A[cnt + 1].push_back(A[id][i]);
		}
	}
	RFOR(i,A[id].size(),0)
	{
		A[cnt].push_back(A[id][i]);
		if (clr[A[id][i]] == 2) break;
	}
	reverse(ALL(A[cnt]));
	FOR(i,0,A[id].size())
	{
		A[cnt].push_back(A[id][i]);
		if (clr[A[id][i]] == 2) break;
	}
	
	FOR(i,0,E[id].size())
	{
		if (clr[E[id][i].first] == 0 || clr[E[id][i].second] == 0)
		{
			E[cnt].push_back(E[id][i]);
		}
	}
	FOR(i,0,E[id].size())
	{
		if (clr[E[id][i].first] == 1 || clr[E[id][i].second] == 1)
		{
			E[cnt + 1].push_back(E[id][i]);
		}
	}
	
	FOR(i,0,Q[id].size())
	{
		if (clr[Q[id][i].first.first] == clr[Q[id][i].first.second] && clr[Q[id][i].first.first] != 2)
		{
			Q[cnt + clr[Q[id][i].first.first]].push_back(Q[id][i]);
		}
	}
	
	
	FOR(i,0,A[id].size())
	{
		clr[A[id][i]] = 0;
		g[A[id][i]].clear();
	}
	
	int ll = cnt;
	int rr = cnt + 1;
	cnt += 2;
	
	{
		VI aaa;
		aaa.swap(A[id]);
		vector<PII> eee;
		eee.swap(E[id]);
		vector<pair<PII, int> > qqq;
		qqq.swap(Q[id]);
	}
	
	f(ll);
	f(rr);
}

int main()
{
	
	int n;
	cin >> n;
	FOR(i,0,n)
	{
		A[0].push_back(i);
		d[i] = INF;
	}
	FOR(i,0,n - 3)
	{
		int a , b;
		cin >> a >> b;
		--a;--b;
		E[0].push_back(MP(a, b));
	}
	int q;
	cin >> q;
	FOR(i,0,q)
	{
		int a , b;
		scanf("%d%d" , &a , &b);
		--a;--b;
		Q[0].push_back(MP(MP(a , b) , i));
		res[i] = INF;
	}
	++cnt;
	
	f(0);
	
	FOR(i,0,q)
	{
		printf("%d\n" , res[i]);
	}
	
	return 0;
}
