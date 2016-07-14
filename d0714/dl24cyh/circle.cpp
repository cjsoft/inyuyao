#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MOD 1000000007
#define MXN 100007
using namespace std;
typedef long long ll;
inline int getint() {
    static int rtn, f;
    static char ch;
    rtn = 0; f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
int n, m, l, r;
int x[MXN], y[MXN];
int main() {
    freopen("circle.in", "r", stdin);
    freopen("circle.out", "w", stdout);
    n = getint();
    for (int i = 1; i <= n; ++i) x[i] = getint(), y[i] = getint();
    m = getint();
    for (int i = 0; i < m; ++i) l = getint(), r = getint();
    printf("%lld\n", (1 + (ll)l * r));
    return 0;
}