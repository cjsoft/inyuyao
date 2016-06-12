#include<iostream>
#include<algorithm>
#include<stdio.h>
#define lson (id*2)
#define rson (id*2+1)
using namespace std;
struct node{
	int v;int w;int next;
}edge[100002];
int tot,n,head[5005],num,vis[5005],hash[1000005],mapp[5005],sum[1000005],vi[5005],zans;
int tr[400005];
void addedge(int u,int v,int w)
{
	tot++;
	edge[tot].v=v;
	edge[tot].w=w;
	edge[tot].next=head[u];
	head[u]=tot;
}
void pushup(int id)
{
	tr[id]=tr[lson]+tr[rson];
	return ;
}
void build(int l,int r,int id)
{
	tr[id]=0;
	if (l>=r) return ;
	int mid=(l+r)/2;
	build(l,mid,lson);
	build(mid+1,r,rson);
}
void add(int l,int r,int id,int s,int v)
{
	if (l>r) return ;
	if (l==r&&l==s)
	{
		tr[id]+=v;
		return ;
	}
	int mid=(l+r)/2;
	if (s<=mid)
	add(l,mid,lson,s,v);
	else
	add(mid+1,r,rson,s,v);	
	pushup(id);
}
int query(int l,int r,int id,int s)
{
	if (l>r) return -1;
	if (l==r)
	return l;
	int mid=(l+r)/2;
	if (tr[lson]>=s)
	return query(l,mid,lson,s);
	else
	return query(mid+1,r,rson,s-tr[lson]);
}
void dfs(int x,int fa,int dep)
{
	if (dep%2==1)
	{
		//cout<<x<<endl;
		//cout<<tr[1]<<endl;
		int goal=(dep+1)/2; 
		int tmpid=query(1,num,1,goal);
		//cout<<tmpid<<endl;
		int tmp=mapp[tmpid];
		zans+=tmp;
		//cout<<tmp<<endl;
	}
	for (int i=head[x];i!=0;i=edge[i].next)
	{
		int v=edge[i].v;
		if (v!=fa)
		{
			add(1,num,1,hash[edge[i].w],1);
			//cout<<tr[1]<<endl;
			dfs(v,x,dep+1);
			add(1,num,1,hash[edge[i].w],-1);
		}
	}
}
int main()
{
	freopen("draw.in","r",stdin);
	freopen("draw.out","w",stdout);
	tot=1;
	scanf("%d",&n);
	for (int i=1,x,y,z;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		addedge(x,y,z);
		addedge(y,x,z);
		vi[i]=z;
	}
	num=0;
	sort(vi+1,vi+n);
	for (int i=1;i<n;i++)
	if (hash[vi[i]]==0)
	{
		num++;
		hash[vi[i]]=num;
		mapp[num]=vi[i];
	}
	for (int i=1;i<=n;i++)
	{
		build(1,num,1);
		dfs(i,i,0);
	}
	zans/=2;
	printf("%d\n",zans);
}
