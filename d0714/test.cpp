#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MOD 1632899
#define MXM 100007
#define MXN 100007
using namespace std;
typedef long long ll;
ll c[MXM], f[MXM];
void init() {
    c[0] = 4623;
    f[0] = 1;
    for (int i = 1; i < MXM; ++i) {
        c[i] = c[i - 1] * c[0] % MOD;
        if (c[i] < 0) c[i] += MOD;
    }
    for (int i = 1; i < MXM; ++i) {
        f[i] = f[i - 1] * (c[i] - 1) % MOD;
        if (f[i] < 0) f[i] += MOD;
    }
    for (int i = 2; i < MXM; ++i) {
        f[i] += f[i - 1];
        f[i] %= MOD;
        if (f[i] < 0) f[i] += MOD;
    }
}
inline int getint() {
    static int rtn, f;
    static char ch;
    rtn = 0; f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
int n, m;
int x[MXN], y[MXN];

int main() {
    init();
    n = getint();
    m = getint();
    for (int i = 1; i <= n; ++i) x[i] = getint(), y[i] = getint();
    for (int i = 1; i <= m; ++i) getint(), getint(), getint();
    int q = getint(), t;
    double a, b, c, d;
    for (int i = 0; i < q; ++i) {
        scanf("%lf %lf %lf %lf %d", &a, &b, &c, &d, &t);
        printf("%lld\n", f[t]);
    }
    return 0;
}
