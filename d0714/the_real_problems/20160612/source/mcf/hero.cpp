#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define iterate(_x, _i) for (edge *_i = head[_x]; _i; _i = _i->prev)
#define MXN 307
#define INF 0x3f3f3f3f
using namespace std;
inline int getint();
int n, m, K;
struct edge {
    edge *prev;
    int from, to, weight, flow;
} buf[MXN * MXN << 3], *cur, *head[MXN * MXN];
inline int loc(int x, int y) {
    --x, --y;
    return m * x + y;
}
void init() {
    memset(buf, 0, sizeof(buf));
    memset(head, 0, sizeof(head));
    cur = buf;
}
void addedge(int a, int b, int weight, int flow) {
    cur->from = a;
    cur->to = b;
    cur->prev = head[a];
    cur->weight = weight;
    cur->flow = flow;
    head[a] = cur++;
}
edge *pre[MXN * MXN << 1];
int spfa(int from, int t) {
    static queue<int> q;
    static char inq[MXN * MXN << 1];
    static int dist[MXN * MXN << 1];
    while (!q.empty()) q.pop();
    memset(inq, 0, sizeof(inq));
    memset(dist, 0x3f, sizeof(dist));
    dist[from] = 0;
    inq[from] = 1;
    q.push(from);
    while (!q.empty()) {
        static int u;
        u = q.front();
        // printf("   %d\n", u);
        iterate(u, i) {
            static int v, w;
            v = i->to; w = i->weight;
            if (i->flow > 0 && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pre[v] = i;
                if (!inq[v]) {
                    inq[v] = 1;
                    q.push(v);
                }
            }
        }
        inq[u] = 0;
        q.pop();
    }
    if (dist[t] < INF) return dist[t];
    else return INF;
}
void qqsolve(int &cost) {
    int from = n * m + 1, to = n * m + 2;
    while (spfa(from, to) != INF) {
        static int t, M;
        M = INF;
        t = n * m + 2;
        while (t != n * m + 1) {
            M = min(M, pre[t]->flow);
            t = pre[t]->from;
        }
        t = n * m + 2;
        while (t != n * m + 1) {
            cost += pre[t]->weight * M;
            pre[t]->flow -= M;
            (buf + ((pre[t] - buf) ^ 1))->flow += M;
            t = pre[t]->from;
        }
    }
}
int main() {
    freopen("hero.in", "r", stdin);
    freopen("hero.out", "w", stdout);
    init();
    n = getint(); m = getint(); K = getint();
    int tmp;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            tmp = getint();
            if (i < n) {
                addedge(loc(i, j), loc(i + 1, j), tmp, 1);
                addedge(loc(i + 1, j), loc(i, j), -tmp, 0);
            } else {
                addedge(loc(i, j), n * m, tmp, 1);
                addedge(n * m, loc(i, j), -tmp, 0);
            }
            if (j < m) {
                addedge(loc(i, j), loc(i, j + 1), K, INF);
                addedge(loc(i, j + 1), loc(i, j), -K, 0);
            }
            if (j > 1) {
                addedge(loc(i, j), loc(i, j - 1), K, INF);
                addedge(loc(i, j - 1), loc(i, j), -K, 0);
            }
        }
    }
    for (int i = 1; i <= m; ++i) {
        addedge(n * m + 1, loc(1, i), 0, 1);
        addedge(loc(1, i), n * m + 1, 0, 0);
    }
    addedge(n * m, n * m + 2, 0, 2);
    addedge(n * m + 2, n * m, 0, 0);
    int ans = 0;
    qqsolve(ans);
    printf("%d\n", ans);
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