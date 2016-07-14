#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define iterate(_x, _i) for (edge *_i = head[_x]; _i; _i = _i->prev)
#define MXN 57
#define INF 0x3f3f3f3f
using namespace std;
inline int getint();
int n, k;
struct edge {
    edge *prev;
    int from, to, weight, flow;
} buf[MXN * MXN << 3], *cur, *head[MXN * MXN << 1];
inline int loc(int x, int y, int z) {
    --x, --y;
    return n * y + x + n * n * z;
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
    if (dist[t] < 0) return dist[t];
    else return INF;
}
void kakasolve(int &cost) {
    int from = n * n * 2 + 1, to = n * n * 2 + 2;
    while (spfa(from, to) != INF) {
        static int t, M;
        M = INF;
        t = n * n * 2 + 2;
        while (t != n * n * 2 + 1) {
            M = min(M, pre[t]->flow);
            t = pre[t]->from;
        }
        t = n * n * 2 + 2;
        while (t != n * n * 2 + 1) {
            cost += pre[t]->weight * M;
            pre[t]->flow -= M;
            (buf + ((pre[t] - buf) ^ 1))->flow += M;
            t = pre[t]->from;
        }
    }
}
int main() {
    while (~scanf("%d %d", &n, &k)) {
        init();
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                static int tmp;
                tmp = getint();
                if (i < n) {
                    addedge(loc(i, j, 1), loc(i + 1, j, 0), 0, INF);
                    addedge(loc(i + 1, j, 0), loc(i, j, 1), 0, 0);
                }
                if (j < n) {
                    addedge(loc(i, j, 1), loc(i, j + 1, 0), 0, INF);
                    addedge(loc(i, j + 1, 0), loc(i, j, 1), 0, 0);
                }
                addedge(loc(i, j, 0), loc(i, j, 1), -tmp, 1);
                addedge(loc(i, j, 1), loc(i, j, 0), tmp, 0);
                addedge(loc(i, j, 0), loc(i, j, 1), 0, k - 1);
                addedge(loc(i, j, 0), loc(i, j, 1), 0, 0);
            }
        }
        addedge(n * n * 2 + 1, loc(1, 1, 0), 0, k);
        addedge(loc(1, 1, 0), n * n * 2 + 1, 0, 0);
        addedge(loc(n, n, 1), n * n * 2 + 2, 0, k);
        addedge(n * n * 2 + 2, loc(n, n, 1), 0, 0);
        int cost = 0;
        kakasolve(cost);
        printf("%d\n", -cost);
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