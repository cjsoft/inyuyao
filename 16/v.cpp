#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MXN 1000007
using namespace std;
struct edge {int a, b;} egs[MXN];
int fa[MXN];
int n, m;
void init();
int getfa(int);
inline int getint();
int main() {

    return 0;
}
void init() {
    for (int i = 0; i <= n; ++i) fa[i] = i;
}
int getfa(int x) {
    static int t, tmp;
    for (t = x; fa[t] != t; t = fa[t]);
    for (tmp = fa[x]; x != t; x = tmp, tmp = fa[x]) fa[x] = t;
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