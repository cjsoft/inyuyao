#include <iostream>
#include <cstdio>
#include <algorithm>
#define MXN 300007
using namespace std;
int n, l;
int fa[MXN];
char use[MXN];
int find(int a) {
    int t = a, tmp;
    for (; fa[t] != t; t = fa[t]);
    for (; fa[a] != a; tmp = fa[a], fa[a] = t, a = tmp);
    return t;
}
inline int getint();
int main() {
    freopen("LADICE.in", "r", stdin);
    freopen("LADICE.out", "w", stdout);
    n = getint();
    l = getint();
    for (int i = 1; i <= l; ++i) fa[i] = i;
    int a, b;
    for (int i = 0; i < n; ++i) {
        a = getint(); b = getint();
        if (!use[find(a)]) {
            use[fa[a]] = 1;
            if (!fa[a] != find(b)) fa[fa[a]] = fa[b];
            puts("LADICA");
        } else if (!use[find(b)]) {
            use[fa[b]] = 1;
            puts("LADICA");
        } else {
            puts("SMECE");
        }
    }
    return 0;
}
int __rtn__, __f__;
char __ch__;
int getint() {
    __rtn__ = 0; __f__ = 1;
    while ((__ch__ = getchar()) < '0' || __ch__ > '9') if (__ch__ == '-') __f__ = -__f__;
    __rtn__ = __ch__ - '0';
    while ((__ch__ = getchar()) >= '0' && __ch__ <= '9') __rtn__ = __rtn__ * 10 + __ch__ - '0';
    return __rtn__ * __f__;
}