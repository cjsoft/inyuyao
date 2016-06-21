#include <iostream>
#include <cstdio>
#include <cstring>
#define MXN 300007
using namespace std;

struct node {
    int data, dep;
    node *fa;
    node() {
        data = -1;
        dep = 0;
        fa = NULL;
    }
} buf[MXN], *cur = buf, *locator[MXN];
inline node *newnode(node *parent, int data) {
    if (parent) cur->dep = parent->dep + 1;
    else cur->dep = 1;
    cur->fa = parent;
    cur->data = data;
    return cur++;
}

inline int getint();
int fail[MXN];
void initNext(int raw[], int len) {
    memset(fail, 0, sizeof(fail));
    for (int i = 1; i < len; ++i) {
        int j = i; {
            while (j > 0) {
                j = fail[j];
                if (raw[i] == raw[j]) {
                    fail[i + 1] = j + 1;
                    break;
                }
            }
        }
    }
}
int tmpc[MXN];
int extend(int id, int pos, int data) {
    locator[id] = newnode(locator[pos], data);
    int l = locator[id]->dep;
    node *p = locator[id];
    tmpc[p->dep] = 0;
    while (p) {
        tmpc[p->dep - 1] = p->data;
        p = p->fa;
    }
    initNext(tmpc, l);
    return l - fail[l];
}
int n, m, type;
int main() {
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    n = getint(); m = getint(); type = getint();
    int lastans = 0;
    int x, c;
    for (int i = 1; i <= n; ++i) {
        x = getint() ^ lastans; c = getint() ^ lastans;
        int t = extend(i, x, c);
        if (type == 1) lastans = t;
        printf("%d\n", t);
    }
    return 0;
}
int getint() {
    static int rtn = 0, f = 1;
    static char ch;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch -'0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
