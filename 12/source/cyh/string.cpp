#include <iostream>
#include <cstdio>
#include <cstring>
#define mid(l, r) (l + ((r - l) >> 1))
#define MXN 300007
#define MXM 300007
int L[MXM * 20 * 3], R[MXM * 20 * 3];
int v[MXM * 20 * 3];
int T[MXM];
int dep[MXM];
int tot = 1;
int n, m, type;
using namespace std;
int edit(int lastVersion, int l, int r, int pos, int data) {
    int y = tot++;
    if (l == r) {
        v[y] = data;
        return y;
    }
    int m = mid(l, r);
    if (pos <= m) {
        R[y] = R[lastVersion];
        L[y] = edit(L[lastVersion], l, m, pos, data);
    } else {
        L[y] = L[lastVersion];
        R[y] = edit(R[lastVersion], m + 1, r, pos, data);
    }
    return y;
}
int query(int version, int l, int r, int pos) {
    if (l == r) return v[version];
    int m = mid(l, r);
    if (pos <= m)
        return query(L[version], l, m, pos);
    else
        return query(R[version], m + 1, r, pos);
}
int main() {
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    scanf("%d %d %d", &n, &m, &type);
    int x, y, ans = 0;
    int versionCursor, transTarget;
    int tmpRoot;
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &x, &y);
        if (type) x ^= ans, y ^= ans;
        dep[i] = dep[x] + 1;
        versionCursor = query(T[x], 0, n, x);
        transTarget = query(versionCursor, 1, m, y);
        printf("%d\n", ans = dep[i] - dep[transTarget]);
        tmpRoot = edit(T[x], 0, n, x, edit(versionCursor, 1, m, y, i)); // 令trans(x, y) = i并产生一个新的版本
        T[i] = edit(tmpRoot, 0, n, i, query(tmpRoot, 0, n, transTarget)); // 从transTarget得到trans(i)
    }
    return 0;
}