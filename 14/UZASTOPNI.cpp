#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <bitset>
#define iterate(x, i) for (int i = head[x]; i; i = buf[i].prev)
#define MXN 10007
#define MXV 107
typedef bitset<103> bst;
using namespace std;
bst Q[MXN][MXV];
int v[MXN];
struct edge {
    int to;
    int prev;
} buf[MXN << 1 | 1];
int head[MXN], tot = 1;
inline void addedge(int a, int b) {
    buf[tot].to = b;
    buf[tot].prev = head[a];
    head[a] = tot++;
}
void dfs(int root, int fa) {
    bool tag = false;
    iterate(root, i) {
        if (buf[i].to == fa) continue;
        tag = true;
        dfs(buf[i].to, root);
        for (int i = v[root]; i >= 0; --i) {
            for (int i = )
        }
    }
}
inline int getint();
int main() {
    freopen("UZASTOPNI.in", "r", stdin);
    freopen("UZASTOPNI.out", "w", stdout);
    
    n = getint();
    int a, b;
    for (int i = 1; i <= n; ++i) v[i] = getint();
    for (int i = 1; i < n; ++i) {
        a = getint(); b = getint();
        addedge(a, b); addedge(b, a)
    }
    return 0;
}
int getint() {
    static int rtn, f;
    static char ch;
    rtn = 0; f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <=' 9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}