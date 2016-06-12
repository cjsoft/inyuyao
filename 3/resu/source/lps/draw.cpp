#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
using namespace std;
int n,m;
int head[15005],nex[15005],tot,to[15005];
int val[15005];
int a[15005];
int bb[15005];
int f[15005],sz[15005],size;
int vis[15005];
long long ans;
int F;
int rt;
void add(int x,int y,int v)
{
	int tmp=head[x];
	head[x]=++tot;
	to[tot]=y;
	nex[tot]=tmp;	
	val[tot]=v;
}
void getrt(int x,int fa)
{

	sz[x]=1;
	f[x]=0;
	
	for(int i=head[x];i!=-1;i=nex[i])
	{
		
		int v=to[i];
		if(v==fa||vis[v]) continue ;
		getrt(v,x);
		sz[x]+=sz[v];
		f[x]=max(f[x],sz[v]);
	}
	f[x]=max(f[x],size-sz[x]);
	if(f[x]<f[rt]) rt=x;
}
void dfs2(int x,int fa,int cnt,int aa[])
{
//	cout<<x<<"   "<<fa<<endl;
	if(cnt%2==1)
	{
		for(int i=1;i<=cnt;i++)
		bb[i]=aa[i];
		sort(bb+1,bb+1+cnt);
		ans+=bb[(1+cnt)>>1];
	//	cout<<ans<<endl;
	}
	for(int i=head[x];i!=-1;i=nex[i])
	{
		int v=to[i];
		if(v==fa||vis[v]) continue;
		aa[cnt+1]=val[i];
		dfs2(v,x,cnt+1,aa);	
	}
	return ;
}
void dfs1(int x,int fa,int cnt,int aa[],int id)
{
	sz[x]=1;
	if(cnt%2==1)
	{
		for(int i=1;i<=cnt;i++)
		bb[i]=aa[i];
		sort(bb+1,bb+1+cnt);
		ans+=bb[(1+cnt)>>1];
	//	cout<<ans<<endl;
	}
//	cout<<x<<"  "<<fa<<"  "<<cnt<<"     "<<id<<endl;
	for(int i=nex[id];i!=-1;i=nex[i])
	{
		
		int v=to[i];
		if(vis[v]) continue ;
		aa[cnt+1]=val[i];
		dfs2(v,F,cnt+1,aa);
	}

	
	for(int i=head[x];i!=-1;i=nex[i])
	{
		int v=to[i];
		if(v==fa||vis[v]) continue;
		aa[cnt+1]=val[i];
		dfs1(v,x,cnt+1,aa,id);	
		sz[x]+=sz[v];       
	}
	return ;	
	
}
void cal(int x)
{
	F=x;
	for(int i=head[x];i!=-1;i=nex[i])
	{
	
		int v=to[i];
		if(vis[v]) continue ;	
		int cnt=0;
		a[cnt+1]=val[i];
		dfs1(v,x,cnt+1,a,i);
	}
	
}
void solve(int x)
{
	cal(x);
//	cout<<x<<"   "<<ans<<endl;
	//while(1);
	vis[x]=1;
    for(int i=head[x];i!=-1;i=nex[i])
    {
       	int v=to[i];
		if(vis[v]) continue ;
       
        f[0]=size=sz[v];
        getrt(v,rt=0);
        solve(rt);
    }	
}
int main()
{
		freopen("draw.in","r",stdin);
		freopen("draw.out","w",stdout);
	int aa,bb,cc;
	memset(head,-1,sizeof(head));
	scanf("%d\n",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%d",&aa,&bb,&cc);
		add(aa,bb,cc);
		add(bb,aa,cc);
	}
	ans=0;
    f[0]=size=n;
    getrt(1,rt=0); 
	
    solve(rt);
    printf("%lld\n",ans);

}
