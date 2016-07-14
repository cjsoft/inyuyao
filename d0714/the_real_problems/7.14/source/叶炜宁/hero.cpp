#include<cstdio>
#include<queue>
#include<algorithm>
#define MG make_pair
#define se second
#define M 2000010
#define N 100010
#define inf 1000000000
using namespace std;
typedef long long ll;
typedef pair<ll,int> pa;
int n,m,K,tot,edgenum=1,S,T;
int head[N],pre[N],last[N],flag[N],a[310][310],id[310][310],q[N];
int vet[M],next[M],maxv[M],cost[M];
ll ans,dis[N],INF=10000000ll*100000000ll;
//priority_queue<pa,vector<pa>,greater<pa> >q;
void add(int u,int v,int w,int z)
{
	vet[++edgenum]=v;
	next[edgenum]=head[u];
	head[u]=edgenum;
	maxv[edgenum]=w;
	cost[edgenum]=z;
}
void Add(int u,int v,int w,int z){add(u,v,w,z);add(v,u,0,-z);}
void spfa()
{
	for (int i=0;i<=tot;i++){flag[i]=0;dis[i]=INF;}
	dis[0]=0;flag[0]=1;
	q[0]=0;
	int p1=-1,p2=0;
	while (p1<p2)
	{
		p1++;int u=q[p1%(tot+1)];
		flag[u]=0;
		for (int e=head[u];e;e=next[e])
		{
			if (maxv[e]<=0) continue;
			int v=vet[e];
			if (dis[u]+cost[e]<dis[v])
			{
				dis[v]=dis[u]+cost[e];
				pre[v]=u;
				last[v]=e;
				if (!flag[v]){flag[v]=1;p2++;q[p2%(tot+1)]=v;}
			}
		}
	}
}
void work()
{
	if (dis[T]==INF) return;
	ans+=dis[T];
	int u=T;
	while (u)
	{
		int e=last[u];
		maxv[e]--;maxv[e^1]++;
		u=pre[u];
	}
}
int main()
{
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) scanf("%d",&a[i][j]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) id[i][j]=++tot;
	S=0;T=++tot;
	for (int i=1;i<=m;i++) Add(S,id[1][i],1,a[1][i]);
	for (int i=1;i<n;i++)
		for (int j=1;j<=m;j++)
		{
			if (i<n) Add(id[i][j],id[i+1][j],1,a[i+1][j]);
			if (id[i][j-1]) Add(id[i][j],id[i][j-1],inf,K);
			if (id[i][j+1]) Add(id[i][j],id[i][j+1],inf,K);
		}
	for (int i=1;i<=m;i++) Add(id[n][i],T,1,0);
	spfa();work();
	spfa();work();
	printf("%lld\n",ans);
}
