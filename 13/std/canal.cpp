#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
const int mod=998244353,MAXN=100000,MAXM=100000,MAXP=200,MAXQ=200;
struct Point
{
	int x,y;
	Point(int _x=0,int _y=0):x(_x),y(_y){}
	bool operator<(const Point &o)const
	{
		if(x!=o.x)return x<o.x;
		else return y<o.y;
	}
}obst[MAXQ+10];
int n,m,p,q,fac[MAXN+MAXM+10],inv[MAXN+MAXM+10];
int g[MAXP+10][MAXP+10],ways[MAXQ+10],st[MAXP+10],ed[MAXP+10];
inline int quick_pow(int x,int r)
{
	int ret=1;
	for(;r;r>>=1)
	{
		if(r&1)ret=(LL)ret*x%mod;
		x=(LL)x*x%mod;
	}
	return ret;
}
inline int com(int a,int b)
{
	if(a<b||a<0||b<0)return 0;
	return (LL)fac[a]*inv[b]%mod*inv[a-b]%mod;
}
inline int get_ways(const Point &a,const Point &b)
{
//	cout<<'('<<a.x<<", "<<a.y<<") --> ("<<b.x<<", "<<b.y<<')'<<endl;
	return com((b.x-a.x)+(b.y-a.y),b.x-a.x);
}
inline void init()
{
	scanf("%d%d%d%d",&n,&m,&p,&q);
	for(int i=0;i<p;i++)scanf("%d",&st[i]);
	for(int i=0;i<p;i++)scanf("%d",&ed[i]);
	for(int i=0;i<q;i++)scanf("%d%d",&obst[i].x,&obst[i].y);
	sort(st,st+p);
	sort(ed,ed+p);
	sort(obst,obst+q);
}
inline void prepare()
{
	fac[0]=1;
	for(int i=1;i<=n+m;i++)fac[i]=(LL)fac[i-1]*i%mod;
	inv[n+m]=quick_pow(fac[n+m],mod-2);
	for(int i=n+m-1;i>=0;i--)inv[i]=(LL)inv[i+1]*(i+1)%mod;
}
inline void solve(int o)
{
	for(int i=0;i<q;i++)
	{
		ways[i]=get_ways(Point(0,st[o]),obst[i]);
		printf("%d\t", ways[i]);
		for(int j=0;j<i;j++)ways[i]=(ways[i]-(LL)ways[j]*get_ways(obst[j],obst[i]))%mod;
	}
	for(int i=0;i<p;i++)
	{
		g[o][i]=get_ways(Point(0,st[o]),Point(n,ed[i]));
		for(int j=0;j<q;j++)g[o][i]=(g[o][i]-(LL)ways[j]*get_ways(obst[j],Point(n,ed[i])))%mod;
	}
	puts("");
	puts("");
}
inline int calc()
{
/*	for(int i=0;i<p;i++)
	{
		for(int j=0;j<p;j++)cout<<g[i][j]<<' ';
		cout<<endl;
	}*/
	int ret=1;
	for(int i=0;i<p;i++)
	{
		if(!g[i][i])
		{
			for(int j=i+1;j<p;j++)
				if(g[j][i])
				{
					for(int k=i;k<p;k++)swap(g[i][k],g[j][k]);
					ret=-ret;
					break;
				}
			if(!g[i][i])return 0;
		}
		for(int j=i+1;j<p;j++)
		{
			int mult=(LL)g[j][i]*quick_pow(g[i][i],mod-2)%mod;
			for(int k=i;k<p;k++)g[j][k]=(g[j][k]-(LL)g[i][k]*mult)%mod;
		}
	}
	for(int i=0;i<p;i++)ret=(LL)ret*g[i][i]%mod;
	return (ret+mod)%mod;
}
int main(void)
{
	// freopen("canal.in","r",stdin);
	// freopen("canal.out","w",stdout);
	init();
	prepare();
	for(int i=0;i<p;i++)solve(i);
	printf("%d\n",calc());
	return 0;
}
