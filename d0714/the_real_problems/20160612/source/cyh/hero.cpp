#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MXN 307
#define INF 0x3fffffff
using namespace std;
typedef long long ll;
int n, m;
ll K;
ll cost[MXN][MXN];
ll dp[MXN][MXN];
inline bool checkmin(ll &, ll);
inline ll getll();


int main() {
    freopen("hero.in", "r", stdin);
    freopen("hero.out", "w", stdout);
    n = getll(); m = getll(); K = getll();
    // memset(cost, 31, sizeof(cost));
    // memset(dp, 31, sizeof(dp));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cost[i][j] = getll();
        }
    }
    for (int i = 0; i <= m + 1; ++i) {
        for (int j = 0; j <= m + 1; ++j) {
            if (i > 0 && j <= m && i < j) dp[i][j] = 0;
            else dp[i][j] = INF;
        }
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            for (int k = j + 1; k <= m; ++k) {
                dp[j][k] += cost[i][j] + cost[i][k];
            }
        }
        for (int j = 1; j < m; ++j) {
            for (int k = j + 1; k <= m; ++k) {
                checkmin(dp[j][k], dp[j - 1][k] + K);
                checkmin(dp[j][k], dp[j][k - 1] + K);
            }
        }
        for (int j = 1; j < m; ++j) {
            for (int k = m; k > j; --k) {
                checkmin(dp[j][k], dp[j - 1][k] + K);
                checkmin(dp[j][k], dp[j][k + 1] + K);
            }
        }
        for (int j = m - 1; j >= 1; --j) {
            for (int k = j + 1; k <= m; ++k) {
                checkmin(dp[j][k], dp[j + 1][k] + K);
                checkmin(dp[j][k], dp[j][k - 1] + K);
            }
        }
        for (int j = m - 1; j >= 1; --j) {
            for (int k = m; k > j; --k) {
                checkmin(dp[j][k], dp[j + 1][k] + K);
                checkmin(dp[j][k], dp[j][k + 1] + K);
            }
        }
    }
    for (int i = 1; i < m; ++i) {
        for (int j = i + 1; j <= m; ++j) {
            dp[i][j] += cost[n][i] + cost[n][j];
        }
    }
    ll ans = 0x3f3f3f3f3f3f3f3fLL;
    for (int i = 1; i < m; ++i) {
        for (int j = i + 1; j <= m; ++j) {
            checkmin(ans, dp[i][j]);
        }
    }
    printf("%I64d\n", ans);
    return 0;
}
ll getll() {
    static ll rtn, f;
    static char ch;
    rtn = 0; f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
bool checkmin(ll &a, ll b) {
    if (b < a) {
        a = b;
        return true;
    } else return false;
}