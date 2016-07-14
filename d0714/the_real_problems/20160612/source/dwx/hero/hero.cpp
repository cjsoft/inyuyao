#include <algorithm>
#include <iostream>
#include <climits>
#include <cstring>
#include <cstdio>
using namespace std;

#define Clear(a, b) memset(a, b, sizeof a)
#define min(a, b) ((a) < (b) ? (a) : (b))

template<class T>
inline bool GetMin(T &x, T y) {
	if (x > y) { x = y; return 1; }
	return 0;
}

const int N = 3e2 + 10;
const int Inf = INT_MAX;

int n, m;
int k, a[N][N];

void Init() {
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			scanf("%d", &a[i][j]);
}

int f[N][N][N];

void Solve() {
	Clear(f, 60);
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= m; ++j)
			if (i != j)
				f[1][i][j] = a[1][i] + a[1][j];
	for (int x = 1; x < n; ++x) {
		static int g[N][N];
		Clear(g, 60);
		for (int i = 1; i <= m; ++i)
			for (int j = 1; j <= m; ++j) {
				int &ng = g[i][j];
				ng = f[x][i][j] - k * (i + j);
				ng = min(ng, g[i - 1][j]);
				ng = min(ng, g[i][j - 1]);
				if (i != j) {
					int h = a[x + 1][i] + a[x + 1][j], &nf = f[x + 1][i][j];
					nf = min(nf, ng + k * (i + j) + h);
				}
			}
		for (int i = m; i; --i)
			for (int j = 1; j <= m; ++j) {
				int &ng = g[i][j];
				ng = f[x][i][j] + k * i - k * j;
				ng = min(ng, g[i + 1][j]);
				ng = min(ng, g[i][j - 1]);
				if (i != j) {
					int h = a[x + 1][i] + a[x + 1][j], &nf = f[x + 1][i][j];
					nf = min(nf, ng - k * i + k * j + h);
				}
			}
		for (int i = m; i; --i)
			for (int j = m; j; --j) {
				int &ng = g[i][j];
				ng = f[x][i][j] + k * (i + j);
				ng = min(ng, g[i + 1][j]);
				ng = min(ng, g[i][j + 1]);
				if (i != j) {
					int h = a[x + 1][i] + a[x + 1][j], &nf = f[x + 1][i][j];
					nf = min(nf, ng - k * (i + j) + h);
				}
			}
		for (int i = 1; i <= m; ++i)
			for (int j = m; j; --j) {
				int &ng = g[i][j];
				ng = f[x][i][j] - k * i + k * j;
				ng = min(ng, g[i - 1][j]);
				ng = min(ng, g[i][j + 1]);
				if (i != j) {
					int h = a[x + 1][i] + a[x + 1][j], &nf = f[x + 1][i][j];
					nf = min(nf, ng + k * i - k * j + h);
				}
			}
	}
	int ans = Inf;
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= m; ++j)
			GetMin(ans, f[n][i][j]);
	printf("%d\n", ans);
}

int main() {
	freopen("hero.in", "r", stdin);
	freopen("hero.out", "w", stdout);

	Init();
	Solve();

	return 0;
}
