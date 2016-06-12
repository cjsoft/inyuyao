#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<queue>
using namespace std;
struct node{
	int v;int next;
}edge[100002];
queue<int>s;
int tot,n,head[5005],q,dis[5005],vis[5005];
void addedge(int u,int v)
{
	tot++;
	edge[tot].v=v;
	edge[tot].next=head[u];
	head[u]=tot;
}
void bfs(int st,int ed,int id)
{
	while(!s.empty())
	s.pop();
	s.push(st);
	dis[st]=0;
	vis[st]=id;
	while(!s.empty()&&vis[ed]!=id)
	{
		int now=s.front();s.pop();
		for (int i=head[now];i!=0;i=edge[i].next)
		{
			int v=edge[i].v;
			if (vis[v]!=id)
			{
				vis[v]=id;
				dis[v]=dis[now]+1;
				s.push(v);
			}
			if (vis[ed]==id)
			break;
		}
	}
}
int main()
{
	freopen("drive.in","r",stdin);
	freopen("drive.out","w",stdout);
	tot=1;
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		addedge(i,i+1);
		addedge(i+1,i);
	}
	addedge(1,n);
	addedge(n,1);
	for (int i=1,x,y;i<=n-3;i++)
	{
		scanf("%d%d",&x,&y);
		addedge(y,x);
		addedge(x,y);
	}
	scanf("%d",&q);
	for (int i=1,x,y;i<=q;i++)
	{
		scanf("%d%d",&x,&y);
		bfs(x,y,i);
		printf("%d\n",dis[y]);
	}
}

