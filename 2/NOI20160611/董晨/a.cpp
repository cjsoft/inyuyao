#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
#define N 300005
#define M 600005
#define ll long long
int n,m,k,l,id,num,x,y,z,t,Q,r;
int head[N],vet[M],next[M],dep[N],ans;
int a[N],b[N],fa[N][20],root[N];
struct node{
	int l,r,s;
}T[N*20];
void add(int a,int b){
	next[++num]=head[a];
	head[a]=num;
	vet[num]=b;
}
void ins(int &i,int l,int r,int x){
	T[++id]=T[i];i=id;
	T[i].s++;
	if(l==r)return;
	int mid=l+r>>1;
	if(x<=mid)ins(T[i].l,l,mid,x);
	else ins(T[i].r,mid+1,r,x);
}
void dfs(int u){
	root[u]=root[fa[u][0]];
	for (int i=1;i<=18;i++)fa[u][i]=fa[fa[u][i-1]][i-1];
	ins(root[u],1,m,a[u]);
	for (int e=head[u];e;e=next[e]){
		int v=vet[e];
		if(v!=fa[u][0]){
			dep[v]=dep[u]+1;
			fa[v][0]=u;
			dfs(v);
		}
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	int t=dep[x]-dep[y];
	for (int i=0;i<=18;i++)
		if(t&(1<<i))x=fa[x][i];
	for (int i=18;i>=0;i--)
		if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	if(x==y)return x;
	else return fa[x][0];
}
int que(int a,int b,int c,int d,int l,int r,int x,int y){
	if(x>y)return 0;
	if(l==x&&y==r)return T[a].s+T[b].s-T[c].s-T[d].s;
	int mid=l+r>>1;
	if(y<=mid)return que(T[a].l,T[b].l,T[c].l,T[d].l,l,mid,x,y);
	else if(x>mid)return que(T[a].r,T[b].r,T[c].r,T[d].r,mid+1,r,x,y);
	else return que(T[a].l,T[b].l,T[c].l,T[d].l,l,mid,x,mid)+
				que(T[a].r,T[b].r,T[c].r,T[d].r,mid+1,r,mid+1,y);
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d%d",&n,&m,&Q);
	for (int i=1;i<=n;i++)scanf("%d",&a[i]);
	for (int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dep[1]=1;
	dfs(1);
	while(Q--){
		scanf("%d%d%d",&l,&r,&k);
		l^=ans,r^=ans,k^=ans;
		t=lca(l,r);
		x=que(root[l],root[r],root[t],root[fa[t][0]],1,n,1,k-1);
		y=que(root[l],root[r],root[t],root[fa[t][0]],1,n,k,k);
		z=que(root[l],root[r],root[t],root[fa[t][0]],1,n,k+1,m);
		printf("%d %d %d\n",x,y,z);
		ans=x^y^z;
	}
}
