#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdarg>
#define MXN 10007
using namespace std;
inline int getint();
int n, k, c;
int degree[MXN];
int main() {
    freopen("mzz.in", "r", stdin);
    freopen("mzz.out", "w", stdout);
    int sig;
    int a, b, c;
    while (~scanf("%d %d %d", &n, &k, &c)) {
        if (!n) return 0;
        memset(degree, 0, sizeof(int) * (n + 7));
        sig = 0;
        for (int i = 1; i < n; ++i) {
            a = getint(); b = getint(); c = getint();
            degree[a]++;
            degree[b]++;
            sig += c;
        }
        int si = 0;
        for (int i = 1; i < n; ++i) {
            if (degree[i] == 1) ++si;
        }
        if (k == n) {
            printf("%d\n", sig + si);
        } else {
            printf("%d\n", sig << 1);
        }
    }
    return 0;
}
int rtn, f; char ch;
int getint() {
    rtn = 0, f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
