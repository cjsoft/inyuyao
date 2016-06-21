#include <iostream>
#include <cstdio>
#include <cstring>
#define MXN 160
#define MXK 25
#define MOD 12345678
int n, m, k, dp[2][MXN][MXK][MXK];
using namespace std;

int main() {
    int now = 0, last = 1;
    scanf("%d %d %d", &n, &m, &k);
    dp[now][0][0][0] = 1;
    for (int i = 0; i < n + m; ++i) {
        swap(now, last);
        memset(dp[now], 0, sizeof(dp[now]));
        for (int j = 0; j <= min(i, n); ++j) {
            for (int k1 = 0; k1 <= min(j, k); ++k1) {
                for (int k2 = 0; k2 <= min(i - j, k); ++k2) {
                    int T = dp[last][j][k1][k2];
                    if (k1 < k && j < n) dp[now][j + 1][k1 + 1][max(k2 - 1, 0)] = (dp[now][j + 1][k1 + 1][max(k2 - 1, 0)] + T) % MOD;
                    if (k2 < k && i - j < m) dp[now][j][max(k1 - 1, 0)][k2 + 1] = (dp[now][j][max(k1 - 1, 0)][k2 + 1] + T) % MOD;
                }
            }
        }
    }
    int ans = 0;
    for (int k1 = 0; k1 <= k; ++k1)
        for (int k2 = 0; k2 <= k; ++k2)
            ans = (ans + dp[now][n][k1][k2]) % MOD;
    printf("%d\n", ans);
    return 0;
}
