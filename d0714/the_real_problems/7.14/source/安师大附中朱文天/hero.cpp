#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
#define N 350
#define inf 0x7f7f7f7f

bool vis[N*N];
int S,T,n,m,K,en,ans,dis[N*N],from[N*N],head[N*N],v[N][N];

queue<int> Q;

struct Edge{
	int to,f,c,next;
	Edge(){}
	Edge(int _to,int _f,int _c,int _next){
		to=_to,f=_f,c=_c,next=_next;
	}
}e[53821000];

inline int read(){
	char cr;
	int x=0;
	cr=getchar();
	while(cr<'0'||cr>'9') cr=getchar();
	while(cr>='0'&&cr<='9'){
		x=x*10+cr-'0';
		cr=getchar();
	}
	return x;
}
	
int Abs(int x){return x<0?-x:x;}

inline void addEdge(int u,int v,int f,int c){
	e[++en]=Edge(v,f,c,head[u]),head[u]=en;
	e[++en]=Edge(u,0,-c,head[v]),head[v]=en;
}
	
void init(){
	n=read(),m=read(),K=read();
	en=1;
	S=n*m+1,T=S+1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) v[i][j]=read();
	addEdge(0,S,2,0);
	for(int i=1;i<=m;i++) addEdge(S,i,1,v[1][i]);
	for(int i=1;i<n;i++)
	    for(int j=1;j<=m;j++)
		    for(int k=1;k<=m;k++) addEdge((i-1)*m+j,i*m+k,1,v[i+1][k]+K*Abs(j-k));
	for(int i=1;i<=m;i++) addEdge((n-1)*m+i,T,1,0);
}

bool spfa(){
	for(int i=1;i<=T;i++) dis[i]=inf,vis[i]=0;
	Q.push(0),dis[0]=0,vis[0]=1;
	while(!Q.empty()){
		int u=Q.front();
		Q.pop(),vis[u]=0;
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].to;
			if(e[i].f&&dis[v]>dis[u]+e[i].c){
				from[v]=i;
				dis[v]=dis[u]+e[i].c;
				if(!vis[v]){
					Q.push(v);
					vis[v]=1;
				}
			}
		}
	}
	return dis[T]!=inf;
}

void adjust(){
	int p,sum=inf;
	for(int i=T;i;i=e[p^1].to){
		p=from[i];
		sum=min(sum,e[p].f);
	}
	for(int i=T;i;i=e[p^1].to){
		p=from[i];
		e[p].f-=sum;
		e[p^1].f+=sum;
		ans+=sum*e[p].c;
	}
}

int main(){
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	init();
	while(spfa()) adjust();
	printf("%d\n",ans);
	return 0;
}
