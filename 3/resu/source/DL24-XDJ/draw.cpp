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
	#define LLD "%I64d"
	#define LLU "%I64u"
#else
	#define LLD "%lld"
	#define LLU "%llu"
#endif

typedef long long LL;// NOLINT
typedef long double real;

const double INF = 1e100;
const int oo = ~0u >> 2;
const double pi = acos(-1.0);
const double EPS = 1e-8;
const int MAXN = 3010;

inline void read(int &x) {
	x = 0;
	char c = getchar();
	while (c < '0'|| c > '9') c = getchar();
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
}

int n, used[MAXN], h[MAXN], p[MAXN], d[MAXN], status[MAXN];
LL ans;
int x, y, z;
struct Edge {
	int t, w, x;
} e[MAXN << 1];
int head[MAXN], cnt = 1;
inline void add(int s, int t, int w) {
	e[++cnt].t = t; e[cnt].x = head[s]; head[s] = cnt; e[cnt].w = w;
	e[++cnt].t = s; e[cnt].x = head[t]; head[t] = cnt; e[cnt].w = w;
}
typedef std::pair<int, int> PII;
std::vector<PII> edges;
int ssss = 0;
struct node {
	int n;
	std::vector<int> zn;
	node() {
		node(0);
	}
	inline node(int n):n(n) {
		zn.resize(2 * n + 1);
		zn[n] = 1;
	}
	int& operator [] (int idx) {
		if (idx < -n || idx > n) return ssss;
		return zn[idx + n];
	}
	int operator [] (int idx) const {
		if (idx < -n || idx > n) return 0;
		return zn[idx + n];
	}
};
inline void add(node& a, node& b, int sh) {
	g(i, -b.n, b.n) a[i + sh] += b[i];
}
inline void sub(node& a, node& b, int sh) {
	g(i, -b.n, b.n) a[i + sh] -= b[i];
}
LL mult(node& a, node& b, int sh) {
	LL res = 0;
	g(i, -b.n, b.n) res += LL(a[-(i + sh)]) * b[i];
	//printf("%d %d\n", b.n - sh + a.n, -b.n - sh + a.n);
//	printf(LLD"???\n", res);
	return res;
}
node str[MAXN];
void init(int v) {
	status[v] = 1;
	str[v] = node(d[v]);
	used[v] = 1;
	for (int i = head[v]; i; i = e[i].x) {
		if (!used[e[i].t]) {
			init(e[i].t);
			add(str[v], str[e[i].t], 1);
		}
	}
}
void update(int v) {
	int now = 0, u = v;
	status[v] = 0;
	while (u != 0) {
		now += status[u];
		sub(str[p[u]], str[v], now + 1);
		add(str[p[u]], str[v], now - 1);
		u = p[u];
	}
	status[v] = -1;
}
LL calc(int v) {
	LL res = 0;
	int now = -status[v], u = v;
	while (u != 0) {
		now += status[u];
		res += mult(str[p[u]], str[v], now);
		res -= mult(str[u], str[v], now + status[u]);
//	printf(LLD"``\n", res);
		u = p[u];
	}
	return res;
}
void dfs(int v, int vv, int hh) {
	h[v] = hh; p[v] = vv; d[v] = 0;
	used[v] = 1;
	for (int i = head[v]; i; i = e[i].x) {
		if (!used[e[i].t]) {
			dfs(e[i].t, v, hh + 1);
			d[v] = std::max(d[v], d[e[i].t] + 1);
		}
	}
}
int main() {
#ifndef LOCAL
	freopen("draw.in", "r", stdin);
	freopen("draw.out", "w", stdout);
#endif

	read(n);
	f(i, 1, n) {
		read(x); read(y); read(z);
		--x; --y;
		add(x, y, z);
	}
	ans = 0;
	memset(used, 0, sizeof used);
	dfs(0, 0, 0);
	memset(used, 0, sizeof used);
	init(0);
//	f(i, 0, n) printf("%d ", h[i]); puts("");
	f(i, 0, n) for (int j = head[i]; j; j = e[j].x) {
		if (h[i] > h[e[j].t]) edges.push_back(PII(e[j].w, i));
	}
	 //printf("%d\n", edges.size());
	std::sort(edges.begin(), edges.end());
	f(i, 0, edges.size()) {
	//	printf("%d %d\n", edges[i].first, edges[i].second);
		ans += LL(calc(edges[i].second)) * 1LL * edges[i].first;
		update(edges[i].second);
//		printf(LLD"\n", ans);
	}
	printf(LLD"\n", ans);

#ifndef LOCAL
	fclose(stdin);
	fclose(stdout);
#endif
	return 0;
}
/*
5
2 4 4
1 2 5
5 4 2
5 3 3
*/

