#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define N 200005
#define ll long long
int n,m,k,l,t,s,num;ll ans;
int f[N],pre[N],p[N],a[N],b[N],c[N],next[N],vet[N],cost[N],head[N];
int x[N],y[N],z[N];
bool cmp(int x,int y){
	return z[x]<z[y];
}
void add(int a,int b,int c){
	next[++num]=head[a];
	head[a]=num;
	vet[num]=b;
	cost[num]=c;
}
void dfs(int u,int fa,int x,int s){
	p[n+s]++;
	for (int e=head[u];e;e=next[e]){
		int v=vet[e];
		if(v!=fa){
			int y;
			if(cost[e]>=x)y=1;else y=-1;
			dfs(v,u,x,s+y);
		}
	}
}
void dfss(int u,int fa,int x,int s){
	ans+=(ll)pre[x]*p[n+s];
	for (int e=head[u];e;e=next[e]){
		int v=vet[e];
		if(v!=fa){
			int y;
			if(cost[e]<=x)y=1;else y=-1;
			dfss(v,u,x,s+y);
		}
	}
}
int main(){
	freopen("draw.in","r",stdin);
	freopen("draw.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<n;i++){
		f[i]=i;
		scanf("%d%d%d",&x[i],&y[i],&z[i]);
	}
	sort(f+1,f+n,cmp);
	for (int i=1;i<n;i++)pre[i]=z[f[i]],a[f[i]]=i;
	for (int i=1;i<n;i++)add(x[i],y[i],a[i]),add(y[i],x[i],a[i]);
	for (int i=1;i<n;i++){
		for (int j=0;j<=2*n;j++)p[j]=0;
		dfs(x[i],y[i],a[i],0);
		dfss(y[i],x[i],a[i],0);
	}
	printf("%lld\n",ans);
}
