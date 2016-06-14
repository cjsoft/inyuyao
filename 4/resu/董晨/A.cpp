#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define N 2505
#define M 10005
#define P 1000000007
#define ll long long
#define INF 2000000000
int n,m,k,l,t,T,s,x,y,num,z,Len,tot;
int head[N],vet[M],next[M],cost[M],dis[N];
int b[N],c[N],len[N],q[N*N],qq[N*N],diss[N][N],Flag[N][N],flag[N];
ll ans;
struct node{
	int t,d,l,v;
}a[N*N];
bool cmp(node x,node y){
	return x.t<y.t;
}
void add(int a,int b,int c){
	next[++num]=head[a];
	head[a]=num;
	vet[num]=b;
	cost[num]=c;
}
void spfa(){
	for (int i=1;i<=n;i++)dis[i]=INF;
	dis[1]=0;
	int l=0,r=1;
	q[1]=1;
	while(l!=r){
		l=l%n+1;
		int u=q[l];
		flag[u]=0;
		for (int e=head[u];e;e=next[e]){
			int v=vet[e];
			if(dis[u]+cost[e]<dis[v]){
				dis[v]=cost[e]+dis[u];
				len[v]=len[u]+1;
				if(!flag[v]){
					r=r%n+1;
					q[r]=v;
					flag[v]=1;
				}
			}
		}
	}
}
void spfaa(){
	for (int i=1;i<=n;i++)
		for (int j=0;j<=len[i];j++)diss[i][j]=INF;
	q[1]=1,qq[1]=0;
	int l=0,r=1;
	diss[1][0]=0;
	while(l!=r){
		l=l%(N*N)+1;
		int u=q[l],L=qq[l];
		Flag[u][L]=0;
		for (int e=head[u];e;e=next[e]){
			int v=vet[e];
			if(L>=len[v])continue;
			if(diss[u][L]+cost[e]<diss[v][L+1]){
				diss[v][L+1]=diss[u][L]+cost[e];
				if(!Flag[v][L+1]){
					Flag[v][L+1]=1;
					r=r%(N*N)+1;
					q[r]=v,qq[r]=L+1;
				}
			}
		}
	}
}
int shit(int i,int x,int y){
	return (diss[i][x]-diss[i][y])/(y-x)+1;
}
int main(){
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	scanf("%d%d%d",&n,&m,&T);
	for (int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
	}
	spfa();
	spfaa();
	for (int i=2;i<=n;i++){
		int t=0;
		for (int j=1;j<=len[i];j++)
			if(diss[i][j]<INF&&(!t||diss[i][j]<diss[i][q[t]])){
				while(t>=2&&shit(i,q[t-1],q[t])<=shit(i,q[t],j))t--;
				q[++t]=j;
			}
		s+=diss[i][q[t]];
		b[i]=diss[i][q[t]];
		Len+=q[t];
		c[i]=q[t];
		for (int j=1;j<t;j++)a[++tot]=(node){shit(i,q[j],q[j+1]),diss[i][q[j]],q[j],i};
	}
	sort(a+1,a+tot+1,cmp);
	t=0;
	for (int i=1;i<=tot;i++){
		if(a[i].t!=a[i-1].t){
			int tt=min(a[i].t,T+1);
			ans=(ans+(ll)(tt-t)*(s+(ll)t*Len)%P+(ll)(tt-t)*(tt-t-1)/2%P*Len)%P;
			t=tt;
		}
		if(a[i].t>T)break;
		s+=a[i].d-b[a[i].v];
		Len+=a[i].l-c[a[i].v];
	}
//	printf("%d %d %d\n",s,Len,t);
	if(t<=T){
		int tt=T+1;
		ans=(ans+(ll)(tt-t)*(s+(ll)t*Len)%P+(ll)(tt-t)*(tt-t-1)/2%P*Len)%P;
		t=tt;
	}
	printf("%lld\n",ans);
}
