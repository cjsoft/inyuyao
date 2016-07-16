#include <cmath>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#define mp make_pair
#define fi first
#define se second

using namespace std;

typedef pair<int,int> PII;
const int MAXN=100005;
const int INF=1000000000;

struct Point {
	int x,y,num;
	friend bool operator < (const Point &a,const Point &b)
	{
		if (a.x!=b.x) return a.x<b.x;
		return a.y<b.y;
	}
} pnt[MAXN];

struct E{
	int a,b,w;
	E(void){}
	E(int _a,int _b,int _w):a(_a),b(_b),w(_w){}
	friend bool operator < (const E &a,const E &b)
	{
		return a.w<b.w;
	}
}e[MAXN*4];
int en;

struct G{
	int to,next,d;
}g[MAXN*2];
int gn,start[MAXN];

inline void Add(int a,int b,int d)
{
	gn++,g[gn].to=b,g[gn].d=d,g[gn].next=start[a],start[a]=gn;
}

int n,m;
int fa[MAXN];
int ffa[20][MAXN];
int dis[20][MAXN];
int a[MAXN],b[MAXN];
PII c[MAXN];
int Log[MAXN];
int dep[MAXN];

inline void Update(int x,PII v)
{
	for (int i=x;i<=n;i+=i&(-i)) c[i]=min(c[i],v);
}

inline PII Query(int x)
{
	PII res=mp(INF,-1);
	for (int i=x;i;i-=i&(-i)) res=min(res,c[i]);
	return res;
}

int getfa(int x)
{
	if (fa[x]!=x) fa[x]=getfa(fa[x]);
	return fa[x];
}

void merge(int x,int y)
{
	fa[getfa(x)]=getfa(y);
}

inline int LCA(int p,int q)
{
	if (dep[p]<dep[q]) swap(p,q);
	int x=dep[p]-dep[q];
	for (int i=0;i<=Log[x];i++)
		if (x&(1<<i)) p=ffa[i][p];
	for (int i=Log[n];i>=0;i--)
		if (ffa[i][p]!=ffa[i][q]) p=ffa[i][p],q=ffa[i][q];
	if (p==q) return p;
	return ffa[0][p];
}

inline int Query(int p,int q)
{
	int x=dep[p]-dep[q];
	int res=0;
	for (int i=0;i<=Log[x];i++)
		if (x&(1<<i)) res=max(res,dis[i][p]),p=ffa[i][p];
	return res;
}

void Init()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&pnt[i].x,&pnt[i].y);
		pnt[i].num=i;
	}
}

void BuildMST()
{
	for (int dir=1;dir<=4;dir++)
	{
		if (dir==2||dir==4)
			for (int i=1;i<=n;i++) swap(pnt[i].x,pnt[i].y);
		if (dir==3)
			for (int i=1;i<=n;i++) pnt[i].x=-pnt[i].x;
		sort(pnt+1,pnt+n+1);
		for (int i=1;i<=n;i++) a[i]=b[i]=pnt[i].x-pnt[i].y;
		sort(b+1,b+n+1);
		int nq=unique(b+1,b+n+1)-(b+1);
		for (int i=1;i<=n;i++)
		{
			a[i]=lower_bound(b+1,b+nq+1,a[i])-b;
			c[i]=mp(INF,-1);
		}
		for (int i=n;i;i--)
		{
			int now=Query(a[i]).se;
			if (now!=-1) e[++en]=E(pnt[i].num,pnt[now].num,pnt[now].x+pnt[now].y-pnt[i].x-pnt[i].y);
			Update(a[i],mp(pnt[i].x+pnt[i].y,i));
		}
	}
	for (int i=1;i<=n;i++) fa[i]=i;
	sort(e+1,e+en+1);
	for (int i=1;i<=en;i++)
	{
		if (getfa(e[i].a)==getfa(e[i].b)) continue;
		merge(e[i].a,e[i].b);
		// printf("     %d %d\n", e[i].a, e[i].b);
		Add(e[i].a,e[i].b,e[i].w);
		Add(e[i].b,e[i].a,e[i].w);
	}
}

void BuildTree()
{
	static int qu[MAXN];
	static bool vis[MAXN];
	int head=0,tail=1;
	qu[0]=1;
	vis[1]=true;
	while (head!=tail)
	{
		int p=qu[head++];
		for (int i=start[p];i;i=g[i].next)
		{
			int v=g[i].to,d=g[i].d;
			if (vis[v]) continue;
			vis[v]=true;
			dep[v]=dep[p]+1;
			dis[0][v]=d;
			ffa[0][v]=p;
			qu[tail++]=v;
		}
	}
	Log[0]=-1;
	for (int i=1;i<=n;i++) Log[i]=Log[i>>1]+1;
	for (int i=1;i<=Log[n];i++)
		for (int j=1;j<=n;j++)
		{
			ffa[i][j]=ffa[i-1][ffa[i-1][j]];
			dis[i][j]=max(dis[i-1][j],dis[i-1][ffa[i-1][j]]);
		}
}

void Solve()
{
	scanf("%d",&m);
	while (m--)
	{
		int p,q,lca;
		scanf("%d%d",&p,&q);
		lca=LCA(p,q);
		printf("%d\n",max(Query(p,lca),Query(q,lca)));
	}
}

int main()
{
	freopen ("plan.in","r",stdin);
	// freopen ("plan.out","w",stdout);
	Init();
	BuildMST();
	BuildTree();
	Solve();
	return 0;
}
