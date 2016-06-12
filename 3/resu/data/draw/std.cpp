#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <cassert>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;

#define SIZE(x) (int((x).size()))
#define rep(i,l,r) for (int i=(l); i<=(r); i++)
#define repd(i,r,l) for (int i=(r); i>=(l); i--)
#define rept(i,c) for (typeof((c).begin()) i=(c).begin(); i!=(c).end(); i++)

#ifndef ONLINE_JUDGE
#define debug(x) { cerr<<#x<<" = "<<(x)<<endl; }
#else
#define debug(x) {}
#endif

#define maxn 32010
#define maxC 801
#define base 400

int _c[maxn][maxC];
int *c[maxn];

vector< pair<int,int> > e[maxn];

int p[maxn], w[maxn], o[maxn], md[maxn];

void dfs(int cur, int pre, int d)
{
	p[cur]=pre; w[cur]=d; c[cur][0]++; md[cur]=0;
	rept(it,e[cur])
		if (it->first!=pre)
		{
			dfs(it->first,cur,it->second);
			md[cur]=max(md[cur],md[it->first]+1);
			rep(k,-md[it->first],md[it->first])
				c[cur][k-1]+=c[it->first][k];
		}
}


void modify(int x)
{
	int b=-1, y=p[x];
	while (y!=-1)
	{
		rep(k,-md[x],md[x])
		{
			c[y][k+b]-=c[x][k];
			c[y][k+b+2]+=c[x][k];
		}
		b+=o[y];
		y=p[y];
	}
	o[x]=1;
}

int _cs[maxC], *cs;

void solve(int x, int y, int b)
{
	if (x==-1) return;
	//y is child of x to exclude
	rep(k,-md[x],md[x])
	{
		int z=k+b;
		if (-base<=z && z<=base) 
			cs[z]+=c[x][k]-c[y][k-o[y]];
	}
	solve(p[x],x,b+o[x]);
}

LL fprize, fway;

void doit(int x)
{
	modify(x);
	rep(k,-md[x],md[x]) cs[k]=0;
	solve(p[x],x,0);
	rep(k,-md[x],md[x])
	{
		LL way=LL(c[x][k])*cs[-k];
		fprize+=way*w[x];
		fway+=way;
		//if (way) cout<<x<<" "<<w[x]<<" "<<k<<" "<<way<<endl;
	}
}

pair<int,int> z[maxn];

void lemon()
{
	rep(i,1,maxn-1) c[i]=_c[i]+base;
	cs=_cs+base;
	int n; scanf("%d",&n);
	rep(i,1,n-1)
	{
		int x,y,z; scanf("%d%d%d",&x,&y,&z);
		e[x].push_back(make_pair(y,z));
		e[y].push_back(make_pair(x,z));
	}
	dfs(1,-1,-1);
	assert(md[1]<=base);
	rep(i,1,n) o[i]=-1;
	
	fprize=0; fway=0;
	rep(i,2,n) z[i]=make_pair(w[i],i);
	sort(z+2,z+n+1);
	rep(i,2,n) doit(z[i].second);
    cout << fprize << endl;
}

int main()
{
	ios::sync_with_stdio(true);
	lemon();
	return 0;
}
