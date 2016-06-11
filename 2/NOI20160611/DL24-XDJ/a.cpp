/**
 * @author SCaffrey(sirius.caffrey@gmail.com)
 * @copyright MIT
 */
#include <cstdio>// NOLINT
#include <cstring>// NOLINT
#include <bits/stdc++.h>// NOLINT
#include <cmath>// NOLINT
#define x1 x11
#define y1 y11

#define f(x, y, z) for (int x = (y), __ = (z); x < __; ++x)
#define g(x, y, z) for (int x = (y), __ = (z); x <= __; ++x)
#define fd(x, y, z) for (int x = (y), __ = (z); x > __; --x)
#define gd(x, y, z) for (int x = (y), __ = (z); x >= __; --x)

#ifdef WIN32
  #define intD "%I64d"
  #define intU "%I64u"
#else
  #define intD "%lld"
  #define intU "%llu"
#endif

typedef long long LL;// NOLINT
typedef long double real;

const double INF = 1e100;
const int oo = ~0u >> 2;
const double pi = acos(-1.0);
const double EPS = 1e-8;
const int MAXN = 200033;

int n, m, q;
int a[MAXN];
int b[MAXN];
int x, y;
int k;
int ans;
int s[4];
struct edge {
	int t, x;
} e[MAXN * 2];
int head[MAXN], cnt = 1;
inline void add(int s, int t) {
	e[++cnt].t = t; e[cnt].x = head[s]; head[s] = cnt;
}
int dep[MAXN], sz[MAXN], pos[MAXN], belong[MAXN];
int idx;
int fa[MAXN][19];
void dfs1(int x) {
	sz[x] = 1;
	g(i, 1, 18) {
		if (dep[x] < (1 << i)) break;
		fa[x][i] = fa[ fa[x][i - 1] ][i - 1];
	}
	for (int i = head[x]; i; i = e[i].x) {
		if (sz[e[i].t]) continue;
		dep[e[i].t] = dep[x] + 1;
		fa[e[i].t][0] = x;
		dfs1(e[i].t);
		sz[x] += sz[e[i].t];
	}
}
void dfs2(int x, int ff) {
	int k = 0;
	pos[x] = ++idx; belong[x] = ff;
	for (int i = head[x]; i; i = e[i].x) {
		if (dep[e[i].t] < dep[x]) continue;
		if (sz[e[i].t] > sz[k]) k = e[i].t;
	}
	if (!k) return;
	dfs2(k, ff);
	for (int i = head[x]; i; i = e[i].x) {
		if (dep[e[i].t] < dep[x] || e[i].t == k) continue;
		dfs2(e[i].t, e[i].t);
	}
}
int lca(int x, int y) {
	if (dep[x] < dep[y]) std::swap(x, y);
	int t = dep[x] - dep[y];
	g(i, 0, 18) if (t & (1 << i)) x = fa[x][i];
	gd(i, 18, 0) if (fa[x][i] != fa[y][i]) {
		x = fa[x][i]; y = fa[y][i];
	}
	if (x == y) return x;
	return fa[x][0];
}
struct node {
  int l, r, md;
  int sum;
  node *ls, *rs;
} pool[MAXN * 20], *tail;
node* root[MAXN];
node* build(int ll, int rr) {
  node* ans = tail++;
  ans->l = ll; ans->r = rr; ans->md = (ll + (rr - ll >> 1));
  ans->sum = 0;
  if (ll == rr) {
    ans->ls = ans->rs = NULL;
    return ans;
  }
  ans->ls = build(ll, ans->md); ans->rs = build(ans->md + 1, rr);
  return ans;
}
node* update(const node* x, int v) {
  node* ans = tail++;
  ans->sum = x->sum + 1;
  ans->l = x->l; ans->r = x->r; ans->md = x->md;
  ans->ls = x->ls; ans->rs = x->rs;
  if (x->l == x->r) return ans;
  if (v <= ans->md) {
    ans->ls = update(x->ls, v);
  } else {
    ans->rs = update(x->rs, v);
  }
  return ans;
}
int query(node* p1, node* p2, int ll, int rr) {
	if (p1->l == ll && p1->r == rr) {
		return p2->sum - p1->sum;
	}
	if (ll > p1->md) return query(p1->rs, p2->rs, ll, rr);
	if (rr <= p1->md) return query(p1->ls, p2->ls, ll, rr);
	return query(p1->ls, p2->ls, ll, p1->md) + query(p1->rs, p2->rs, p1->md + 1, rr);
}
int get(int x, int f, int k) {
	int res = 0;
	while (belong[x] != belong[f]) {
		res += query(root[pos[belong[x]] - 1], root[pos[x]], 1, k);
		x = fa[belong[x]][0];
	}
	res += query(root[pos[f] - 1], root[pos[x]], 1, k);
	return res;
}
int solve(int x, int y, int k) {
	int lc = lca(x, y);
	int res = 0;
	res += get(x, lc, k);
//	puts("");
	res += get(y, lc, k);
	if (a[lc] <= k) --res;
	return res;
//	puts("");
//	printf("%d %d lc:%d\n", x, y, lc);
//	puts("\n");
}
int main() {
#ifndef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

	scanf("%d%d%d", &n, &m, &q);
	tail = pool;
	g(i, 1, n) scanf(intD, a + i);
	f(i, 1, n) {
		scanf("%d%d", &x, &y);
		add(x, y);
		add(y, x);
	}
	dfs1(1);
	dfs2(1, 1);
	root[0] = build(1, 131072);
	g(i, 1, n) b[pos[i]] = a[i];
  g(i, 1, n) {
    root[i] = update(root[i - 1], b[i]);
  }
//	root = new seg(1, n);
	while (q--) {
		scanf("%d%d%d", &x, &y, &k);
		//printf("%d: %d %d %d\n", ans, x, y, k);
		x ^= ans; y ^= ans; k ^= ans;
//		printf("%d: %d %d %d\n", ans, x, y, k);
		s[0] = solve(x, y, k - 1);
		s[1] = solve(x, y, k);
		s[2] = solve(x, y, 131072);
//		printf("%d %d %d\n", s[0], s[1], s[2]);
		s[2] = s[2] - s[1];
		s[1] = s[1] - s[0];
		ans = 0;
		f(i, 0, 3) ans ^= s[i];
		printf("%d %d %d\n", s[0], s[1], s[2]);
	}
//	g(i, 1, n) printf("%d ", pos[i]); puts("");
//	g(i, 1, n) printf("%d ", belong[i]); puts("");

#ifndef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}
/*
5 5 4
3 4 2 3 3
2 4
5 1
1 3
2 1
2 5 2
6 7 0
7 7 0
2 4 2

5 5 1
3 4 2 3 3
2 4
5 1
1 3
2 1
5 4 3
*/

