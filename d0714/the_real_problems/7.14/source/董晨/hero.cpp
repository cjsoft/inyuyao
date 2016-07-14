#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 305
#define M 800005
#define INF 1000000000
int ed,n,m,k,l,num,x,y,z,K,ans;
int dis[M],head[M],vet[M],next[M],cost[M],size[M];
int a[N][N],flag[M],p[M][2],q[M],rem[M];
void add(int a,int b,int c,int d){
	next[++num]=head[a];
	head[a]=num;
	vet[num]=b;
	size[num]=c;
	cost[num]=d;
	next[++num]=head[b];
	head[b]=num;
	vet[num]=a;
	size[num]=0;
	cost[num]=-d;
}
bool spfa(){
	for (int i=1;i<=ed;i++)dis[i]=INF;
	int pre=0,tail=1;
	q[1]=0;
	rem[0]=INF;
	while(pre!=tail){
		pre=pre%(ed+1)+1;
		int u=q[pre];
//		printf("%d\n",u);
		flag[u]=0;
		for (int e=head[u];e;e=next[e]){
			int v=vet[e];
			if(size[e]&&dis[u]+cost[e]<dis[v]){
				dis[v]=dis[u]+cost[e];
				p[v][0]=u;p[v][1]=e;
				rem[v]=min(size[e],rem[u]);
				if(!flag[v]){
					tail=tail%(ed+1)+1;
					flag[v]=1;
					q[tail]=v;
				}
			}
		}
	}
	if(dis[ed]==INF)return 0;
	ans+=rem[ed]*dis[ed];
	int u=ed;
	while(u){
		size[p[u][1]]-=rem[ed];
		size[p[u][1]^1]+=rem[ed];
		u=p[u][0];
	}
	return 1;
}
int main(){
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout); 
	num=1;
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)scanf("%d",&a[i][j]);
	ed=n*m+1;
	for (int i=1;i<=m;i++){
		add(0,i,1,0);
		add((n-1)*m+i,ed,1,a[n][i]);
	}
	for (int i=1;i<n;i++)
		for (int j=1;j<=m;j++)add((i-1)*m+j,i*m+j,1,a[i][j]);
	for (int i=0;i<n;i++)
		for (int j=1;j<m;j++){
			add(i*m+j,i*m+j+1,INF,K);
			add(i*m+j+1,i*m+j,INF,K);
		}
	spfa();spfa();
	printf("%d\n",ans);
}