#include <cstdio>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <iostream>
#include <vector>
#define lson(x) ((x) << 1)
#define rson(x) ((x) << 1 | 1)
#define mid(l, r) ((l) + (((r) - (l)) >> 1))
#define INF 0x3f3f3f3f3f3fLL
#define MXN 20007
#define MXM 107
using namespace std;
typedef long long ll;
inline int getint();
inline ll getll();
inline int queryK(ll[], int, int, ll);
class segtree {
private:
    ll atag[MXN << 2 | 1];
    inline void update(int, int, int);
    inline void pushdown(int, int, int);
public:
    segtree() {for (int i = 0; i < (MXN << 2 | 1); ++i) {atag[i] = 0; stree[i] = 0;}}
    ll stree[MXN << 2 | 1];
    ll raw[MXN];
    void build(int, int, int);
    ll query(int, int, int, int, int);
    void add(int, int, int, int, int, ll);
} st;
int n, m;

ll c[MXN], r[MXN], p[MXN], d[MXN];
int stt[MXN], ed[MXN];
ll dp[MXN];
vector <int> lst[MXN];
int main() {
    freopen("jhaha.in", "r", stdin);
    freopen("jhaha.out", "w", stdout);
    n = getint(); m = getint();
    for (int i = 2; i <= n; ++i) d[i] = getll();
    for (int i = 1; i <= n; ++i) c[i] = getll();
    for (int i = 1; i <= n; ++i) r[i] = getll();
    for (int i = 1; i <= n; ++i) p[i] = getll();
    ++n; ++m;
    d[n] = INF; p[n] = INF;
    for (int i = 1; i <= n; ++i) {
        int ll = d[i] - r[i], rr = d[i] + r[i];
        ll = lower_bound(d + 1, d + n + 1, ll) - d;
        rr = lower_bound(d + 1, d + n + 1, rr) - d;
        if (d[i] + r[i] < d[rr]) rr--;
        stt[i] = ll; ed[i] = rr;
        lst[ed[i]].push_back(i);
    }
    ll ans, tmp = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = tmp + c[i];
        for (int j = 0; j < lst[i].size(); ++j)
            tmp += p[lst[i][j]];
    }
    ans = dp[n];
    for (int j = 2; j <= m; ++j) {
        st.build(1, 1, n);
        for (int i = 1; i <= n; ++i) {
            ll tmp = st.query(1, 1, n, 1, i - 1);
            dp[i] = tmp + c[i];
            for (int k = 0; k < lst[i].size(); ++k) {
                int x = lst[i][k];
                st.add(1, 1, n, 1, stt[x] - 1, p[x]);
            }
        }
        ans = min(ans, dp[n]);
    }
    printf("%lld\n", ans);

}

void segtree::build(int root, int l, int r) {
    atag[root] = 0;
    if (l == r) {
        stree[root] = dp[l];
        atag[root] = 0;
        return;
    }
    build(lson(root), l, mid(l, r));
    build(rson(root), mid(l, r) + 1, r);
    update(root, l, r);
}
ll segtree::query(int root, int l, int r, int ql, int qr) {
    if (ql > qr || ql > r || qr < l) return 0;
    pushdown(root, l, r);
    if (ql <= l && qr >= r) return stree[root];
    int m = mid(l, r);
    ll ans = INF;
    if (ql <= m) ans = min(ans, query(lson(root), l, m, ql, qr));
    if (m < qr) ans = min(ans, query(rson(root), m + 1, r, ql, qr));
    return ans;
}
void segtree::add(int root, int l, int r, int ql, int qr, ll data) {
    if (ql > r || qr < l || ql > qr) return;
    if (ql <= l && qr >= r) {
        stree[root] += data;
        atag[root] += data;
        return;
    }
    pushdown(root, l, r);
    if (ql <= mid(l, r)) add(lson(root), l, mid(l, r), ql, qr, data);
    if (mid(l, r) < qr) add(rson(root), mid(l, r) + 1, r, ql, qr, data);
    update(root, l, r);
    return;
    add(lson(root), l, mid(l, r), ql, qr, data);
    add(rson(root), mid(l, r) + 1, r, ql, qr, data);
    update(root, l, r);
}
void segtree::update(int root, int l, int r) {
    if (l >= r) return;
    stree[root] = min(stree[lson(root)], stree[rson(root)]);
}
void segtree::pushdown(int root, int l, int r) {
    if (l >= r) return;
    if (atag[root]) {
        stree[lson(root)] += atag[root];
        stree[rson(root)] += atag[root];
        atag[lson(root)] += atag[root];
        atag[rson(root)] += atag[root];
        atag[root] = 0;
    }
    update(root, l, r);
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
ll getll() {
    static ll rtn, f;
    static char ch;
    rtn = 0; f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
int queryK(ll raw[], int l, int r, ll data) {
    return lower_bound(raw + l, raw + r + 1, data) - raw - l;
}