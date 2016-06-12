#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
using namespace std;
int n,m;
int head[5005],nex[40005],tot,to[40005];
int vis[5005];
int v[5005];
queue<int> q;

int d[5005];
struct node{
	int x,y,id,ans;
		
}qq[10005];
int cmp(node xx,node yy)
{
	return xx.x<yy.x;	
}
int cc(node xx,node yy)
{
	return xx.id<yy.id;	
}

void add(int x,int y)
{
	int tmp=head[x];
	head[x]=++tot;
	to[tot]=y;
	nex[tot]=tmp;	
}
void spfa(int x)
{
	d[x]=0;	
	q.push(x);
	while(!q.empty())
	{
		int now=q.front();
		
		q.pop();
		for(int i=head[now];i!=-1;i=nex[i])	
		{
			int nexx=to[i];
		
			if(d[nexx]==-1)
			{
				d[nexx]=d[now]+1;
				q.push(nexx);
			}
			
		}
	}
	
}
int main()
{
		freopen("drive.in","r",stdin);
		freopen("drive.out","w",stdout);
	scanf("%d",&n);
	memset(head,-1,sizeof(head));
	for(int i=1;i<n;i++)
	{
		add(i,i+1);
		add(i+1,i);
	}
	add(1,n);
	add(n,1);
	int aa,bb;
	for(int i=1;i<=n-3;i++)
	{
		scanf("%d%d",&aa,&bb);
		add(aa,bb);
		add(bb,aa);
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&qq[i].x,&qq[i].y);
		qq[i].id=i;
		if(qq[i].x>qq[i].y) swap(qq[i].y,qq[i].x);	
	}
	sort(qq+1,qq+1+m,cmp);
	for(int i=1;i<=m;i++)
	{
		if(!vis[qq[i].x])
		{
			vis[qq[i].x]=1;
			memset(d,-1,sizeof(d));
		
			spfa(qq[i].x);
		}
		qq[i].ans=d[qq[i].y];
	}
	sort(qq+1,qq+1+m,cc);
	for(int i=1;i<=m;i++)
	printf("%d\n",qq[i].ans);
	
}
