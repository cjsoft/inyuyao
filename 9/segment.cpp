#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MXM 1000007
#define MXQ 1000007
#define MXN 1000007
#define INF 0x3f3f3f3f
#define lson(x) (x << 1)
#define rson(x) (x << 1 | 1)
#define mid(l, r) (l + ((r - l) >> 1))
using namespace std;
int n, m, q;
int stree[MXN << 2 | 1];
int etag[MXN << 2 | 1];
int raw[MXN];
int L[MXM], R[MXM];
inline void update(int root, int l, int r) {
    if (l < r)
    stree[root] = max(stree[lson(root)], stree[rson(root)]);
}
inline void pushdown(int root, int l, int r) {
    if (etag[root] != INF) {
        stree[lson(root)] = etag[root];
        stree[rson(root)] = etag[root];
        etag[lson(root)] = etag[rson(root)] = etag[root];
        etag[root] = INF;
    }
}
void build(int root, int l, int r) {
    if (l == r) {
        stree[root] = raw[l];
        etag[root] = INF;
        return;
    }
    etag[root] = INF;
    build(lson(root), l, mid(l, r));
    build(rson(root), mid(l, r) + 1, r);
    update(root, l, r);
}
void edit(int root, int l, int r, int ql, int qr, int data) {
    if (ql > r || qr < l) return;
    if (ql <= l && qr >= r) {
        etag[root] = data;
        stree[root] = data;
        return;
    }
    pushdown(root, l, r);
    edit(lson(root), l, mid(l, r), ql, qr, data);
    edit(rson(root), mid(l, r) + 1, r, ql, qr, data);
    pushdown(root, l, r);
}
int query(int root, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return -INF;
    if (ql <= l && qr >= r) return stree[root];
    pushdown(root, l, r);
    return max(
            query(lson(root), l, mid(l, r), ql, qr),
            query(rson(root), mid(l, r) + 1, r, ql, qr)
            );
}
inline int getint();
int main() {
    freopen("segment.in", "r", stdin);
    freopen("segment.out", "w", stdout);
    n = getint(); m = getint(); q = getint();
    for (int i = 1; i <= n; ++i) {
        raw[i] = getint();
    }
    for (int i = 1; i <= m; ++i) {
        L[i] = getint();
        R[i] = getint();
    }
    int op, a, b, k;
    for (int i = 1; i <= q; ++i) {
        op = getint();
        if (op == 1) {
            a = getint(); b = getint();
            raw[a] = b;
        } else {
            build(1, 1, n);
            a = getint(); b = getint(); k = getint();
            for (int j = a; j <= b; ++j) {
                int o = query(1, 1, n, L[j], R[j]);
                // printf("  %d\n", o);
                edit(1, 1, n, L[j], R[j], o);
            }
            printf("%d\n", query(1, 1, n, k, k));
        }
    }
    return 0;
}
int getint() {
    int rtn = 0, f = 1;
    char ch;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch -'0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
