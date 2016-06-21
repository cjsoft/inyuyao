#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lson(x) (x << 1)
#define rson(x) (x << 1 | 1)
#define mid(l, r) (l + ((r - l) >> 1))
#define MXN 10000007
#define MXQ 100007
using namespace std;
int n, q;
int lne[MXN << 2 | 1], stree[MXN << 2 | 1];
struct node {
    int fa[18], data;
} buf[8000001]; int ltot = 2;
int newnode(int data, int fa) {
    buf[ltot].data = data;
    buf[ltot].fa[0] = fa;
    for (int i = 1; buf[ltot].fa[i - 1] != 0 && i < 18; ++i) {
        buf[ltot].fa[i] = buf[buf[ltot].fa[i - 1]].fa[i - 1];
    }
    return ltot++;
}
inline void pushdown(int root) {
    if (lne[root] != 0) {
        lne[lson(root)] = lne[root];
        lne[rson(root)] = lne[root];
        lne[root] = 0;
    }
}
int opdata;
char opcode;
void dosomething(int root, int l, int r) {
    if (lne[root] != 0) {
        if (opcode == 1) {
            int tmp = newnode(opdata, lne[root]);
            lne[root] = tmp;
        } else {
            if (buf[lne[root]].fa[0] != 0)
                lne[root] = buf[lne[root]].fa[0];
        }
    } else {
        dosomething(lson(root), l, mid(l, r));
        dosomething(rson(root), mid(l, r) + 1, r);
    }
}

void locateSegment(int root, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return;
    if (ql <= l && qr >= r) {
        dosomething(root, l, r);
        return;
    }
    pushdown(root);
    if (qr <= mid(l, r)) {
        locateSegment(lson(root), l, mid(l, r), ql, qr);
    } else if (ql > mid(l, r)) {
        locateSegment(rson(root), mid(l, r) + 1, r, ql, qr);
    } else {
        locateSegment(lson(root), l, mid(l, r), ql, qr);
        locateSegment(rson(root), mid(l, r) + 1, r, ql, qr);
    }
}
int retn;
int queryk(int root, int l, int r, int pos, int k) {
    // if (k == 2)
        // puts("here");
    if (lne[root] != 0) {
        int tmp = lne[root];
        int len = 0, b = 1;
        --k;
        for (; b <= k; b <<= 1, ++len);
        for (len--, b >>= 1; b > 0; --len, b >>= 1) {
            if (k & b) {
                tmp = buf[tmp].fa[len];
                if (tmp == 1 || tmp == 0) {
                    retn = -1;
                    return -1;
                }
            }
        }
        if (tmp == 1 || tmp == 0) {
            retn = -1;
            return -1;
        }
        retn = 1;
        return buf[tmp].data;
    } else {
        if (pos <= mid(l, r)) {
            return queryk(lson(root), l, mid(l, r), pos, k);
        } else {
            return queryk(rson(root), mid(l, r) + 1, r, pos, k);
        }
    }
}
inline int getint();
int main() {
    // while (1);
    freopen("stack.in", "r", stdin);
    freopen("stack.out", "w", stdout);
    n = getint(); q = getint();
    lne[1] = 1;
    int t;
    int l, r, x;
    for (int i = 0; i < q; ++i) {
        t = getint();
        if (t == 0) {
            l = getint(); r = getint(); x = getint();
            opdata = x; opcode = 1;
            locateSegment(1, 1, n, l, r);
        } else if (t == 1) {
            l = getint(); r = getint();
            opcode = -1;
            locateSegment(1, 1, n, l, r);
        } else {
            l = getint(); r = getint();
            x = queryk(1, 1, n, l, r);
            if (retn == -1)
                puts("Error");
            else
                printf("%d\n", x);
        }
    }
}
int getint() {
    static int rtn, f;
    static char ch;
    rtn = 0; f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
