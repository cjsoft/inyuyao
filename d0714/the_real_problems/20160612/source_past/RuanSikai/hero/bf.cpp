#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int maxn = 305;

int n, m, k, c[maxn][maxn];
LL dp[2][maxn][maxn];

inline int iread() {
	int f = 1, x = 0; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) f = ch == '-' ? -1 : 1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
	return f * x;
}

inline int iabs(int x) {
	return x < 0 ? -x : x;
}

int main() {
	freopen("hero.in", "r", stdin);
	freopen("hero.ans", "w", stdout);
	n = iread(); m = iread(); k = iread();
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) c[i][j] = iread();

	memset(dp[1], 0x3f, sizeof(dp[1]));
	for(int i = 1; i <= m; i++) for(int j = i + 1; j <= m; j++) dp[1][i][j] = c[1][i] + c[1][j];

	for(int l = 2; l <= n; l++) {
		memset(dp[l & 1], 0x3f, sizeof(dp[l & 1]));
		for(int i = 1; i <= m; i++) for(int j = i + 1; j <= m; j++)
			for(int i2 = 1; i2 <= m; i2++) for(int j2 = i2 + 1; j2 <= m; j2++)
				dp[l & 1][i2][j2] = min(dp[l & 1][i2][j2], dp[~l & 1][i][j] + (LL)k * iabs(i2 - i) + (LL)k * iabs(j2 - j) + c[l][i2] + c[l][j2]);
	}

	LL ans = 0x3f3f3f3f3f3f3f3fLL;
	for(int i = 1; i <= m; i++) for(int j = i + 1; j <= m; j++)
		ans = min(ans, dp[n & 1][i][j]);
	printf("%lld\n", ans);
	return 0;
}

