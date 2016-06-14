#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define MXN 5000007
using namespace std;
typedef long long ll;
int raw[MXN], temp[MXN];
int n;
int getint() {
    int rtn = 0, f = 1;
    char ch;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}

int main() {
    freopen("kth.in", "r", stdin);
    freopen("kth.out", "w", stdout);
    n = getint();
    for (int i = 1; i <= n; ++i) {
        raw[i] = getint();
    }
    int Q, a, b, c, d;
    Q = getint();
    for (int i = 0; i < Q; ++i) {
        a = getint(); b = getint(); c = getint(); d = getint();
        if (a == 1) {
            for (int i = b; i <= c; ++i) raw[i] += d;
        } else {
            int id = 0;
            for (int i = b; i <= c; ++i) temp[id++] = raw[i];
            sort(temp, temp + id);
            printf("%d\n", temp[d - 1]);
        }
    }
}
