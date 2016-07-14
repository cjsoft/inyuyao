#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

#define Clear(a, b) memset(a, b, sizeof a)

typedef long double db;

const int N = 30;

int n, m, l[N], r[N], x[N];
db y[N];

void Init() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &l[i]);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &r[i]);
		x[i] = r[i] - l[i] + 1;
		y[i] = (db)1 / x[i];
	}
	scanf("%d", &m);
}

db f[N][N][2][2], g[N][N][2][2];
db h[N][2];

void Solve() {
	for (int k = 0; k <= 1e3; ++k) {
		Clear(f, 0);
		f[0][0][0][0] = 1;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j <= i; ++j)
				for (int a = 0; a < 2; ++a)
					for (int b = 0; b < 2; ++b) {
						if (l[i + 1] <= k && k <= r[i + 1]) { // exactly the score(k)
							db p = f[i][j][a][b] * y[i + 1];
							if (!b)
								f[i + 1][j + 1][1][0] += p; // in
							f[i + 1][j][a][1] += p; // out
						}
						int v = max(0, min(r[i + 1] - k, x[i + 1]));
						f[i + 1][j + 1][a][b] += f[i][j][a][b] * v * y[i + 1]; // >
						v = max(0, min(k - l[i + 1], x[i + 1]));
						f[i + 1][j][a][b] += f[i][j][a][b] * v * y[i + 1]; // <
					}
		Clear(g, 0);
		g[n + 1][0][0][0] = 1;
		for (int i = n + 1; i > 1; --i)
			for (int j = 0; j <= n - i + 1; ++j)
				for (int a = 0; a < 2; ++a)
					for (int b = 0; b < 2; ++b) {
						if (l[i - 1] <= k && k <= r[i - 1]) { // exactly the score(k)
							db p = g[i][j][a][b] * y[i - 1];
							g[i - 1][j + 1][1][b] += p; // in
							if (!a)
								g[i - 1][j][0][1] += p; // out
						}
						int v = max(0, min(r[i - 1] - k, x[i - 1]));
						g[i - 1][j + 1][a][b] += g[i][j][a][b] * v * y[i - 1]; // >
						v = max(0, min(k - l[i - 1], x[i - 1]));
						g[i - 1][j][a][b] += g[i][j][a][b] * v * y[i - 1]; // <
					}
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < i && j < m; ++j) {
				int t = 1;
				if ((j + 1) % 4 <= 1)
					t = 0;
				int _j = m - j - 1;
				for (int a = 0; a < 2; ++a)
					for (int b = 0; b < 2; ++b)
						for (int c = 0; c < 2; ++c)
							for (int d = 0; d < 2; ++d) {
								if (b && c) continue;
								db p = f[i - 1][j][a][b] * g[i + 1][_j][c][d];
								if (a || c) {
									int v = max(0, min(r[i] - k, x[i]));
									h[i][t] += p * v * y[i];
								}
								if (l[i] <= k && k <= r[i] && !b) 
									h[i][t] += p * y[i];
							}
			}
		}
	}
	for (int i = 1; i <= n; ++i)
		printf("%.6f %.6f\n", (double)h[i][0], (double)h[i][1]);
}

int main() {
	freopen("assign.in", "r", stdin);
	freopen("assign.out", "w", stdout);

	Init();
	Solve();

	return 0;
}
