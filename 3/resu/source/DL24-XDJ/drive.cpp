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
int dis[MAXN], vis[MAXN];
std::queue<int> Q;
int n;
int a, b;
int q;
int s, t;
struct edge {
	int t, x;
} e[MAXN * 4];
int head[MAXN], cnt = 1;
inline void add(int s, int t) {
	e[++cnt].t = t; e[cnt].x = head[s]; head[s] = cnt;
	e[++cnt].t = s; e[cnt].x = head[t]; head[t] = cnt;
}
typedef std::pair<int, int> PII;
std::vector<PII> G[MAXN];
int ans[MAXN];
int get(int s, int t, int id) {
	if (s == t) return 0;
	while (!Q.empty()) Q.pop();
	int u;
	dis[s] = 0; vis[s] = id; Q.push(s);
	while (!Q.empty()) {
		u = Q.front(); Q.pop();
		for (int i = head[u]; i; i = e[i].x) {
			if (e[i].t == t) {
				return dis[u] + 1;
			}
			if (vis[e[i].t] == id) continue;
			vis[e[i].t] = id;
			Q.push(e[i].t);
			dis[e[i].t] = dis[u] + 1;
		}
	}
}
void get(int s) {
	int u;
	dis[s] = 0; vis[s] = s; Q.push(s);
	while (!Q.empty()) {
		u = Q.front(); Q.pop();
		for (int i = head[u]; i; i = e[i].x) {
			if (vis[e[i].t] == s) continue;
			vis[e[i].t] = s;
			Q.push(e[i].t);
			dis[e[i].t] = dis[u] + 1;
		}
	}
	f(i, 0, G[s].size()) ans[G[s][i].second] = dis[G[s][i].first];
}
int main() {
#ifndef LOCAL
	freopen("drive.in", "r", stdin);
	freopen("drive.out", "w", stdout);
#endif

	read(n);
	f(i, 0, n - 3) {
		read(a); read(b);
		add(a, b);
		add(i + 1, i + 2);
	}
	f(i, n - 3, n - 1) add(i + 1, i + 2);
	add(n, 1);
	read(q);
	g(i, 1, q) {
		read(s); read(t);
		G[s].push_back(PII(t, i));
	}
	g(i, 1, n) if (G[i].size()) get(i);
	g(i, 1, q) printf("%d\n", ans[i]);

#ifndef LOCAL
	fclose(stdin);
	fclose(stdout);
#endif
	return 0;
}


