#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define INF 0x3f3f3f3f
#define iterate(x, i) for (edge *i = head[x]; i; i = i->prev)
#define loc(x, y, z) ((y) * (n + 2) + (x) + 4 + (z) * (n + 2) * (n + 2))
using namespace std;
typedef long long ll;
int n, k;
int N;
struct edge {
    edge *prev;
    int from, to;
    int weight;
    int flow;
    int capacity;
} buf[103 * 103 * 40], *head[2 * 103 * 103], *cur = buf;
edge *egg[2 * 103 * 103];
int loca(int x, int y, int z) {
    return loc(x, y, z);
}
inline void init(int n) {
    N = n;
    memset(head, 0, sizeof(head));
    cur = buf;
}
inline void addedge(int a, int b, int weight, int capa) {
    cur->to = b;
    cur->from = a;
    cur->capacity = capa;
    cur->weight = weight;
    cur->flow = 0;
    cur->prev = head[a];
    head[a] = cur++;
    cur->to = a;
    cur->from = b;
    cur->capacity = 0;
    cur->weight = -weight;
    cur->flow = 0;
    cur->prev = head[b];
    head[b] = cur++;
}
int spfa(int from, int to) {
    static char inq[52 * 52];
    static int dist[52 * 52];
    static int tmp;
    memset(inq, 0, sizeof(inq));
    memset(dist, 0x3f, sizeof(dist));
    queue<int> Q;
    Q.push(from);
    inq[from] = 1;
    // idkast[from] = 0;
    while (!Q.empty()) {
        tmp = Q.front();
        iterate(tmp, i) {
            if (i->flow < i->capacity && i->weight + dist[tmp] < dist[i->to]) {
                egg[i->to] = i;
                dist[i->to] = i->weight + dist[tmp];
                if (!inq[i->to]) {
                    inq[i->to] = 1;
                    Q.push(i->to);
                }
            }
        }
        inq[tmp] = 0;
        Q.pop();
    }
    if (dist[to] == INF)
        return -1;
    else
        return 1;
}
int kakasolve(int s, int t, int &cost) {
    int mn = INF;
    int ans = 0;
    int tmp;
    while (spfa(s, t) != -1) {
        tmp = t;
        egg[s] = 0;

        while (egg[tmp]) {
            mn = min(mn, egg[tmp]->capacity - egg[tmp]->flow);
            tmp = egg[tmp]->from;
        }
        tmp = t;
        while (egg[tmp]) {
            egg[tmp]->flow += mn;
            (buf + ((egg[tmp] - buf) ^ 1))->flow -= mn;
            cost += mn * egg[tmp]->weight;
            tmp = egg[tmp]->from;
        }
        ans += mn;
    }
    return ans;
}
int a[52][52];
inline int getint();
int main() {
    while (~scanf("%d %d", &n, &k)) {
        if (!n) return 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                a[i][j] = getint();
        init(2 * n * n + 2);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                addedge(loc(i, j, 0), loc(i, j, 1), -a[i][j], 1);
                addedge(loc(i, j, 0), loc(i, j, 1), 0, k - 1);
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i < n)
                    addedge(loc(i, j, 1), loc(i + 1, j, 0), 0, INF);
                if (j < n)
                    addedge(loc(i, j, 1), loc(i, j + 1, 0), 0, INF);
            }
        }
        addedge(0, loc(1, 1, 0), 0, k);
        addedge(loc(n, n, 1), 1, 0, k);
        int cost = 0;
        kakasolve(0, 1, cost);
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