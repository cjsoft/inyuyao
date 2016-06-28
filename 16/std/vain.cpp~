# include <bits/stdc++.h>
using namespace std;
# define REP(i, n) for (int i = 1; i <= n; ++ i)
# define REP_D(i, n) for (int i = n; i >= 1; -- i)
# define REP_D0(i, n) for (int i = n - 1; i >= 0; -- i)
# define REP_G(i, x) for (int i = pos[x]; i; i = g[i].frt)
# define NR 1001000
const int BUF_SIZE = (int) 1e4 + 10;
struct fastIO {
	char buf[BUF_SIZE];
	int cur;
	FILE *in;
	fastIO () {
		cur = BUF_SIZE;
		in = stdin;
	}
	inline char nextChar () {
		if (cur == BUF_SIZE) {
			fread (buf, BUF_SIZE, 1, in);
			cur = 0;
		}
		return buf[cur++];
	}
	inline int nextInt () {
		int x = 0;
		char c = nextChar ();
		while (!('0' <= c && c <= '9')) c = nextChar ();
		while ('0' <= c && c <= '9') {
			x = x * 10 + c - '0';
			c = nextChar ();
		}
		return x;
	}
} IO;
struct Arr { int x, y, w; } e[NR];
struct Edge { int y, frt; } g[NR << 1];
const int inf = 1 << 30;
int n, m, gsz, pos[NR], dep[NR], f[NR][20], par[NR], ext[NR], fa[NR], ans[NR], maxw[NR], pre[NR], suf[NR], deg[NR], tf[NR];
bool ve[NR], acs[NR];
int gf (int x, int *f = fa) { return f[x] == x ? x : (f[x] = gf (f[x], f)); }
bool cmpE (const Arr &a, const Arr &b) { return a.w < b.w; }
void AE (int x, int y) { g[++ gsz] = (Edge) { y, pos[x] }, pos[x] = gsz; }
# define v g[i].y
void dfs (int x) {
	f[x][0] = par[x];
	for (int i = 1; (1 << i) <= dep[x]; ++ i) f[x][i] = f[f[x][i - 1]][i - 1];
	REP_G (i, x) if (v != par[x]) ++ deg[x], par[v] = x, dep[v] = dep[x] + 1, dfs (v);
}
int lca (int x, int y, int &tx, int &ty) {
	if (dep[x] < dep[y]) swap (x, y);
	REP_D0 (i, 20) if (dep[f[x][i]] >= dep[y]) x = f[x][i];
	if (x == y) return tx = -1, ty = -1, x;
	REP_D0 (i, 20) if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
	return tx = x, ty = y, par[x];
}
void crawl (int x, int y, int w) {
	for (x = gf (x); dep[par[x]] > dep[y]; x = gf (x)) {
		int z = par[x];
		if (!acs[gf (x, tf)]) {
			acs[gf (x, tf)] = true; -- deg[z];
			if (!deg[z]) ans[z] = min (ans[z], w == -1 ? max (pre[z - 1], suf[z + 1]) : w);
		}
		fa[x] = z;
	}
}
void add_path (int x, int y, int w) {
	if (dep[x] > dep[y]) swap (x, y);
	int _x, _y, z = lca (x, y, _x, _y);
	if (_x == -1) {
		assert (z == x);
		crawl (y, z, w);
	} else {
		_x = gf (_x, tf), _y = gf (_y, tf);
		if (_x != _y) {
			if (!acs[_x] || !acs[_y]) -- deg[z];
			tf[_x] = _y, acs[_y] |= acs[_x];
		}
		if (!deg[z]) ans[z] = min (ans[z], w == -1 ? max (pre[z - 1], suf[z + 1]) : w);
		crawl (x, z, w), crawl (y, z, w);
	}
}
int main () {
	freopen("vain.in","r",stdin);
	freopen("vain.out","w",stdout);
//	scanf("%d%d",&n,&m);
	n=IO.nextInt();
	m=IO.nextInt();
	int size = 256 << 20; // 256MB
    char *p = (char*)malloc(size) + size;
    __asm__("movl %0, %%esp\n" :: "r"(p));
	int tid = 0; dep[0] = -1;
	REP (i, n) pos[i] = maxw[i] = 0, ans[i] = ext[i] = inf, fa[i] = tf[i] = i, deg[i] = 0, acs[i] = false;
	REP (i, m) {
//		scanf ("%d%d%d", &e[i].x, &e[i].y, &e[i].w); 
		e[i].x=IO.nextInt();e[i].y=IO.nextInt();e[i].w=IO.nextInt();
		ve[i] = false;
		ext[e[i].x] = min (ext[e[i].x], e[i].w); ext[e[i].y] = min (ext[e[i].y], e[i].w);
	}
	sort (e + 1, e + m + 1, cmpE);
	int cnt = 0; gsz = 0;	
	REP (i, m) {
		int x = e[i].x, y = e[i].y;
		if (cnt == n - 1) {
			add_path (x, y, e[i].w);
		} else {
			int fx = gf (x), fy = gf (y);
			if (fx != fy) {
				fa[fx] = fy, ++ cnt, AE (x, y), AE (y, x), ve[i] = true, maxw[x] = max (maxw[x], e[i].w), maxw[y] = max (maxw[y], e[i].w);
				if (cnt == n - 1) {
					REP (j, n) pre[j] = max (maxw[j], pre[j - 1]);
					suf[n + 1] = 0;
					REP_D (j, n) suf[j] = max (maxw[j], suf[j + 1]);
					dfs (1);
					REP (j, n) {
						fa[j] = j;
						if (!deg[j]) ans[j] = max (pre[j - 1], suf[j + 1]);
					}
					-- deg[1];
					if (!deg[1]) ans[1] = suf[2];
					REP (j, i - 1) if (!ve[j]) {
						add_path (e[j].x, e[j].y, -1);
					}
				}
			}
		}
	}
	long long res=0;
	REP (i, n ) res+= ((ans[i] == inf) ? (-1) : (max (ans[i], ext[i])));
	REP (x, n) {
		f[x][0] = 0; for (int i = 1; (1 << i) <= dep[x]; ++ i) f[x][i] = 0;
	}
	std::cout<<res;
	return 0;
}
