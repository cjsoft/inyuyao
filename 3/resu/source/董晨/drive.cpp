#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define N 400005
int n,m,k,l,t,s,ans,num,x,y;
int dis[N],a[N],b[N],q[N],head[N],vet[N],next[N],flag[N];
void add(int a,int b){
	next[++num]=head[a];
	head[a]=num;
	vet[num]=b;
}
int bfs(int x,int y,int k){
	if(x==y)return 0;
	int l=0,r=1;
	q[1]=x;flag[x]=k;dis[x]=0;
	while(l<r){
		int u=q[++l];
		for (int e=head[u];e;e=next[e]){
			int v=vet[e];
			if(flag[v]==k)continue;
			flag[v]=k;
			dis[v]=dis[u]+1;
			if(v==y)return dis[v];
			q[++r]=v;
		}
	}
}
int main(){
	freopen("drive.in","r",stdin);
	freopen("drive.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n-3;i++){
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	for (int i=1;i<n;i++)add(i,i+1),add(i+1,i);
	add(n,1);add(1,n);
	scanf("%d",&m);
	while(m--){
		k++;
		scanf("%d%d",&x,&y);
		printf("%d\n",bfs(x,y,k));
	}
}
