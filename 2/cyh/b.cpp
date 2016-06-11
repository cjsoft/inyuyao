#include <iostream>
#include <cstdio>
#include <cstring>
#define MXN 200007
#define MXM 7
#include <algorithm>
using namespace std;
inline int getint();
int c[MXN], a[MXN][MXM], b[MXN];
int n, m, k;
int main() {
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    n = getint(); m = getint(); k = getint();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            a[j][i] = getint();
        }
    }
    for (int i = 0; i < n; ++i) b[i] = getint();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            c[i] += a[j][b[i * j % n]];
    }
    sort(c, c + n, greater<int>());
    printf("%d\n", c[k - 1]);
    // for (int i = 0; i < n; ++i)
    //     printf("%d\n", c[i]);
    return 0;
}

int getint() {
    int rtn = 0, f = 1;
    char ch;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
