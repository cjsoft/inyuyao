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
const int MAXN = 100033;

inline void read(int &x) {
	x = 0;
	char c = getchar();
	while (c < '0'|| c > '9') c = getchar();
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
}
const int MOD = 1e9 + 7;
int n, m, T;
int u, v, w;
struct edge {
	int t, w, x;
} e[MAXN];
int head[MAXN], cnt = 1;
inline void add(int s, int t, int w) {
	e[++cnt].t = t; e[cnt].x = head[s]; head[s] = cnt; e[cnt].w = w;
	e[++cnt].t = s; e[cnt].x = head[t]; head[t] = cnt; e[cnt].w = w;
}
typedef std::pair<int, int> PII;
std::priority_queue<PII, std::vector<PII>, std::greater<PII> > PQ;
int sssp[MAXN];
int dis[MAXN];
int dep[MAXN];
bool vis[MAXN];
LL ans = 0;
void dij() {
	dis[1] = 0;
	g(i, 2, n) dis[i] = oo;
	while (!PQ.empty()) PQ.pop();
	PQ.push(PII(0, 1));
	PII tee;
	int u;
	while (!PQ.empty()) {
		tee = PQ.top(); PQ.pop();
		u = tee.second;
		if (dis[u] < tee.first) continue;
		for (int i = head[u]; i; i = e[i].x) {
			if (dis[e[i].t] - dis[u] > e[i].w) {
				dis[e[i].t] = dis[u] + e[i].w;
				PQ.push(PII(dis[e[i].t], e[i].t));
			}
		}
	}
}
int main() {
#ifndef LOCAL
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif

	read(n); read(m); read(T);
	f(i, 0, m) {
		read(u); read(v); read(w);
		add(u, v, w - 1);
	}
	ans = 0;
	g(ti, 0, T) {
		g(i, 2, cnt) e[i].w += 1;
		dij();
		g(i, 1, n) {
			ans = (ans + dis[i]) % MOD;
		}
	}
	printf(LLD"\n", ans);

#ifndef LOCAL
	fclose(stdin);
	fclose(stdout);
#endif
	return 0;
}



