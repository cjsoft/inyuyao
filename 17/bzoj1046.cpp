#include <iostream>
#include <cstdio>
#include <algorithm>
#include <memory.h>
#define MXN 10007
#define MXM 1007
using namespace std;

int stk[MXN], tot = 0;
int head[MXN];
int raw[MXN];
bool asktag[MXN];
int glresu[MXM][MXN], cur = 0;
int askcase[MXM];
int loca[MXN];
int n, m;
inline int getint() {
    static int rtn, f;
    static char ch;
    rtn = 0; f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}

int main() {
    n = getint();
    int tmp;
    for (int i = 0; i < n; ++i) {
        raw[i] = getint();
    }
    m = getint();
    for (int i = 0; i < m; ++i)
        asktag[askcase[i] = getint()] = true;
    for (int i = 0; i < n; ++i) {
        if (tot < 1 || raw[i] > stk[tot - 1]) {
            stk[tot++] = raw[i];
            if (asktag[tot]) {
                loca[tot] = cur;
                memcpy(&glresu[cur++][0], stk, sizeof(int) * tot);
            }
        } else {
            int *p = upper_bound(stk, stk + tot, raw[i]);
            *p = raw[i];
        }
    }
    int id = 0;
    int last = 0;
    for (int i = 0; i < m; ++i) {
        if (tot < askcase[i]) puts("Impossible");
        else {
            for (int j = 0; j < askcase[i]; ++j) {
                printf("%d", glresu[loca[askcase[i]]][j]);
                if (j != askcase[i] - 1) putchar(' ');
            }
            putchar('\n');
            // ++id;
        }
    }
    return 0;
}