#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
const int maxn = 35000;
struct node{
	int v,w,next;
}e[250005];
int n,tot,head[maxn],odds[maxn],evens[maxn];
LL oddv[maxn],evenv[maxn],ev[maxn],ov[maxn],ans;
void add(int u,int v,int w)
{
	e[tot]=(node){v,w,head[u]};
	head[u]=tot++;
	e[tot]=(node){u,w,head[v]};
	head[v]=tot++;
}
void dfs(int pre,int u)
{
	int v;
	evens[u]=1;
	for(int i = head[u]; i!=-1; i=e[i].next)
		if((e[i].v)!=pre)
		{
			v=e[i].v;
			dfs(u,v);
			odds[u]+=evens[v];
			evens[u]+=odds[v];
			oddv[u]+=evenv[v]+(ev[v]=((LL)evens[v])*((LL)e[i].w));
			evenv[u]+=oddv[v]+(ov[v]=((LL)odds[v])*((LL)e[i].w));
		}
	for(int i = head[u]; i!=-1; i=e[i].next)
		if((e[i].v)!=pre)
		{
			v=e[i].v;
			ans+=evenv[v]+ev[v]+((LL)evens[v])*(evenv[u]-oddv[v]-ov[v]);
			cout<<v<<' '<<ans<<' '<<evenv[v]<<' '<<ev[v]<<' '<<evens[v]<<' '<<evenv[u]<<' '<<oddv[v]<<' '<<ov[v]<<endl;
		}
}
int main(void)
{
	scanf("%d",&n);
	for(int i = 1; i <= n; i++)
		head[i]=-1;
	int a,b,c;
	for(int i = 1; i < n; i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);
	}
	dfs(0,1);
	printf("%lld\n",ans);
	return 0;
}
	
