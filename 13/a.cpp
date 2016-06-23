#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MOD 998244353LL
#define MXN 100007
#define add(a, b) (((ll)(a) + (b) + 998244353LL) % 998244353LL)
#define multi(a, b) ((ll)(a) * (b) % 998244353LL)
using namespace std;
typedef long long ll;
struct mat {
    ll d[13][13];
    int n;
    mat() {
        memset(d, 0, sizeof(d));
        n = 0;
    }
};
void initJiecheng(int, int);
ll det(const mat &b) {
    static mat a;
    a = b;
    int i, j, k;
    ll ans = 1;
    bool flag = 1;
    for (i = 1; i <= a.n; i++)
        for (j = 1; j <= a.n; j++)
            a.d[i][j] = (a.d[i][j] + MOD) % MOD;
    for (i = 1; i <= a.n; i++) {
        for (j = i + 1; j <= a.n; j++)
            while (a.d[j][i]) {
                ll t = a.d[i][i] / a.d[j][i];
                for (k = i; k <= a.n; k++)
                    a.d[i][k] = (a.d[i][k] + MOD - t * a.d[j][k] % MOD) % MOD;
                for (k = i; k <= a.n; k++)
                    swap(a.d[i][k], a.d[j][k]);
                flag ^= 1;
            }
        ans = ans * a.d[i][i] % MOD;
        printf("%lld\n", ans);
        if (!ans) return 0;
    }
    for (int i=1; i <= a.n; ++i) {
        for (int j = 1; j <= a.n; ++j) printf("%lld ", a.d[i][j]); puts("");
    }
    if (!flag) ans = (MOD - ans);
    return ans;
}
bool tag[67][67];
int y1[13], y2[13];
ll jiecheng[MXN];
ll dp[67][67];
inline ll getll();
int n, m, p, q;
mat tmp;
void initDp(int x);
ll Comb(int, int);
int main() {
    n = getll(); m = getll(); p = getll(); q = getll();
    for (int i = 0; i < p; ++i) {
        y1[i] = getll();
    }
    sort(y1, y1 + p);
    for (int i = 0; i < p; ++i) {
        y2[i] = getll();
    }
    sort(y2, y2 + p);
    int xx, yy;
    memset(tag, 0, sizeof(tag));
    for (int i = 0; i < q; ++i) {
        xx = getll(); yy = getll();
        tag[xx][yy] = 1;
    }
    tmp = mat();
    tmp.n = p;
    if (n > 55 || m > 55 || q < 2) goto TTT;
    for (int i = 0; i < p; ++i) {
        initDp(y1[i]);
        for (int j = 0; j < p; ++j) {
            tmp.d[i + 1][j + 1] = dp[n][y2[j]];
        }
    }
QQQ:
    for (int i=1; i <= p; ++i) {
        for (int j = 1; j <= p; ++j) printf("%lld ", tmp.d[i][j]); puts("");
    }
    printf("%lld\n", det(tmp));
    return 0;
TTT:
    initJiecheng(n, m);
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < p; ++j) {
            if (y1[i] <= y2[j]) {
                tmp.d[i + 1][j + 1] = Comb(n + y2[j] - y1[i], n);
            }
            if (q == 1 && y1[i] <= yy && yy <= y2[j]) {
                tmp.d[i + 1][j + 1] = (tmp.d[i + 1][j + 1] - Comb(xx + yy - y1[i], xx) * Comb(n - xx + y2[j] - yy, n - xx) % MOD) % MOD;
            }
        }
    }
    goto QQQ;
}
ll getll() {
    static ll rtn, f;
    static char ch;
    rtn = 0, f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
void initDp(int y) {
    memset(dp, 0, sizeof(dp));
    for (int i = y; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == y && j == 0) {
                dp[j][i] = 1;
                continue;
            }
            if (tag[j][i]) continue;
            if (i > y) dp[j][i] = (dp[j][i] + dp[j][i - 1]) % MOD;
            if (j > 0) dp[j][i] = (dp[j][i] + dp[j - 1][i]) % MOD;
        }
    }
} 
ll ext_gcd(ll a, ll b, ll &xx, ll &yy) {// NOLINT 
  if (b) {
    ll c = ext_gcd(b, a % b, yy, xx);
    yy -= xx * (a / b);
    return c;
  }
  xx = 1; yy = 0;
  return a;
}
ll inv(ll n) {
    ll x, y;
    ext_gcd(n, MOD, x, y);
    while (x < 0) x += MOD;
    return x % MOD;
}
ll qpow(ll x, int y) {
    ll rtn = 1;
    for (; y > 0; y >>= 1) {
        if (y & 1) rtn = rtn * x % MOD;
        x = x * x % MOD;
    }
    return rtn;
}
void initJiecheng(int n, int m) {
    int mmm = n + m;
    jiecheng[0] = 1;
    for (int i = 1; i <= mmm; ++i)
        jiecheng[i] = jiecheng[i - 1] * i % MOD;
}
ll Comb(int n, int m) {
    if (n == m || m == 0) return 1;
    ll dn = jiecheng[m] * jiecheng[n - m] % MOD;
    dn = qpow(dn, MOD - 2);
    return jiecheng[n] * dn % MOD;
}
