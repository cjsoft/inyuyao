#include<iostream>
#include<algorithm>
#include<vector>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 70005;
struct node{
	int v,next;
}e[250005];
int n,Q,tot,head[maxn],p[maxn],dis[maxn],res[maxn],q[maxn],ans[maxn];
vector<node> que[maxn];
void add(int u,int v)
{
	e[tot]=(node){v,head[u]};
	head[u]=tot++;
	e[tot]=(node){u,head[v]};
	head[v]=tot++;
}
void solve(int x)
{
	memset(dis,-1,sizeof(dis));
	dis[x]=0;
	int h=0,t=0;
	q[t++]=x;
	while(h<t)
	{
		int u=q[h++];
		for(int i = head[u]; i != -1; i=e[i].next)
			if(dis[e[i].v]==-1)
			{
				dis[e[i].v]=dis[u]+1;
				q[t++]=e[i].v;
			}
	}
	for(int i = 0; i < que[x].size(); i++)
		ans[que[x][i].next]=dis[que[x][i].v],res[x]++,res[que[x][i].v]++;
	return;
}
bool cmp(int a,int b)
{
	return (que[a].size())>(que[b].size());
}
int main(void)
{
	freopen("drive.in","r",stdin);
	freopen("drive.out","w",stdout);
	scanf("%d",&n);
	for(int i = 1; i <= n; i++)
		head[i]=-1;
	for(int i = 1; i < n; i++)
		add(i,i+1);
	if(n>1)add(n,1);
	int a,b;
	for(int i = n-3; i > 0; i--)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
	}
	scanf("%d",&Q);
	for(int i = 1; i <= Q; i++)
	{
		scanf("%d%d",&a,&b);
		que[a].push_back((node){b,i});
		que[b].push_back((node){a,i});
		p[i]=i;
	}
	sort(p+1,p+1+Q,cmp);
	for(int i = 1; i <= n; i++)
		if(res[p[i]]<(que[p[i]].size()))solve(p[i]);
	for(int i = 1; i <= Q; i++)
		printf("%d\n",ans[i]);
	return 0;
}
	
