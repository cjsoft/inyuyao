#include <cstdio>
#include <cstring>
#include <ctime>
#include <algorithm>
template <typename T> inline void tension(T &a, const T &b){if (a>b) a=b;}
template <typename T> inline bool tensionv(T &a, const T &b){return a>b?a=b, true:false;}
inline unsigned int getuint(){
	char w=getchar();
	while (w<'0'||'9'<w) w=getchar();
	unsigned int ans=0;
	for (;'0'<=w&&w<='9';w=getchar()) ans=ans*10+w-'0';
	return ans;
}
int n, m, K;
int a[305][305];
namespace Force{
	int dp[55][55][55];
	void solve(){
		for (int j=1;j<=m;j++) for (int k=1;k<=m;k++) if (j!=k) dp[1][j][k]=a[1][j]+a[1][k];
		for (int i=2;i<=n;i++) for (int x=1;x<=m;x++) for (int y=1;y<=m;y++) if (x!=y){
			dp[i][x][y]=0x3f3f3f3f;
			for (int j=1;j<=m;j++) for (int k=1;k<=m;k++) if (j!=k) tension(dp[i][x][y], dp[i-1][j][k]+a[i][x]+a[i][y]+K*std::abs(j-x)+K*std::abs(k-y));
		}
		int ans=0x3f3f3f3f;
		for (int j=1;j<=m;j++) for (int k=1;k<=m;k++) if (j!=k) tension(ans, dp[n][j][k]);
		printf("%d\n", ans);
	}
}
/*
namespace Force2{
	const int MAXV=305*305*305;
	std::pair<int, int> heap[MAXV>>1];int heap_size;
	int dist[MAXV];
	inline int ID(int x, int y, int z){return x*301*301+y*301+z;}
	inline void push(int x, int d){if (tensionv(dist[x], d)) heap[heap_size++]=std::make_pair(-dist[x], x), std::push_heap(heap, heap+heap_size);}
	void solve(){
		memset(dist, 0x3f, sizeof(dist));
		for (int i=1;i<=m;i++) for (int j=1;j<=m;j++) if (i!=j) heap[heap_size++]=std::make_pair(-(dist[ID(1, i, j)]=0), ID(1, i, j));
		std::make_heap(heap, heap+heap_size);
		int ans=0x3f3f3f3f;
		for (int d, x;heap_size;){
			d=-heap->first, x=heap->second, std::pop_heap(heap, heap+heap_size--);
			if (d!=dist[x]) continue;
			if (d>ans) continue;
			int i=x/301/301%301, j=x/301%301, k=x%301;
			if (j!=k) if (i<n) push(ID(i+1, j, k), d+a[i][j]+a[i][k]); else tension(ans, d+a[i][j]+a[i][k]);
			if (1<j) push(ID(i, j-1, k), d+K);
			if (j<m) push(ID(i, j+1, k), d+K);
			if (1<k) push(ID(i, j, k-1), d+K);
			if (k<m) push(ID(i, j, k+1), d+K);
		}
		printf("%d\n", ans);
	}
}
*/
namespace Force233{
	int V, S, T;
	int id[305][305];
	const int MAXV=305*305, MAXE=305*305*20;
	struct Edge{int t, next, cap, v;} G[MAXE];int head[MAXV], e=1;
	inline void add_double_edge(int x, int y, int z, int v){
		G[++e].t=y, G[e].next=head[x], head[x]=e;G[e].cap=z, G[e].v=v;
		G[++e].t=x, G[e].next=head[y], head[y]=e;G[e].cap=0, G[e].v=-v;
	}
	struct Min_Cost_Flow{
		int dist[MAXV], vis[MAXV];
		std::pair<int, int> heap[MAXE];int heap_size;
		void SPFA(){
			memset(dist+1, 0x3f, sizeof(*dist)*V), heap[heap_size++]=std::make_pair(-(dist[T]=0), T), std::make_heap(heap, heap+heap_size);
			for (int d, x;heap_size;){
				d=-heap->first, x=heap->second, std::pop_heap(heap, heap+heap_size--);
				if (d!=dist[x]) continue;
				for (int i=head[x];i;i=G[i].next) if (G[i^1].cap&&tensionv(dist[G[i].t], d-G[i].v))
					heap[heap_size++]=std::make_pair(-dist[G[i].t], G[i].t), std::push_heap(heap, heap+heap_size);
			}
		}
		int dfs(int x, int aug0){
			if (x==T) return aug0;vis[x]=1;
			int aug=aug0;
			for (int i=head[x];i;i=G[i].next) if (G[i].cap&&!vis[G[i].t]&&dist[x]==dist[G[i].t]+G[i].v){
				int flow=dfs(G[i].t, std::min(aug, G[i].cap));
				if (flow){
					G[i].cap-=flow, G[i^1].cap+=flow, aug-=flow;
					if (!aug) break;
				}
			}
			return aug0-aug;
		}
		bool adjust(){
			SPFA();return dist[S]!=0x3f3f3f3f;
			int d=0x3f3f3f3f;
			for (int x=1;x<=V;x++) if (vis[x]) for (int i=head[x];i;i=G[i].next) if (G[i].cap&&!vis[G[i].t]) tension(d, dist[G[i].t]+G[i].v-dist[x]);
			if (d==0x3f3f3f3f) return false;
			for (int x=1;x<=V;x++) if (vis[x]) dist[x]+=d;
			return true;
		}
		std::pair<int, int> min_cost_flow(int limit){
			std::pair<int, int> ans(0, 0);
			for (SPFA();limit;){
				for (int t;limit;){
					memset(vis+1, 0, sizeof(*vis)*V);
					if (t=dfs(S, limit)) ans.first+=t, ans.second+=t*dist[S], limit-=t; else break;
				}
				if (!adjust()) break;
			}
			return ans;
		}
	} MCF;
	void solve(){
		S=++V, T=++V;
		for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) id[i][j]=++V;
		for (int j=1;j<=m;j++) add_double_edge(S, id[1][j], 1, 0);
		for (int i=1;i<n;i++) for (int j=1;j<=m;j++) add_double_edge(id[i][j], id[i+1][j], 1, a[i][j]);
		for (int j=1;j<=m;j++) add_double_edge(id[n][j], T, 1, a[n][j]);
		for (int i=1;i<=n;i++) for (int j=1;j<m;j++) add_double_edge(id[i][j], id[i][j+1], 0x3f3f3f3f, K);
		for (int i=1;i<=n;i++) for (int j=m;j>1;j--) add_double_edge(id[i][j], id[i][j-1], 0x3f3f3f3f, K);
		printf("%d\n", MCF.min_cost_flow(2).second);
		//printf("%.3f\n", 1.0*clock()/CLOCKS_PER_SEC);
	}
}
int main(){
	freopen("hero.in", "r", stdin);
	freopen("hero.out", "w", stdout);
	n=getuint(), m=getuint(), K=getuint();
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) a[i][j]=getuint();
	//if (n<=50&&m<=50) return Force::solve(), 0;
	//Force::solve();
	//Force2::solve();
	Force233::solve();
	return 0;
}
