#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define MXN 2500
#define MOD 1000000007LL
#define INF 0x3f3f3f30
#define iterate(x, i, v, w) for (int i = head[x], v = buf[i].to, w = buf[i].weight; i; i = buf[i].prev, v = buf[i].to, w = buf[i].weight)
using namespace std;
typedef long long ll;
int n, m, t;
ll dis[MXN]; int cnt[MXN];
char inq[MXN];
struct edge {int prev, to; ll weight;} buf[MXN << 1 | 1];
int head[MXN], ctot = 1;
void spfa() {
    queue<int> Q;
    for (int i = 0; i <= n; i++) {
        dis[i] = INF;
        cnt[i] = 0;
        inq[i] = 0;
    }
    dis[1] = cnt[1] = 0;
    inq[1] = 1; Q.push(1);
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        iterate(u, i, v, w) {
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                if (!inq[v])
                    Q.push(v);
            }
        }
    }
}
inline void addedge(int a, int b, ll weight) {
    buf[ctot].prev = head[a];
    buf[ctot].weight = weight;
    buf[ctot].to = b;
    head[a] = ctot++;

}
inline int getint();
int main() {
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    n = getint(); m = getint(); t = getint();
    int a, b, c;
    for (int i = 1; i <= m; ++i) {
        a = getint(); b = getint(); c = getint();
        addedge(a, b, c);
        addedge(b, a, c);
    }
    ll resu = 0;
    spfa();
    for (int i = 2; i <= n; ++i)
        resu += dis[i], resu %= MOD;
    for (int i = 1; i <= t; ++i) {
        for (int i = 1; i < ctot; ++i) {
            buf[i].weight++;
        }
        spfa();
        for (int i = 2; i <= n; ++i)
            resu += dis[i], resu %= MOD;
    }
    printf("%lld\n", resu);
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
