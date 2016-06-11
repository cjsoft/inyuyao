#include <iostream>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#define mid(l, r) (l + ((r - l) >> 1))
#define iterate(x, i) for (int i = head[x]; i; i = buf[i].prev)
#define MXN 262147
#define MXM 131077
using namespace std;
int n, m, q;
int nodeweight[MXN], dep[MXN], fa[MXN], sz[MXN], hson[MXN], lhd[MXN], locator[MXN], revlocator[MXN], sptot = 1;
int an1, an2, an3;
int ls[(MXM << 5) + 18 * MXN], rs[(MXM << 5) + 18 * MXN];
int stee[(MXM << 5) + 18 * MXN], tot = 1;
int versions[MXN];
inline int getint();
inline void update(int root) {
    stee[root] = stee[ls[root]] + stee[rs[root]];
}
void build(int &cur, int l, int r) {
    cur = tot++;
    if (l == r) return;
    build(ls[cur], l, mid(l, r));
    build(rs[cur], mid(l, r) + 1, r);
}
void add(int &root, int last, int data, int l, int r) {
    root = tot++;
    if (l == r) {
        stee[root] = stee[last] + 1;
        return;
    }
    ls[root] = ls[last];
    rs[root] = rs[last];
    int m = mid(l, r);
    if (data <= m)
        add(ls[root], ls[last], data, l, m);
    else
        add(rs[root], rs[last], data, m + 1, r);
    update(root);
}

int query(int verl, int verr, int l, int r, int ql, int qr) {
    if (ql > r || qr < l || qr < ql)
        return 0;
    if (ql <= l && qr >= r)
        return stee[verr] - stee[verl];
    int m = mid(l, r);
    return query(ls[verl], ls[verr], l, m, ql, qr) + 
           query(rs[verl], rs[verr], m + 1, r, ql, qr);
}
struct edge {
    int prev;
    int to;
} buf[MXN << 1 | 1];
int btot = 1, head[MXN];
void addedge(int a, int b) {
    buf[btot].prev = head[a];
    buf[btot].to = b;
    head[a] = btot++;
}
void dfs(int root) {
    if (!root) return;
    sz[root] = 1;
    hson[root] = 0;
    iterate(root, i) {
        if (buf[i].to == fa[root])
            continue;
        dep[buf[i].to] = dep[root] + 1;
        fa[buf[i].to] = root;
        dfs(buf[i].to);
        sz[root] += sz[buf[i].to];
        if (sz[buf[i].to] >= sz[hson[root]])
            hson[root] = buf[i].to;
    }
}
void dfs2(int root) {
    if (!root) return;
    locator[root] = sptot;
    revlocator[sptot++] = root;
    if (hson[root]) {
        lhd[hson[root]] = lhd[root];
        dfs2(hson[root]);
    } else return;
    iterate(root, i) {
        if (buf[i].to == fa[root] || buf[i].to == hson[root])
            continue;
        lhd[buf[i].to] = buf[i].to;
        dfs2(buf[i].to);
    }
}
void shupaoQ(int x, int y, int k, int &a, int &b, int &c) {
    a = b = c = 0;
    while (lhd[x] != lhd[y]) {
        if (dep[lhd[x]] < dep[lhd[y]])
            swap(x, y);
        // query(versions[locator[lhd[x]] - 1], versions[locator[x]], k, 1, m);
        a += query(versions[locator[lhd[x]] - 1], versions[locator[x]], 1, m, 1, k - 1);
        b += query(versions[locator[lhd[x]] - 1], versions[locator[x]], 1, m, k, k);
        c += query(versions[locator[lhd[x]] - 1], versions[locator[x]], 1, m, k + 1, m);
        x = fa[lhd[x]];
    }
    if (locator[x] > locator[y]) swap(x, y);
    // query(versions[locator[x] - 1], versions[locator[y]], k, 1, m);
    a += query(versions[locator[x] - 1], versions[locator[y]], 1, m, 1, k - 1);
    b += query(versions[locator[x] - 1], versions[locator[y]], 1, m, k, k);
    c += query(versions[locator[x] - 1], versions[locator[y]], 1, m, k + 1, m);
}


int main() {
    // int size = 64 << 20;
    // char *p = (char*)malloc(size) + size;  
    // __asm__("movl %0, %%esp\n" :: "r"(p));
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    n = getint(); m = getint(); q = getint();
    for (int i = 1; i <= n; ++i) nodeweight[i] = getint();
    int a, b, c;
    for (int i = 1; i < n; ++i) {
        a = getint(); b = getint();
        addedge(a, b); addedge(b, a);
    }
    int stp = 1;
    sz[0] = 0;
    dep[1] = 1;
    lhd[1] = 1;
    dfs(stp);
    dfs2(stp);
    build(versions[0], 1, m);
    for (int i = 1; i < sptot; ++i)
        add(versions[i], versions[i - 1], nodeweight[revlocator[i]], 1, m);
    int lastans = 0;
    int x, y, k;
    while (q--) {
        x = getint() ^ lastans; y = getint() ^ lastans; k = getint() ^ lastans;
        shupaoQ(x, y, k, a, b, c);
        printf("%d %d %d\n", a, b, c);
        lastans = a ^ b ^ c;
    }

    return 0;
}
inline int getint() {
    register int rtn = 0, f = 1;
    register char ch;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
