#include <iostream>
#include <cstdio>
#include <cstring>
#define MXN 10007
#define lson(x) (x << 1)
#define rson(x) (x << 1 | 1)
#define mid(l, r) (l + ((r - l) >> 1))
typedef long long ll;

ll stree[MXN << 2 | 1], tag[MXN << 2 | 1];
ll raw[MXN];
int flipcnt[MXN << 2 | 1];
bool fliptag[MXN << 2 | 1];
inline void update(int root) {
    stree[root] = stree[lson(root)] + stree[rson(root)];
    flipcnt[root] = flipcnt[lson(root)] + flipcnt[rson(root)];
}
void build(int root, int l, int r) {
    if (l == r) {
        if (raw[l] >= 0) {
            stree[root] = raw[l];
            tag[root] = 0;
            flipcnt[root] = 0;
        } else {
            stree[root] = -raw[l];
            tag[root] = 0;
            flipcnt[root] = 1;
        }
        return;
    }
    build(lson(root), l, mid(l, r));
    build(rson(root), mid(l, r) + 1, r);
    update(root);
}
inline void directAdd(int root, int l, int r, ll data) {
    stree[root] += (r - l + 1) * data;
    stree[root] -= (flipcnt[root] * data) << 1;
    //stree[lson(root)] += (mid(l, r) + 1 - l) * data;
    //stree[lson(root)] -= (flipcnt[lson(root)] * data) << 1;
    //stree[rson(root)] += (r - mid(l, r)) * data;
    //stree[rson(root)] -= (flipcnt[rson(root)] * data) << 1;
    tag[lson(root)] += data;
    tag[rson(root)] += data;
}
inline void pushdown(int root, int l, int r) {
    //if (flipcnt[root] == r - l + 1) {
    //    flipcnt[lson(root)] = mid(l, r) + 1 - l;
    //    flipcnt[rson(root)] = r - mid(l, r);
    //}
    //if (fliptag[root] && !flipcnt[root]) {
    //    flipcnt[lson(root)] = 0;
    //    flipcnt[rson(root)] = 0;
    //    fliptag[lson(root)] = true;
    //    fliptag[rson(root)] = true;
    //    fliptag[root] = false;
    //}
    if (tag[root]) {
        directAdd(lson(root), l, mid(l, r), tag[root]);
        directAdd(rson(root), mid(l, r) + 1, r, tag[root]);
        tag[root] = 0;
    }
    update(root);
}
ll query(int root, int l, int r, int ql, int qr) {
    if (ql > r || qr < l)
        return 0;
    if (ql <= l && qr >= r)
        return stree[root];
    pushdown(root, l, r);
    return query(lson(root), l, mid(l, r), ql, qr)
         + query(rson(root), mid(l, r) + 1, r, ql, qr);
}

void add(int root, int l, int r, int al, int ar, ll data) {
    if (al > r || ar < l)
        return;
    if (al <= l && ar >= r) {
        directAdd(root, l, r, data);
        return;
    }
    //pushdown(root, l, r);
    add(lson(root), l, mid(l, r), al, ar, data);
    add(rson(root), mid(l, r) + 1, r, al, ar, data);
    pushdown(root, l, r);
}
void flip(int root, int l, int r, int fl, int fr) {
    if (fl > r || fr < l)
        return;
    if (fl <= l && fr >= r) {
        flipcnt[root] = r - l + 1;
        fliptag[root] = true;
        return;
    }
    pushdown(root, l, r);
    flip(lson(root), l, mid(l, r), fl, fr);
    flip(rson(root), mid(l, r) + 1, r, fl, fr);
    pushdown(root, l, r);
}
int n, m;
inline ll getll();
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i)
        raw[i] = getll();
    build(1, 0, n - 1);
    int op, l, r;
    ll x;
    while (m--) {
        scanf("%d %d %d", &op, &l, &r);
        if (op == 0) {
            x = getll();
            add(1, 0, n - 1, l, r, x);
        } else if (op == 1) {
            flip(1, 0, n - 1, l, r);
        } else {
            printf("%lld\n", query(1, 0, n - 1, l, r));
        }
    }
    return 0;
}
ll getll() {
    ll f = 1, rtn = 0;
    char ch;
    while ((ch = getchar()) < '0' || ch > '9')
        if (ch == '-')
            f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') {
        rtn = rtn * 10 + ch - '0';
    }
    return f * rtn;
}
