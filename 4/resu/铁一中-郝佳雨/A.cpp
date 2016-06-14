#include<iostream>
#include<queue>
#include<cstdio>
#include<cstring>
#define LL long long
using namespace std;
const int maxn = 2505;
const int maxm = 5005;
const int mod = (LL)(1e9+7);
struct node{
	int v;
	LL w;
	int next;
}e[maxm*2];
int n,m,tot,vis[maxn],head[maxn];
LL t,ans,dis[maxn];
void add(int u,int v,LL w)
{
	e[tot]=(node){v,w,head[u]};
	head[u]=tot++;
	e[tot]=(node){u,w,head[v]};
	head[v]=tot++;
}
bool operator < (node a,node b)
{
	return dis[a.v]<dis[b.v];
}
void dij(int t)
{
	priority_queue<node>q;
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0LL,vis[1]=1;
	q.push((node){1,0,0});
	while(!q.empty())
	{
		int u = (q.top()).v;
		//printf("%d\n",u);
		//getchar();
		q.pop();
		for(int i = head[u]; i != -1; i=e[i].next)
		{
			if(dis[e[i].v]>dis[u]+e[i].w+t)
			{
				dis[e[i].v]=dis[u]+e[i].w+t;
				if(!vis[e[i].v])vis[e[i].v]=1,q.push((node){e[i].v,0,0});
			}
		}
		vis[u]=0;
	}
}
LL pow(LL x,LL k)
{
	LL ret=1LL,base=x;
	while(k)
	{
		if(k & 1)
		{
			ret*=base;
			//cout<<ret<<' ';
			ret%=mod;
			//cout<<ret<<endl;
		}
		base*=base;
		base%=mod;
		k>>=1;
	}
	return ret;
}
int main(void)
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	scanf("%d%d%lld",&n,&m,&t);
	for(int i = 0; i <= n; i++)
		head[i]=-1;
	int u,v;LL l;
	for(int i = 0; i < m; i++)
	{
		scanf("%d%d%lld",&u,&v,&l);
		add(u,v,l);
	}
	//cout<<"test"<<endl;
	if(t>1000)
	{
		dij(0);
		for(int i = 1; i <= n; i++)
			ans+=dis[i],ans%=mod;
		//cout<<ans<<endl;
		LL b=pow(2LL,mod-2LL);
		//cout<<b<<endl;
		ans=(ans*2LL)%mod;
		ans=(ans+t*((LL)(n-1)))%mod;
		ans=(ans*(t+1LL))%mod;
		ans=(ans*b)%mod;
	}
	else
	{
		for(int i = 0; i <= t; i++)
		{
			dij(i);
			for(int i = 1; i <= n; i++)
				ans+=dis[i],ans%=mod;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
