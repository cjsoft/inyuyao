#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define INF 0x3f3f3f3f
#define MXN 100007
#define mid(l, r) (l + ((r - l) >> 1))
#define iterate(_x, _i) for (edge *_i = head[_x]; _i; _i = _i->prev)
#define lson(x) ((x) << 1)
#define rson(x) ((x) << 1 | 1)
template<typename T> void checkmax(T &a, T b) { if (a < b) a = b; }
using namespace std;
struct pos {
    int x, y, id;
    bool operator<(const pos &b) const {
        return y < b.y;
    }
} cities[MXN];
int n, m;
int S, T;
int dist[1007];
inline int iabs(int a) { if (a < 0) return -a; else return a; }
struct edge {
    edge *prev;
    int to, weight;
} buf[1007 << 1 | 1], *cur, *head[1007];
void initegs() {
    memset(buf, 0, sizeof(buf));
    memset(head, 0, sizeof(head));
    cur = buf;
}
inline void addedge(int a, int b, int weight) {
    cur->prev = head[a];
    cur->to = b;
    cur->weight = weight;
    head[a] = cur++;
}
// void spfa() {
//     char inq[1007];
//     memset(inq, 0, sizeof(inq));
//     memset(dist, 0x3f, sizeof(dist));
//     queue<int> q;
//     inq[S] = 1;
//     dist[S] = 0;
//     q.push(S);
//     while (!q.empty()) {
//         static int u, v, w;
//         u = q.front();
//         iterate(u, i) {
//             v = i->to; w = i->weight;
//             if (max(w, dist[u]) < dist[v]) {
//                 dist[v] = max(w, dist[u]);
//                 if (!inq[v]) {
//                     inq[v] = 1;
//                     q.push(v);
//                 }
//             }
//         }
//         q.pop();
//         inq[u] = 0;
//     }
// }

int stree[MXN << 2 | 1];
inline void update(int root, int l, int r) {
    if (l >= r) return;
    stree[root] = max(stree[lson(root)], stree[rson(root)]);
}
void build(int root, int l, int r) {
    if (l == r) {
        stree[root] = cities[l + 1].y - cities[l].y;
        return;
    }
    build(lson(root), l, mid(l, r));
    build(rson(root), mid(l, r) + 1, r);
    update(root, l, r);
}
int query(int root, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) return 0;
    if (l >= ql && r <= qr) return stree[root];
    return max(query(lson(root), l, mid(l, r), ql, qr), query(rson(root), mid(l, r) + 1, r, ql, qr));
}
int loc[MXN];
struct eg { int u, v, w; bool operator<(const eg &b) const { return w < b.w; } } avaeg[1007];
int qfa[1007];
void inituni() { for (int i = 0; i < 1007; ++i) { qfa[i] = i; } }
int getfa(int x) {
    int t = x, tmp;
    for (; qfa[t] != t; t = qfa[t]);
    for (; qfa[x] != x; qfa[x] = t, x = tmp) tmp = qfa[x];
    return t;
}
void uni(int a, int b) { qfa[getfa(a)] = getfa(b); }
int fa[1007][12];
int dep[1007];
int nw[1007][12];
void dfs(int root) {
    dep[root] = dep[fa[root][0]] + 1;
    iterate(root, i) {
        if (i->to == fa[root][0]) continue;
        fa[i->to][0] = root;
        nw[i->to][0] = i->weight;
        // printf("  %d\n", i->weight);
        dfs(i->to);
    }
}
int query(int a, int b) {
    if (dep[a] > dep[b]) swap(a, b);
    int delta = dep[b] - dep[a], d = delta;
    int s = 1, l = 0;
    int ans = 0;
    for (; s <= delta; s <<= 1, ++l, d >>= 1) {
        if (d & 1) {
            checkmax(ans, nw[b][l]);
            b = fa[b][l];
        }
    }
    if (a == b) return ans;
    for (int i = 11; i >= 0; --i) {
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
int main() {
    freopen("plan.in", "r", stdin);
    freopen("plan.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &cities[i].x, &cities[i].y);
        cities[i].id = i;
    }
    if (n <= 1000) {
        eg *egs = new eg[n * n];
        int tot = 0, cnt = 0;
        for (int i = 1; i < n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                egs[tot].u = i;
                egs[tot].v = j;
                egs[tot++].w = iabs(cities[i].x - cities[j].x) + iabs(cities[i].y - cities[j].y);
            }
        }
        sort(egs, egs + tot);
        inituni();
        for (int i = 0; i < tot && cnt < n - 1; ++i) {
            if (getfa(egs[i].u) != getfa(egs[i].v)) {
                uni(egs[i].u, egs[i].v);
                avaeg[cnt++] = egs[i];
            }
        }
        initegs();
        for (int i = 0; i < cnt; ++i) {
            addedge(avaeg[i].u, avaeg[i].v, avaeg[i].w);
            addedge(avaeg[i].v, avaeg[i].u, avaeg[i].w);
        }
        fa[1][0] = 1;
        dfs(1);
        for (int i = 1; i < 12; ++i) {
            for (int j = 1; j <= n; ++j) {
                fa[j][i] = fa[fa[j][i - 1]][i - 1];
                nw[j][i] = max(nw[fa[j][i - 1]][i - 1], nw[j][i - 1]);
            }
        }
        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            scanf("%d %d", &S, &T);
            printf("%d\n", query(S, T));
        }
    } else {
        sort(cities + 1, cities + 1 + n);
        for (int i = 1; i <= n; ++i) loc[cities[i].id] = i;
        build(1, 1, n - 1);
        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            scanf("%d %d", &S, &T);
            if (loc[S] > loc[T]) swap(S, T);
            printf("%d\n", query(1, 1, n - 1, loc[S], loc[T] - 1));
        }
    }
    
    return 0;
}
