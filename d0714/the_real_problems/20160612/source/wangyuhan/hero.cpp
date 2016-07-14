#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); ++i)
#define red(i, a, b) for(int i = (a); i >= (b); --i)
#define ll long long
#define abs ABS
#define sqr SQR
#define PII pair<int, int>
#define MP make_pair
#define PB push_back
#define FI first
#define SE second

template<typename tn> void read(tn& a) {
	tn x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) {
		if (c == '-') f = -1;
		c = getchar();
	}
	while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
	a = x * f;
}
template<typename tn> void cmax(tn& a, tn b) { if (b > a) a = b; }
template<typename tn> void cmin(tn& a, tn b) { if (b < a) a = b; }
template<typename tn> tn abs(tn a) { return a < 0 ? -a : a; }
template<typename tn> tn sqr(tn a) { return a * a; }

const int N = 330, NN = N * N * 2;
const int inf_int = 1000000000;
const ll inf = 100000000ll * 100000000ll;
int n, m, K, tot, tail = 1, S, T;
ll d[NN];
int head[NN], a[NN], inq[NN], p[NN], c[N][N];
struct edge {
	int from, to, cap, flow;
	ll cost;
	int nxt;
}e[NN * 15];
int q[NN * 50];

void addedge(int from, int to, int cap, int cost) {
	e[++tail] = (edge){from, to, cap, 0, cost, head[from]}; head[from] = tail;
	e[++tail] = (edge){to, from, 0, 0, -cost, head[to]}; head[to] = tail;
}
void Build_Graph() {
	tot = n * m * 2 + 1 + 2; 
	rep(i, 0, tot) head[i] = -1;
	S = n * m * 2 + 1; T = S + 1;
	addedge(S, 0, 2, 0);
	rep(i, 1, m) addedge(0, i, 1, 0);
	for(int rd = 1, sum = 0; rd <= n; ++rd, sum += m * 2) {
		int s1 = sum + 1, s2 = s1 + m, s3 = s2 + m;
		int t1 = sum + m, t2 = t1 + m, t3 = t2 + m;
		for(int lp = s1, rp = s2; lp <= t1; ++lp, ++rp)
			addedge(lp, rp, 1, c[rd][lp - sum]);
		if (rd < n) {
			for(int lp = s2, rp = s3; lp <= t2; ++lp, ++rp) {
				addedge(lp, rp, inf_int, 0);
				if (lp < t2) addedge(lp, lp + 1, inf_int, K);
				if (rp > s3) addedge(rp, rp - 1, inf_int, K);
			}
		}else {
			for(int lp = s2; lp <= t2; ++lp)
				addedge(lp, T, 1, 0);
		}
	}
}
bool SPFA(int s, int t, int& flow, ll& cost) {
	int l, r;
	rep(i, 0, tot) d[i] = inf;
	memset(inq, 0, sizeof(inq));
	d[s] = 0; inq[s] = 1; a[s] = inf_int; p[s] = -1;
	q[l = r = 1] = s;
	while(l <= r) {
		int u = q[l++]; inq[u] = 0;
		for(int i = head[u]; i != -1; i = e[i].nxt) {
			edge& E = e[i];
			if (E.cap > E.flow && d[E.to] > d[u] + E.cost) {
				d[E.to] = d[u] + E.cost;
				p[E.to] = i;
				a[E.to] = min(a[u], E.cap - E.flow);
				if (!inq[E.to]) q[++r] = E.to, inq[E.to] = 1;
			}
		}
	}
	if (d[t] == inf) return 0;
	flow += a[t];
	cost += (ll)(a[t]) * d[t];
	int u = t;
	while(u != s) {
		e[p[u]].flow += a[t];
		e[p[u] ^ 1].flow -= a[t];
		u = e[p[u]].from;
	}
	return 1;
}
ll MinCost() {
	int flow = 0; ll cost = 0;
	while(SPFA(S, T, flow, cost));
	return cost;
}
int main() {
	freopen("hero.in", "r", stdin);
	freopen("hero.out", "w", stdout);
	read(n); read(m); read(K);
	rep(i, 1, n) rep(j, 1, m) read(c[i][j]);
	Build_Graph();
	ll ans = MinCost();
	printf("%lld\n", ans);
	return 0;
}