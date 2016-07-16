#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
int n, K;
double dp[2][57][1007];
double dpm[2][57];
ll a[1007];
inline ll sum(int A, int B) { return a[B] - a[A - 1]; }
template <typename T>
inline void checkmin(T &a, T b) { if (a > b) a = b; }
double gmin(int fnow, int i, int j) {
		if (j == 1) return dp[fnow][1][i];
		else {
			double m = double((int)0x3fffffff);
			for (int k = 1; k <= i - j + 1; ++k) {
				checkmin(m, dp[fnow][j][k]);
			}
			return m;
		}
}
int main() {
	freopen("math.in", "r", stdin);
	freopen("math.out", "w", stdout);
	scanf("%d %d", &n, &K);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", a + i);
		a[i] += a[i - 1];
	}
	int tmp;
	int now = 0, last = 1;
	dp[now][1][1] = 100000;
	dpm[now][1] = 100000;
	for (int i = 1; i <= n; ++i) {
		tmp = min(K, i);
		for (int j = 1; j <= tmp; ++j) {
			dpm[now][j] = double((int)0x3fffffff) * 100000.;
			for (int k = 1; k <= i - j + 1; ++k) {
				if (j >= 2) {
					if (k >= 2) {
						dp[now][j][k] = dp[last][j][k - 1] + 100000. * sum(i - k + 1, i) / (double)sum(i, i);
					} else {
						if (j == 2) {
							dp[now][j][1] = dp[last][1][i - 1] + 100000;
						} else {
							dp[now][j][1] = dpm[last][j - 1] + 100000;
						}
						// dp[now][j][1] = gmin(last, i - 1, j - 1) + 1;
					}
				} else {
					dp[now][1][i] = dp[last][1][i - 1] + 100000. * sum(1, i) / (double)sum(i, i);
				}
				checkmin(dpm[now][j], dp[now][j][1]);
			}
		}
		swap(now, last);
	}
	double ans = double((int)0x3fffffff);
	if (K == 1) {
		ans = dp[last][K][n] / 100000.;
	} else {
		for (int i = 1; i <= n - K + 1; ++i) checkmin(ans, dp[last][K][i] / 100000.);
	}
	// for (int i = 1; i <= n; ++i) {
	printf("%.10lf\n", ans);
	// }
}
