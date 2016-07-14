#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define MEM(x, y) memset(x, y, sizeof(x))
#define cmin(x, y) ((x) = min((x), (y)))
#define cmax(x, y) ((x) = max((x), (y)))
#define X first
#define Y second

using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned int UI;
typedef unsigned long long ULL;
typedef pair<int, int> PI;

const int INF = 0x7fffffff;
const LL INF_LL = 0x7fffffffffffffffLL;
const LL MOD = 1000000007;
const LD eps = 1e-8;

template<typename T> void read(T& a){
	a = 0; char c; bool f = 0;
	while (!isdigit(c = getchar())) if (c == '-') f = 1;
	do a = a * 10 + c - '0'; while (isdigit(c = getchar()));
	if (f) a = -a;
}

const int MAXN = 30;
int L[MAXN], R[MAXN];
double P[MAXN], ans[MAXN][2];
double p[MAXN], q[MAXN];
int N, K;
int main(int argc, char *argv[]){
#define PROB "assign"
#ifndef ONLINE_JUDGE
	freopen(PROB".in", "r", stdin);
	freopen(PROB".out", "w", stdout);
#endif
	read(N);
	rep(i, 1, N) read(L[i]);
	rep(i, 1, N) read(R[i]);
	read(K);
	rep(i, 1, N){
		rep(j, 0, K - 1) P[j] = 0;
		debug("%d:\n", i);
		rep(c, L[i], R[i]){
			rep(j, 1, N) p[j] = q[j] = 0;
			p[0] = 1; q[0] = 1;
			rep(j, 1, i - 1){
				double v = (double)(R[j] - c + 1) / (R[j] - L[j] + 1);
				if (v < 0) v = 0; if (v > 1) v = 1;
				red(k, j, 1) p[k] = p[k] * (1 - v) + p[k - 1] * v;
				p[0] *= 1 - v;
			}
			rep(j, i + 1, N){
				double v = (double)(R[j] - c) / (R[j] - L[j] + 1);
				if (v < 0) v = 0; if (v > 1) v = 1;
				red(k, j, 1) q[k] = q[k] * (1 - v) + q[k - 1] * v;
				q[0] *= 1 - v;
			}
			debug("C = %d:\n	p=", c);
			rep(j, 0, N) debug("%.3lf ", p[j]);
			debug("\n	q=");
			rep(j, 0, N) debug("%.3lf ", q[j]);
			debug("\n");
			rep(j, 1, N) q[j] += q[j - 1];
			rep(j, 0, K - 1) P[j] += p[j] * q[K - j - 1];
		}
		
		rep(j, 0, K - 1){
			P[j] /= R[i] - L[i] + 1;
			debug("%.3lf%c", P[j], " \n"[j == K - 1]);
			ans[i][j % 4 == 0 || j % 4 == 3 ? 0 : 1] += P[j];
		}
	}
	rep(i, 1, N) printf("%lf %lf\n", ans[i][0], ans[i][1]);
	return 0;
}
