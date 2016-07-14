#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<queue>
#include<time.h>
using namespace std;
typedef long long ll;
ll INF=2147483640;
ll a[351][351];
ll dis[500051];
ll val[500051];
ll kk;
ll ans=0;
int edge[500051],flow[500051],next[500051],st[500051],last[500051],S,T,SS,n,m;
int b[500051],fa[500051],edg[500051];
int tot=1;
queue<int> que;
inline void addedge(int x,int y,int fl,int v)
{
	edge[++tot]=y;
	flow[tot]=fl;
	val[tot]=v;
	if(st[x]==0)st[x]=tot;
	next[last[x]]=tot;
	last[x]=tot;
	edge[++tot]=x;
	flow[tot]=0;
	val[tot]=-v;
	if(st[y]==0)st[y]=tot;
	next[last[y]]=tot;
	last[y]=tot;
}
void spfa(int sta)
{
	while(dis[T]!=INF)
	{
	  for(int i=0;i<=SS;i++)
	    dis[i]=INF;
	  dis[sta]=0;
	  que.push(sta);
	  b[sta]=1;
	  ll minflow=INF;
	 
	  while(que.empty()==0)
	  {
		  int x=que.front();
		  que.pop();
		  b[x]=0;
		  for(int i=st[x];i!=0;i=next[i])
		  {
			  int next=edge[i],v=val[i];
			  if(dis[next]>dis[x]+v&&flow[i]>0)
			  {
			  	  fa[next]=x;edg[next]=i;
				  dis[next]=dis[x]+v;
				  if(b[next]==0)
				    que.push(next);
		 	  }
		  }
		  if(n*m+1<=x&&x<=n*m*2)
		  {
		  	for(int i=1;i<=m;i++)
		  	{
		  		int nn=(x-1)/m-n,mm=(x-1)%m+1;
		  		int next=(nn+1)*m+i,v=kk*abs(i-mm);
		  	    if(dis[next]>dis[x]+v)
		  	    {
		  	      fa[next]=x;edg[next]=-1;
				  dis[next]=dis[x]+v;	
				  if(b[next]==0)
				    que.push(next);
		  	    }
		  	}
		  }
	  }
	  if(dis[T]!=INF)
	  {
	    for(int i=T;i!=0;i=fa[i])
	    {if(edg[i]!=-1){flow[edg[i]]-=1;flow[edg[i]^1]+=1;}
	    else{addedge(i,fa[i],1,-kk*abs((i-1)%m+1-(fa[i]-1)%m-1));}}
	    ans+=dis[T];
      }
    }
    printf("%lld\n",ans);
}
void init()
{
	INF=INF*INF;
	scanf("%d%d%d",&n,&m,&kk);
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
	  	scanf("%d",&a[i][j]);
	S=n*m*2+1;T=n*m*2+2;SS=n*m*2+3;
	addedge(SS,S,2,0);
	for(int i=1;i<=m;i++)
	addedge(S,i,1,0);
	for(int i=1;i<=m;i++)
	addedge((n-1)*m+n*m+i,T,1,0);
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
	    addedge((i-1)*m+j,(i-1)*m+n*m+j,1,a[i][j]);
	spfa(SS);
}
int main()
{
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	init();
	return 0;
}
