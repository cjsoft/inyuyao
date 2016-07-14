#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int maxg = 305, maxn = 180005, maxm = 2000005, maxq = 2000005, inf = 0x3f3f3f3f;
const LL linf = 0x3f3f3f3f3f3f3f3fLL;

int n, m, k, c[maxg][maxg], id[2][maxg][maxg], tot, head[maxn], cnt, bg, ed, way[maxn], q[maxq];
LL depth[maxn];
bool vis[maxn];

struct _edge {
	int v, w, c, next;
} g[maxm << 1];

inline int iread() {
	int f = 1, x = 0; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) f = ch == '-' ? -1 : 1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
	return f * x;
}

inline void add(int u, int v, int w, int c) {
	g[cnt] = (_edge){v, w, c, head[u]};
	head[u] = cnt++;
}

inline void insert(int u, int v, int w, int c) {
	add(u, v, w, c); add(v, u, 0, -c);
}

inline bool spfa() {
	for(int i = 0; i <= ed; i++) depth[i] = linf;
	int h = 0, t = 0, u, i; depth[q[t++] = bg] = 0;
	while(h != t) for(i = head[u = q[h]], h == maxq - 1 ? h = 0 : h++, vis[u] = 0; ~i; i = g[i].next) if(g[i].w && depth[g[i].v] > depth[u] + g[i].c) {
		depth[g[i].v] = depth[u] + g[i].c;
		way[g[i].v] = i;
		if(!vis[g[i].v]) vis[q[t] = g[i].v] = 1, t == maxq - 1 ? t = 0 : t++;
	}
	return depth[ed] != linf;
}

inline LL back() {
	int flow = inf;
	LL res = 0;
	for(int u = ed; u != bg; u = g[way[u] ^ 1].v) flow = min(flow, g[way[u]].w);
	for(int u = ed; u != bg; u = g[way[u] ^ 1].v) g[way[u]].w -= flow, g[way[u] ^ 1].w += flow, res += (LL)flow * g[way[u]].c;
	return res;
}		

int main() {
	freopen("hero.in", "r", stdin);
	freopen("hero.out", "w", stdout);
	n = iread(); m = iread(); k = iread(); bg = 0; int tbg = ++tot;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) c[i][j] = iread(), id[0][i][j] = ++tot, id[1][i][j] = ++tot;
	ed = ++tot;

	for(int i = 0; i <= ed; i++) head[i] = -1; cnt = 0;

	insert(bg, tbg, 2, 0);
	for(int i = 1; i <= m; i++) insert(tbg, id[0][1][i], 1, c[1][i]), insert(id[1][n][i], ed, 1, 0);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
		insert(id[0][i][j], id[1][i][j], 1, 0);
		if(i != n) insert(id[1][i][j], id[0][i + 1][j], 1, c[i + 1][j]);
		if(j != 1) insert(id[0][i][j], id[0][i][j - 1], inf, k), insert(id[0][i][j - 1], id[0][i][j], inf, k);
		if(j != m) insert(id[0][i][j], id[0][i][j + 1], inf, k), insert(id[0][i][j + 1], id[0][i][j], inf, k);
	}

	LL ans = 0;
	while(spfa()) ans += back();

	printf("%lld\n", ans);
	return 0;
}

