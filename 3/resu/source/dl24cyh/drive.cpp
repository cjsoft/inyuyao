#include <stdio.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
#include <queue>
#define iterate(x, i, j) for (int i = head[x], j = buf[i].to; i; i = buf[i].prev, j = buf[i].to)
#define MXN 100033
#define INF 0x3f000000
using namespace std;
struct edge { int prev, to; } buf[MXN << 2 | 1];
int n;
int head[MXN], ctot = 1;
int dist[MXN], ans[MXN];
struct testCase {
    int a, b, id;
    testCase(int q, int w, int e) {
        if (w < q) swap(q, w);
        id = e;
        a = q;
        b = w;
    }
    testCase() { a = b = id = 0; }
    bool operator<(const testCase &bb) const {
        return a < bb.a;
    }
};
multiset<testCase> sss;
inline void addedge(int a, int b);
void bfs(int stp) {
    for (int i = 0; i <= n; ++i) dist[i] = INF;
    queue<int> Q;
    int u, v;
    Q.push(stp);
    dist[stp] = 0;
    while (!Q.empty()) {
        u = Q.front(); Q.pop();
        iterate(u, i, v) {
            if (dist[v] == INF) {
                dist[v] = dist[u] + 1;
                Q.push(v);
            }
        }
    }
}
int main() {
    freopen("drive.in", "r", stdin);
    freopen("drive.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        addedge(i, i + 1);
        addedge(i + 1, i);
    }
    addedge(n, 1);
    addedge(1, n);
    int a, b;
    for (int i = 0; i < n - 3; ++i) {
        scanf("%d %d", &a, &b);
        addedge(a, b);
        addedge(b, a);
    }
    int q;
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        scanf("%d %d", &a, &b);
        sss.insert(testCase(a, b, i));
    }
    int last = 0;
    for (multiset<testCase>::iterator i = sss.begin(); i != sss.end(); i++) {
        if (last != i->a) bfs(i->a), last = i->a;
        ans[i->id] = dist[i->b];
    }
    for (int i = 1; i <= q; ++i)
        printf("%d\n", ans[i]);
}

void addedge(int a, int b) {
    buf[ctot].to = b;
    buf[ctot].prev = head[a];
    head[a] = ctot++;
}
