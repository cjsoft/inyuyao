#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MOD 1000000007LL
#define MXN 100007
using namespace std;
typedef long long ll;
ll raw[MXN];
ll inv[MXN];
ll qpow(ll x, int y) {
    ll rtn = 1;
    for (; y; y >>= 1) {
        if (y & 1) rtn = rtn * x % MOD;
        x = x * x % MOD;
    }
    return rtn;
}
int n;
void init() {
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) {
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    }
    // inv_i=\left(M-\lfloor\frac{M}{i}\rfloor \times inv_{M\,mod\,i}\right)\,mod\,M
}
inline int getint();
int main() {
    n = getint();
    ll ans = 0;
    init();
    for (int i = 2; i <= n; ++i) {
        ans = (ans + 2 * inv[i]) % MOD;
    }
    ll aaa = 0;
    for (int i = 0; i < n; ++i) {
        aaa = (aaa + getint()) % MOD;
    }
    ans = ans * aaa % MOD;
    for (int i = 2; i<= n; ++i) {
        ans = ans * ((ll)i * (i - 1) / 2) % MOD;
    }
    printf("%lld\n", ans);
    return 0;
}

int getint() {
    int rtn = 0, f = 1;
    char ch;
    for (ch = getchar(); ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (rtn = ch - '0', ch = getchar(); ch >= '0' && ch <= '9'; ch = getchar()) rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
