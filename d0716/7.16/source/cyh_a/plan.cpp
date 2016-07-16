#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#define INF 0x3f3f3f3f
#define lowbit(x) ((x) & (-(x)))
#define iterate(_x, _i) for (edge *_i = head[_x]; _i; _i = _i->prev)
#define MXN 100007
using namespace std;
typedef pair<int, int> pii;
int n;
int qfa[MXN];
void init() { for (int i = 0; i < MXN; ++i) qfa[i] = i; }
template <typename T> void checkmin(T &a, T b) { if (b < a) a = b; }
template <typename T> void checkmax(T &a, T b) { if (b > a) a = b; }
int getfa(int x) {
    static int t, tmp;
    for (t = x; t != qfa[t]; t = qfa[t]);
    for (; x != qfa[x]; qfa[x] = t, x = tmp) tmp = qfa[x];
    return t;
}
void merge(int a, int b) { qfa[getfa(a)] = getfa(b); }
struct edge {
    int u, v, w;
    edge *prev;
    edge() { u = v = w = 0; prev = NULL; }
    edge(int a, int b, int c) { u = a; v = b; w = c; prev = NULL; }
    bool operator<(const edge &b) const { return w < b.w; }
} buf[MXN << 1 | 1], stor[MXN << 3 | 1], *cur, *head[MXN];
inline void addedge(const edge &A) {
    // printf("    %d %d\n", A.u, A.v);
    cur->v = A.v;
    cur->u = A.u;
    cur->w = A.w;
    cur->prev = head[A.u];
    head[A.u] = cur++;
    cur->v = A.u;
    cur->u = A.v;
    cur->w = A.w;
    cur->prev = head[A.v];
    head[A.v] = cur++;
}
struct pos {
    int x, y, id;
    pos() { x = y = id = 0; }
    pos(int a, int b, int c) { x = a; y = b; id = c; }
    bool operator<(const pos &b) const {
        if (x == b.x) return y < b.y;
        return x < b.x;
    }
} pnt[MXN];
pii ta[MXN << 1 | 1];
void taUpdate(int pos, pii ndata) {
    for (; pos < MXN; pos += lowbit(pos)) checkmin(ta[pos], ndata);
}
pii taQuery(int pos) {
    pii rtn = make_pair(INF, INF);
    for (; pos > 0; pos -= lowbit(pos)) checkmin(rtn, ta[pos]);
    return rtn;
}
int a[MXN], b[MXN], size, ecnt = 0;
void buildmst() {
    cur = buf;
    for (int dir = 1; dir <= 4; ++dir) {
        for (int i = 1; i <= n; ++i) {
            if (dir == 2 || dir == 4) swap(pnt[i].x, pnt[i].y);
            if (dir == 3) pnt[i].x = -pnt[i].x;
        }
        sort(pnt + 1, pnt + 1 + n);
        for (int i = 1; i <= n; ++i) a[i] = b[i] = pnt[i].x - pnt[i].y;
        sort(b + 1, b + 1 + n);
        size = unique(b + 1, b + 1 + n) - b - 1;
        for (int i = 1; i <= n; ++i) {
            a[i] = lower_bound(b + 1, b + 1 + size, a[i]) - b;
            ta[i] = make_pair(INF, 0);
        }

        for (int i = n; i > 0; --i) {
            int now = taQuery(a[i]).second;
            if (now) stor[ecnt++] = edge(pnt[i].id, pnt[now].id, pnt[now].x + pnt[now].y - pnt[i].x - pnt[i].y);
            taUpdate(a[i], make_pair(pnt[i].x + pnt[i].y, i));
        }
    }
    for (int i = 0; i < MXN; ++i) qfa[i] = i;
    sort(stor, stor + ecnt);
    int ccc = 0;
    for (int i = 0; i < ecnt, ccc < n - 1; ++i) {
        if (getfa(stor[i].u) != getfa(stor[i].v)) {
            merge(stor[i].u, stor[i].v);
            addedge(stor[i]);
            ++ccc;
        }
    }
}
int fa[MXN][21];
int nw[MXN][21];
int dep[MXN];
void dfs(int root) {
    dep[root] = dep[fa[root][0]] + 1;
    iterate(root, i) {
        if (i->v == fa[root][0]) continue;
        fa[i->v][0] = root;
        nw[i->v][0] = i->w;
        dfs(i->v);
    }
}
int query(int a, int b) {
    if (dep[a] > dep[b]) swap(a, b);
    int delta1 = dep[b] - dep[a], delta2 = delta1, s = 1, l = 0;
    int ans = 0;
    for (; s <= delta1; s <<= 1, ++l, delta2 >>= 1) {
        if (delta2 & 1) {
            checkmax(ans, nw[b][l]);
            b = fa[b][l];
        }
    }
    if (a == b) { return ans; }
    for (int i = 20; i >= 0; --i) {
        if (fa[a][i] != fa[b][i]) {
            checkmax(ans, nw[a][i]);
            checkmax(ans, nw[b][i]);
            a = fa[a][i];
            b = fa[b][i];
        }
    }
    checkmax(ans, nw[a][0]);
    checkmax(ans, nw[b][0]);
    return ans;
}
void buildtree() {
    fa[1][0] = 1;
    dfs(1);
    for (int i = 1; i < 21; ++i) {
        for (int j = 1; j <= n; ++j) {
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
            nw[j][i] = max(nw[fa[j][i - 1]][i - 1], nw[j][i - 1]);
        }
    }
}
int main() {
    freopen("plan.in", "r", stdin);
    freopen("plan.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d %d", &pnt[i].x, &pnt[i].y), pnt[i].id = i;
    buildmst();
    buildtree();
    int m, S, T;
    scanf("%d", &m);
    while (m--) {
        scanf("%d %d", &S, &T);
        printf("%d\n", query(S, T));
    }
    return 0;
}