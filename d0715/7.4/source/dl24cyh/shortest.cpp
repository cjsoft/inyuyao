#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define iterate(_x, _i) for (edge *_i = head[_x]; _i; _i = _i->prev)
#define MOD 1000000007
#define MXN 100007
using namespace std;
typedef long long ll;
struct edge {
	int to;
	ll weight;
	edge *prev;
} buf[MXN << 1], *head[MXN], *cur;
inline void addedge(int a, int b, ll weight) {
	cur->prev = head[a];
	cur->to = b;
	cur->weight = weight;
	head[a] = cur++;
}
ll dist[MXN];
queue<int> q;
char inq[MXN];
void spfa(int s) {
	memset(inq, 0, sizeof(inq));
	memset(dist, 0x3f, sizeof(dist));
	dist[s] = 0;
	inq[s] = 1;
	q.push(s);
	while (!q.empty()) {
		static int u, v, w;
		u = q.front();
		iterate(u, i) {
			v = i->to;
			w = i->weight;
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				if (!inq[v]) {
					inq[v] = 1;
					q.push(v);
				}
			}
		}
		q.pop();
		inq[u] = 0;
	}
}
int n, m;
inline int getint() {
	static int f, rtn;
	static char ch;
	f = 1; rtn = 0;
	while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
	rtn = ch - '0';
	while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
	return rtn * f;
}
int main() {
	freopen("shortest.in", "r", stdin);
	freopen("shortest.out", "w", stdout);
	n = getint(); m = getint();
	cur = buf;
	for (int i = 0; i < m; ++i) {
		static int u, v, x;
		u = getint(); v = getint(); x = getint();
		addedge(u, v, 1 << x);
		addedge(v, u, 1 << x);
	}
	int s = getint(), t = getint();
	spfa(s);
	if (dist[t] != dist[MXN - 1]) printf("%lld\n", dist[t] % MOD);
	else puts("-1");
	return 0;
}
