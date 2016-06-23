#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MOD 998244353LL
#define MXN 100007
using namespace std;
typedef long long ll;
struct mat {
    ll d[207][207];
    int n;
    mat() {
        memset(d, 0, sizeof(d));
        n = 0;
    }
};
struct Position {
    int x, y;
    Position() {x = y = 0;}
    Position(int xx, int yy) {x = xx; y = yy;}
    bool operator<(const Position &b) const {
        if (x != b.x) return x < b.x;
        return y < b.y;
    }
} obstacles[207];
ll ways[207];
ll inv[MXN << 1 | 1];
int st[207], ed[207];
ll jiecheng[MXN << 1 | 1];
int n, m, p, q;
mat tmp;
ll Ways(Position, Position);
ll Comb(int, int);
void initJiecheng(int, int);
ll det(const mat&);
inline ll getll();
void solve(int, mat&);
int main() {
    // freopen("canal.in", "r", stdin);
    // freopen("canal.out", "w", stdout);
    n = getll(); m = getll(); p = getll(); q = getll();
    for (int i = 0; i < p; ++i) {
        st[i] = getll();
    }
    sort(st, st + p);
    for (int i = 0; i < p; ++i) {
        ed[i] = getll();
    }
    sort(ed, ed + p);
    for (int i = 0; i < q; ++i) {
        obstacles[i].x = getll();
        obstacles[i].y = getll();
    }
    sort(obstacles, obstacles + q);
    initJiecheng(n, m);
    for (int i = 0; i < p; ++i)
        solve(i, tmp);
    tmp.n = p;
    printf("%lld\n", det(tmp));
}
ll getll() {
    static ll rtn, f;
    static char ch;
    rtn = 0, f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
ll qpow(ll x, int y) {
    ll rtn = 1;
    for (; y > 0; y >>= 1) {
        if (y & 1) rtn = rtn * x % MOD;
        x = x * x % MOD;
    }
    return rtn;
}
void initJiecheng(int n, int m) {
    int mmm = n + m;
    jiecheng[0] = 1;
    for (int i = 1; i <= mmm; ++i)
        jiecheng[i] = jiecheng[i - 1] * i % MOD;
    inv[n + m] = qpow(jiecheng[n + m], MOD - 2);
    for (int i = n + m - 1; i > 0; --i)
        inv[i] = inv[i + 1] * (i + 1) % MOD;
}
ll Comb(int n, int m) {
    if (n < 0 || m < 0 || m > n) return 0;
    if (n == m || m == 0) return 1;
    return jiecheng[n] * inv[m] % MOD * inv[n - m] % MOD;
}
ll Ways(Position a, Position b) {
    return Comb(b.x - a.x + b.y - a.y, b.x - a.x);
}
ll det(const mat &b) {
    static mat a;
    a = b;
    int i, j, k;
    ll ans = 1;
    bool flag = 1;
    for (i = 0; i < a.n; i++)
        for (j = 0; j < a.n; j++)
            a.d[i][j] = (a.d[i][j] + MOD) % MOD;
    for (i = 0; i < a.n; i++) {
        for (j = i + 1; j < a.n; j++)
            while (a.d[j][i]) {
                ll t = a.d[i][i] / a.d[j][i];
                for (k = i; k < a.n; k++)
                    a.d[i][k] = (a.d[i][k] + MOD - t * a.d[j][k] % MOD) % MOD;
                for (k = i; k < a.n; k++)
                    swap(a.d[i][k], a.d[j][k]);
                flag ^= 1;
            }
        ans = ans * a.d[i][i] % MOD;
        if (!ans) return 0;
    }
    if (!flag) ans = (MOD - ans);
    return ans;
}
void solve(int o, mat &b) {
    for (int i = 0; i < q; ++i) {
        ways[i] = Ways(Position(0, st[o]), obstacles[i]);
        for (int j = 0; j < i; ++j) ways[i] = (ways[i] - ways[j] * Ways(obstacles[j], obstacles[i])) % MOD;
    }
    for (int i =0; i < p; ++i) {
        b.d[o][i] = Ways(Position(0, st[o]), Position(n, ed[i]));
        for (int j = 0; j < q; ++j) b.d[o][i] = (b.d[o][i] - ways[j] * Ways(obstacles[j], Position(n, ed[i]))) % MOD;
    }
}