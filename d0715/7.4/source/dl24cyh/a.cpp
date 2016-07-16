#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
double dp[2][1007][1007];
int a[1007];
int n, K;
int sum(int A, int b) {
	return a[b] - a[A - 1];
}
template <typename T>
inline void checkmin(T &a, T b) { if (b < a) a = b; }
int main() {
	int now = 0, last = 1;
	scanf("%d %d", &n, &K);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		a[i] += a[i - 1];
	}
	dp[0][1][1] = 1;
	int tmp;
	for (int i = 1; i <= n; ++i) {
		tmp = min(i, K);
		for (int j = 2; j <= tmp; ++j) {
			for (int k = 2; k <= i - j + 1; ++k) {
				if (i == 2 && j == 1 && k == 2)
					puts("sd");
				if (k > 1 && !(k - 1 < i && j == 1)) dp[now][j][k] = dp[last][j][k - 1] + sum(i - k + 1, i) / (double)sum(i, i);
			}
		}
		dp[now][1][i] = dp[last][1][i - 1] + sum(1, i) / (double)sum(i, i);
		for (int j = 2; j <= tmp; ++j) {
			if (i == 3 && j == 2)
				puts("sd");
			dp[now][j][1] = double((int)0x3fffffff);
			for (int k = 1; k <= i - j + 1; ++k) {
				if (j - 1 > 0 && !(k - 1 < i && j == 2)) checkmin(dp[now][j][1], dp[last][j - 1][k] + 1);
			}
			if (j == 2) checkmin(dp[now][j][1], dp[last][j - 1][i]);
			if (i - j < 0) {
				dp[now][j][1] = double((int)0x3fffffff);
				puts("s");
			}
		}
		// if (i <= K) dp[now][1][1] = dp[last][1][1] + 1;
		// else dp[now][1][1] = double((int)0x3fffffff);
		swap(now, last);
	}
	double ans = double((int)0x3fffffff);
	for (int i = 1; i <= n; ++i) {
		printf("   %.10lf\n", dp[last][K][i]);
	}
	for (int i = K - 1; i <= min(n, n - K + 1); ++i) {
		checkmin(ans, dp[last][K][i]);
	}
	printf("%.10lf\n", ans);
	return 0;
}
