#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
#include<sstream>
using namespace std;
#define next next_
template<class T> inline bool ten(T &x,const T &y){return y<x?x=y,1:0;}
template<class T> inline bool rel(T &x,const T &y){return x<y?x=y,1:0;}
const int maxn=2005,inf=1000000005;
int N,K,C,ans;
int head[maxn],adj[maxn*2],c[maxn*2],next[maxn*2],tot;
int fa[maxn],siz[maxn];
int f[maxn][maxn],g[maxn];

void addedge(int u,int v,int w)
{tot++;adj[tot]=v;c[tot]=w;next[tot]=head[u];head[u]=tot;
tot++;adj[tot]=u;c[tot]=w;next[tot]=head[v];head[v]=tot;}

void init()
{
	tot=1;
	memset(head,0,N<<2);
	for(int u,v,w,i=1;i<N;i++)
		scanf("%d%d%d",&u,&v,&w),addedge(u,v,w);
}

void dp(int x)
{
	siz[x]=0;f[x][0]=0;
	for(int y,i=head[x];i;i=next[i])
		if((y=adj[i])!=fa[x])
		{
			fa[y]=x;
			dp(y);
			memset(g,63,siz[x]+siz[y]+1<<2);
			for(int a=0;a<=siz[x];a++)
				for(int b=0;b<=siz[y];b++)
					ten(g[a+b],f[x][a]+f[y][b]+(2-(b&1))*c[i]);
			memcpy(f[x],g,siz[x]+siz[y]+1<<2);
			siz[x]+=siz[y];
		}
	f[x][++siz[x]]=inf;
	for(int i=siz[x]-1;~i;i--)
		ten(f[x][i+1],f[x][i]);
}

int work()
{
	dp(0);
	int ans=inf;
	for(int i=0;i<=K&&i+i<=N;i++)
		ten(ans,f[0][i+i]+i*C);
	return ans;
}

int main()
{
	freopen("mzz.in","r",stdin);
	freopen("mzz.out","w",stdout);
	while(scanf("%d%d%d",&N,&K,&C)!=EOF)
	{
		init();
		printf("%d\n",work());
	}
	return 0;
}

