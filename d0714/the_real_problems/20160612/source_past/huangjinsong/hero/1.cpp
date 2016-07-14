#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#define id(a,b,c) ((a-1)*m+b+(c?n*m:0))
using namespace std;
typedef long long LL;
inline int read()
{
	int x=0;bool f=0;char c=getchar();
	for (;c<'0'||c>'9';c=getchar()) f=c=='-'?1:0;
	for (;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	return f?-x:x;
}
const int N=10010,M=1000010;
const LL oo=0x3f3f3f3f3f3f3f3fll;
int n,m,K,S,S1,T,ll=1;
int head[N],to[M],next[M],fl[M],co[M],qu[N],pre[M];
LL flw,cst,dis[N];
bool vis[N];

inline void adde(int u,int v,int w,int c)
{
	to[++ll]=v;next[ll]=head[u];head[u]=ll;fl[ll]=w;co[ll]=c;
	to[++ll]=u;next[ll]=head[v];head[v]=ll;fl[ll]=0;co[ll]=-c;
}

bool spfa()
{
	memset(dis,0x3f,sizeof(LL)*(T+2));
	memset(vis,0,sizeof(bool)*(T+2));
	int l=0,r=1;
	dis[S]=0;qu[0]=S;vis[S]=1;
	while (l!=r)
	{
		int u=qu[l++];if (l==N) l=0;
		for (int i=head[u];i;i=next[i]) if (fl[i])
			if (dis[to[i]]>dis[u]+co[i])
			{
				dis[to[i]]=dis[u]+co[i];
				pre[to[i]]=i;
				if (!vis[to[i]]) 
				{
					vis[to[i]]=1;
					qu[r++]=to[i];if (r==N) r=0;
				}
			}
		vis[u]=0;
	}
	return dis[T]<oo;
}

void mcf()
{
	int f=0x3f3f3f3f;
	for (int i=pre[T];i;i=pre[to[i^1]])
		f=min(f,fl[i]);
	flw+=f;
	for (int i=pre[T];i;i=pre[to[i^1]])
		fl[i]-=f,fl[i^1]+=f,cst+=(LL)co[i]*f;
}

int main()
{
	n=read();m=read();K=read();
	S=n*m*2+1;S1=S+1;T=S+2;
	adde(S,S1,2,0);
	for (int i=1;i<=m;i++) adde(S1,id(1,i,0),1,0),adde(id(n,i,1),T,1,0);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			adde(id(i,j,0),id(i,j,1),1,read());
	for (int i=1;i<n;i++)
		for (int j=1;j<=m;j++)
			for (int k=1;k<=m;k++)
				adde(id(i,j,1),id(i+1,k,0),1,K*abs(j-k));
	while (spfa())
		mcf();
	cout<<cst<<endl;
	return 0;
}
