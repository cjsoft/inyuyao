#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define MXN 2507
#define MXM 5007
#define INF 0x3f3f3f30
#define MOD 1000000007LL
#define iterate(x, i) for (int i = head[x]; i; i = buf[i].prev)
using namespace std;
typedef long long ll;
char inq[MXN][MXM];
int stk[MXM], top = 0;
ll dist[MXN][MXM];
int n, m, T;
struct edge {
    int prev, to;
    ll weight;
} buf[MXM << 1 | 1];
int head[MXN], ctot = 1;
inline ll cross(int x1, int y1, int x2, int y2, int x3, int y3) {
    return (ll)(x2 - x1) * (y3 - y1) - (ll)(x3 - x1) * (y2 - y1);
    return (ll)(y1 - y2) * (x2 - x3) - (ll)(y2 - y3) * (x1 - x2);
}
inline void addedge(int a, int b, ll weight) {
    buf[ctot].to = b;
    buf[ctot].prev = head[a];
    buf[ctot].weight = weight;
    head[a] = ctot++;
}
void spfa() {
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            dist[i][j] = INF;
    dist[1][0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (dist[j][i] < INF) {
                iterate(j, k) {
                    dist[buf[k].to][i + 1] = std::min(dist[buf[k].to][i + 1], dist[j][i] + buf[k].weight);
                }
            }
        }
    }
    return;
    queue<int> qu, qcnt;
    qu.push(1);
    qcnt.push(0);
    while (!qu.empty()) {
        int u = qu.front(), cnt = qcnt.front();
        iterate(u, i) {
            if (dist[u][cnt] + buf[i].weight < dist[buf[i].to][cnt + 1]) {
                dist[buf[i].to][cnt + 1] = dist[u][cnt] + buf[i].weight;
                qu.push(buf[i].to);
                qcnt.push(cnt + 1);
            }
        }
        qu.pop(); qcnt.pop();
    }
}
inline int getint();
int main() {
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
    n = getint(); m = getint(); T = getint();
    int u, v, l;
    for (int i = 1; i <= m; ++i) {
        u = getint(); v = getint(); l = getint();
        addedge(u, v, l);
        addedge(v, u, l);
    }
    spfa();
    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= n; ++j)
    //         printf("%d\n", dist[j][i]);
    // }
    // return 0;
    ll resu = 0;
    for (int i = 2; i <= n; ++i) {
        top = 0;
        for (int j = n - 1; j >= 0; --j) {
            if (dist[i][j] >= INF) continue;
            while (top > 1 && cross(stk[top - 2], dist[i][stk[top - 2]], stk[top - 1], dist[i][stk[top - 1]], j, dist[i][j]) >= 0) --top;
            stk[top++] = j;
        }
        static ll from[MXN];
        from[0] = 0;
        for (int j = 1; j < top; ++j) {
            from[j] = (dist[i][stk[j]] - dist[i][stk[j - 1]] + stk[j - 1] - stk[j] - 1) / (stk[j - 1] - stk[j]);
            from[j] = std::max(from[j], 0LL);
        }
        ll to = T + 1;
        for (int j = top - 1; j >= 0; --j) {
            if (from[j] >= to) continue;
            resu = ((ll)resu + ((ll)(from[j] + to - 1) * (to - from[j]) * stk[j] >> 1) % MOD) % MOD;
            resu = ((ll)resu + (ll)(to - from[j]) * dist[i][stk[j]]) % MOD;
            to = from[j];
        }
    }
    printf("%d\n", (int)resu);
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