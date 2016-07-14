#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <climits>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') f = -1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
	return x * f;
}

const int maxn = 200005, maxm = 5001005;
int n, m, K, S, T, SS;
int t[305][305];
struct edge{
	int to, next, c, w;
}e[maxm << 1];
int head[maxn], top = 1;

void addedge(int u, int v, int c, int w) {
	e[++top] = (edge) {v, head[u], c, w}; head[u] = top;
	e[++top] = (edge) {u, head[v], 0, -w}; head[v] = top;
}

int get_id1(int x, int y) {
	return (x - 1) * m + y;
}

int get_id2(int x, int y) {
	return n * m + (x - 1) * m + y;
}

long long dis[maxn];
int pre[maxn];
bool vis[maxn];
queue<int> q;
bool spfa() {
	for (int i = S; i <= T; i++) dis[i] = inf;
	dis[S] = 0; q.push(S);
	while(!q.empty()) {
		int pos = q.front(); q.pop(); vis[pos] = false;
 		for (int i = head[pos]; i; i = e[i].next) if (e[i].c && dis[e[i].to] > dis[pos] + e[i].w) {
			dis[e[i].to] = dis[pos] + e[i].w;
			pre[e[i].to] = i;
			if (!vis[e[i].to]) vis[e[i].to] = true, q.push(e[i].to);
		}
	}
	return dis[T] != inf;
}

long long ans = 0;

void end() {
	int flow = inf;
	for (int pos = T, i; pos != S; pos = e[i ^ 1].to) {
		i = pre[pos];
		flow = min(flow, e[i].c);
	}
	for (int pos = T, i; pos != S; pos = e[i ^ 1].to) {
		i = pre[pos];
		e[i].c -= flow, e[i ^ 1].c += flow;
		ans += flow * e[i].w;
	}
}

int main() {
	freopen("hero.in", "r", stdin);
	freopen("hero.out", "w", stdout);
	n = read(), m = read(), K = read(); S = 0, SS = 2 * n * m + 1, T = SS + 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) t[i][j] = read();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) 
			addedge(get_id1(i, j), get_id2(i, j), 1, t[i][j]);
	for (int i = 1; i < n; i++)
		for (int j = 1; j <= m; j++)
			for (int k = 1; k <= m; k++) 
				addedge(get_id2(i, j), get_id1(i + 1, k), 1, K * abs(j - k));
	for (int i = 1; i <= m; i++) 
		addedge(SS, get_id1(1, i), 1, 0), addedge(get_id2(n, i), T, 1, 0);
	addedge(S, SS, 2, 0);
	while(spfa())
		end();
	printf("%lld\n", ans);
	return 0;
}
