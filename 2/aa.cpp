#include <iostream>
#include <cstdio>
#include <cstring>
#define mid(l, r) (l + ((r - l) >> 1))
#define iterate(x, i) for (int i = head[x]; i; i = buf[i].prev)
#define MXN 131089
#define MXM 65587
using namespace std;
int n, m, q;
int nodeweight[MXN], dep[MXN], revdep[MXN], indegree[MXN], fa[MXN];
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
    // if (data <= m)
    //     return query(ls[verl], ls[verr], data, l, m);
    // else
    //     return query(rs[verl], rs[verr], data, m + 1, r);
}
struct edge {
    int prev;
    int to;
} buf[MXN << 1 | 1];
int btot = 1, head[MXN];
void addedge(int a, int b) {
    ++indegree[b];
    buf[btot].prev = head[a];
    buf[btot].to = b;
    head[a] = btot++;
}
void dfs(int root) {
    revdep[dep[root]] = root;
    iterate(root, i) {
        if (buf[i].to == fa[root])
            continue;
        fa[buf[i].to] = root;
        dep[buf[i].to] = dep[root] + 1;
        dfs(buf[i].to);
    }
}
void transfer(int root) {
    int t = head[root];
    while (true) {
        if (!t) break;
        while (buf[t].to == fa[root]) t = buf[t].prev;
        if (!t) break;
        dep[buf[t].to] = dep[root] + 1;
        revdep[dep[root] + 1] = buf[t].to;
        fa[buf[t].to] = root;
        root = buf[t].to;
        t = head[root];
    }
}
void bruteSolve(int x, int y, int k, int &a, int &b, int &c) {
    a = b = c = 0;
    if (dep[x] > dep[y]) swap(x, y);
    while (dep[y] > dep[x]) {
        if (nodeweight[x] > k) ++c;
        else if (nodeweight[x] == k) ++b;
        else ++a;
        y = fa[y];
    }
    while (x != y) {
        if (nodeweight[x] > k) ++c;
        else if (nodeweight[x] == k) ++b;
        else ++a;
        x = fa[x];
        if (nodeweight[y] > k) ++c;
        else if (nodeweight[y] == k) ++b;
        else ++a;
        y = fa[y];
    }
    if (nodeweight[y] > k) ++c;
    else if (nodeweight[y] == k) ++b;
    else ++a;
}
int main() {
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    n = getint(); m = getint(); q = getint();
    for (int i = 1; i <= n; ++i) nodeweight[i] = getint();
    int a, b, c;
    for (int i = 1; i < n; ++i) {
        a = getint(); b = getint();
        addedge(a, b); addedge(b, a);
    }
    if (n > 30000) {
        int stp = 1;
        for (int i = 1; i <= n; ++i)
            if (indegree[i] == 1)
                stp = i;
        dep[stp] = 1;
        revdep[1] = stp;
        transfer(stp);
        // dfs(stp);
        build(versions[0], 1, m);
        for (int i = 1; i <= n; ++i)
            add(versions[i], versions[i - 1], nodeweight[revdep[i]], 1, m);
        int lastans = 0;
        int x, y, k;
        while (q--) {
            x = getint() ^ lastans; y = getint() ^ lastans; k = getint() ^ lastans;
            if (dep[x] > dep[y]) swap(x, y);
            a = query(versions[dep[x] - 1], versions[dep[y]], 1, m, 1, k - 1);
            b = query(versions[dep[x] - 1], versions[dep[y]], 1, m, k, k);
            c = query(versions[dep[x] - 1], versions[dep[y]], 1, m, k + 1, m);
            printf("%d %d %d\n", a, b, c);
            lastans = a ^ b ^ c;
        }
    } else {
        dfs(1);
        int lastans = 0;
        int x, y, k;
        while (q--) {
            x = getint() ^ lastans; y = getint() ^ lastans; k = getint() ^ lastans;
            bruteSolve(x, y, k, a, b, c);
            printf("%d %d %d\n", a, b, c);
            lastans = a ^ b ^ c;
        }
    }
    return 0;
}
int getint() {
    int rtn = 0, f = 1;
    char ch;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
