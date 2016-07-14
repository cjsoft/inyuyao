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

const int MAXN = 303;
int N, M, K;
int V[MAXN][MAXN];
LL F[MAXN][MAXN], G[4][MAXN][MAXN];
const int dx[4] = {-1, -1, 1, 1};
const int dy[4] = {1, -1, -1, 1};
int main(int argc, char *argv[]){
#define PROB "hero"
#ifndef ONLINE_JUDGE
	freopen(PROB".in", "r", stdin);
	freopen(PROB".out", "w", stdout);
#endif
	read(N); read(M); read(K);
	rep(i, 1, N) rep(j, 1, M) read(V[i][j]);
	rep(d, 0, 3) rep(i, 0, M + 1) G[d][i][0] = G[d][0][i] = G[d][M + 1][i] = G[d][i][M + 1] = INF_LL >> 3;
	rep(T, 1, N){
		//debug("T = %d\n", T);
		rep(i, 1, M) rep(j, 1, M){
			F[i][j] = INF_LL >> 3;
			if (i != j){
				if (T == 1) F[i][j] = 0;
				else
					rep(d, 0, 3)
						cmin(F[i][j], G[d][i][j] - (dx[d] * i + dy[d] * j) * K);
				F[i][j] += V[T][i] + V[T][j];
				//debug("[%d][%d] = %lld\n", i, j, F[i][j]);
			}
		}
		rep(d, 0, 3)
			rep(i, 1, M) rep(j, 1, M)
				G[d][i][j] = F[i][j] + (dx[d] * i + dy[d] * j) * K;
		rep(i, 1, M) red(j, M, 1)
			cmin(G[0][i][j], min(G[0][i - 1][j], G[0][i][j + 1]));
		rep(i, 1, M) rep(j, 1, M)
			cmin(G[1][i][j], min(G[1][i - 1][j], G[1][i][j - 1]));
		red(i, M, 1) rep(j, 1, M)
			cmin(G[2][i][j], min(G[2][i + 1][j], G[2][i][j - 1]));
		red(i, M, 1) red(j, M, 1)
			cmin(G[3][i][j], min(G[3][i + 1][j], G[3][i][j + 1]));
	}
	LL ans = INF_LL;
	rep(i, 1, M) rep(j, 1, M) cmin(ans, F[i][j]);
	printf("%lld\n", ans);
	return 0;
}
