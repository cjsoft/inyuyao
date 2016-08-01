#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <map>
#define mid(l, r) ((l) + (((r) - (l)) >> 1))
#define MXN 500007
#define INF 0x3f3f3f3f
using namespace std;
typedef pair<int, int> pii;
struct PersistentSeg {
    int L[(MXN << 4) + (MXN << 2) | 1],
        R[(MXN << 4) + (MXN << 2) | 1];
    pii stree[(MXN << 4) + (MXN << 2) | 1];
    // bool etag[(MXN << 4) + (MXN << 2) | 1];
    // pii tag[(MXN << 4) + (MXN << 2) | 1];
    int versions[MXN];
    int tot;
    PersistentSeg() {
        tot = 1;
    }
    // inline void pushdown(int root) {
    //     if (etag[root]) {
    //         etag[root] = false;
    //         tag[L[root]] 
    //     }
    // }
    int edit(int last, int l, int r, int ql, int qr, pii data) {
        if (l > qr || r < ql)
            return last;
        int y = tot++;
        if (l >= ql && r <= qr) {
            // etag[y] = true;
            stree[y] = data;
            L[y] = R[y] = y;
            return y;
        }
        L[y] = L[last]; R[y] = R[last];
        if (ql <= mid(l, r)) L[y] = edit(L[last], l, mid(l, r), ql, qr, data);
        if (qr > mid(l, r)) R[y] = edit(R[last], mid(l, r) + 1, r, ql, qr, data);
        return y;
    }
    pii query(int ver, int l, int r, int pos) {
        if (l == r) return stree[ver];
        if (pos <= mid(l, r)) return query(L[ver], l, mid(l, r), pos);
        else return query(R[ver], mid(l, r) + 1, r, pos);
    }
} pseg;
struct Seg {
    int stree[MXN << 2 | 1];
    int etag[MXN << 2 | 1];
    Seg() {
        for (int i = 0; i < (MXN << 2 | 1); ++i) etag[i] = -INF;
    }
    #define lson(x) ((x) << 1)
    #define rson(x) ((x) << 1 | 1)
    inline void update(int root, int l, int r) {
        if (l >= r) return;
        stree[root] = stree[lson(root)] + stree[rson(root)];
    }
    inline void edit(int root, int l, int r, int data) {
        stree[root] = data * (r - l + 1);
        etag[root] = data;
    }
    inline void pushdown(int root, int l, int r) {
        if (l >= r) return;
        if (etag[root] != -INF) {
            edit(lson(root), l, mid(l, r), etag[root]);
            edit(rson(root), mid(l, r) + 1, r, etag[root]);
            etag[root] = -INF;
        }
    }
    void edit(int root, int l, int r, int ql, int qr, int data) {
        // for (int i = ql; i <= qr; ++i) stree[i] = data;
        // return;
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) {
            edit(root, l, r, data);
            return;
        }
        pushdown(root, l, r);
        edit(lson(root), l, mid(l, r), ql, qr, data);
        edit(rson(root), mid(l, r) + 1, r, ql, qr, data);
        update(root, l, r);
    }
    int query(int root, int l, int r, int ql, int qr) {
        // int ans = 0;
        // for (int i = ql; i <= qr; ++i) ans += stree[i];
        // return ans;
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return stree[root];
        pushdown(root, l, r);
        return query(lson(root), l, mid(l, r), ql, qr) + query(rson(root), mid(l, r) + 1, r, ql, qr);
    }
} seg;
int l, r, x, n, m, type, lastans = 0, op, l2, r2;
inline int getint();
inline void decrypt(int &l, int &r) {
    l2 = (l + lastans * type) % n + 1;
    r2 = (r + lastans * type) % n + 1;
    l = min(l2, r2);
    r = max(l2, r2);
}
int main() {
    freopen("c3.in", "r", stdin);
    pseg.stree[0] = make_pair(0, 0);
    pseg.versions[0] = 0;
    n = getint(); m = getint(); type = getint();
    for (int i = 1; i <= m; ++i) {
        pseg.versions[i] = pseg.versions[i - 1];
        op = getint();
        if (op == 1) {
            l = getint(); r = getint();
            decrypt(l, r);
            // lastans = seg.query(1, 1, n, l, r);
            printf("%d\n", lastans = seg.query(1, 1, n, l, r));
        } else if (op == 2) {
            l = (getint() + lastans * type) % n + 1;
            pii x = pseg.query(pseg.versions[i - 1], 1, n, l);
            pii y = pseg.query(x.second, 1, n, l);
            seg.edit(1, 1, n, l, l, y.first);
            pseg.versions[i] = pseg.edit(pseg.versions[i - 1], 1, n, l, l, y);
        } else {
            l = getint(); r = getint(); x = getint();
            decrypt(l, r);
            seg.edit(1, 1, n, l, r, x);
            pseg.versions[i] = pseg.edit(pseg.versions[i - 1], 1, n, l, r, make_pair(x, i - 1));
        }
    }
    return 0;
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