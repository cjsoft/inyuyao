#include<algorithm>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include  <stdio.h>
#include   <math.h>
#include   <time.h>
#include   <vector>
#include   <bitset>
#include    <queue>
#include      <set>
#include      <map>
using namespace std;

const int N=200005;

int n,k,tot,typ[N],Q[N],G[N],next[N*2],e[N*2],fa[N],Sum[N],Max[N];

void adde(int u,int v)
{
	e[++tot]=v;next[tot]=G[u];G[u]=tot;
	e[++tot]=u;next[tot]=G[v];G[v]=tot;
}

void bfs()
{
	int l,r;
	Q[l=r=1]=1;
	while(l<=r)
	{
		int u=Q[l++];
		for(int i=G[u];i;i=next[i])
			if(e[i]!=fa[u])
				fa[e[i]]=u,Q[++r]=e[i];
	}
}

bool check(int k)
{
	memset(Sum,0,sizeof Sum);memset(Max,0,sizeof Max);
	for(int i=n;i;i--)
	{
		int u=Q[i];
		if(typ[u]==1)
			Max[u]=k-1;
		else
			Sum[u]++;
		if(Sum[u]>=k)
			return 0;
		int f=Max[u]>=Sum[u]?Max[u]-Sum[u]:-Sum[u];
		if(i==1&&f<0)
			return 0;
		if(f<0)
			Sum[fa[u]]-=f;
		else
			Max[fa[u]]=max(Max[fa[u]],f);
	}
	return 1;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("deep.in","r",stdin);
	freopen("deep.out","w",stdout);
#endif
	scanf("%d%d",&n,&k);
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),adde(u,v);
	for(int i=1,u;i<=k;i++)
		scanf("%d",&u),typ[u]=1;
	bfs();
	int l=1,r=n,Ans=n;
	while(l<=r)
	{
		int Mid=l+r>>1;
		if(check(Mid))
			Ans=Mid,r=Mid-1;
		else
			l=Mid+1;
	}
	printf("%d\n",Ans);
	return 0;
}


