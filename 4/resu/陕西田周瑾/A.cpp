#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<queue>
using namespace std;
struct node{
	int v;int w;int next;
}edge[100002];
queue<int>q;
const int mod=1e9+7;
int tot,n,head[5005],m;
long long dis[5005];
int vis[5005],t;
void addedge(int u,int v,int w)
{
	tot++;
	edge[tot].v=v;
	edge[tot].w=w;
	edge[tot].next=head[u];
	head[u]=tot;
}
long long spfa(int id)
{
	for (int i=1;i<=n;i++)
	dis[i]=1e18+8;
	q.push(1);
	dis[1]=0;
	while(!q.empty())
	{
		int now=q.front();q.pop();
		vis[now]=0;
		for (int i=head[now];i!=0;i=edge[i].next)
		{
			int v=edge[i].v;
			if (dis[v]>dis[now]+edge[i].w)
			{
				dis[v]=dis[now]+edge[i].w;
				if (vis[v]!=id)
				{
					vis[v]=id;
					q.push(v);
				}
			}
		}
	}
	long long cnt=0;
	for (int i=1;i<=n;i++)
	{
		cnt=cnt+dis[i];
	}
	return cnt;
}
int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	tot=1;
	scanf("%d%d%d",&n,&m,&t);
	for (int i=1,x,y,z;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		addedge(x,y,z);
		addedge(y,x,z);
	}
	long long p1=m*t;
	long long p2=n*t;
	if (p1<=1000000&&p2<=1000000)
	{
		long long ans=0;
		for (int i=0;i<=t;i++)
		{
			ans+=spfa(i+1);
			ans%=mod;
			for (int j=1;j<=tot;j++)
			edge[j].w++;
		}
		printf("%lld\n",ans);
		return 0;
	}
	else
	{
		long long tmp1=spfa(1);
		for (int i=1;i<=tot;i++)
		edge[i].w+=t;		
		long long tmp2=spfa(t);
		if ((tmp2-tmp1)%t==0)
		{
			long long ans=((tmp1+tmp2)*(t+1)/2)%mod;
			printf("%lld\n",ans);
		}

	}
}
