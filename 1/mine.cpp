#include <iostream>
#include <cstdio>
#include <cstring>
#define lowbit(x) (x & -x)
#define MXN 2007
typedef long long ll;
using namespace std;
int l[MXN][MXN], r[MXN][MXN], u[MXN][MXN], d[MXN][MXN];
int ta[MXN];
int prev[MXN << 1 | 1], data[MXN << 1 | 1], head[MXN], tot;
int n, m;
inline void add(int pos, int data) {
    for (; pos <= n; pos += lowbit(pos)) ta[pos] += data;
}
inline int sum(int pos) {
    int rtn = 0;
    for (; pos > 0; pos -= lowbit(pos)) rtn += ta[pos];
    return rtn;
}
inline void append(int a, int d) {
    data[tot] = d;
    prev[tot] = head[a];
    head[a] = tot++;
}
int main() {
    scanf("%d %d", &n, &m);
    int x1, y1, x2, y2;
    ++n;
    while (m--) {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        ++x1; ++x2; ++y1; ++y2;
        if (x1 == x2) {
            if (y1 > y2) swap(y1, y2);
            for (int i = y1; i <= y2; ++i)
                u[x1][i] = y2, d[x1][i] = y1;
        } else {
            if (x1 > x2) swap(x1, x2);
            for (int i = x1; i <= x2; ++i)
                l[i][y1] = x1, r[i][y1] = x2;
        }
    }
    ll resu = 0;
    for (int i = -n; i <= n; ++i) {
        tot = 2;
        for (int j = 0; j <= n; ++j) head[j] = ta[j] = 0;
        for (int x = max(1 - i, 1); x <= n; ++x) {
            int y = x + i;
            if (y > n) break;
            if (!r[x][y] || !u[x][y]) continue;
            int det = min(r[x][y] - x, u[x][y] - y);
            append(x, x);
            if (x + det + 1 <= n) append(x + det + 1, -x);
        }
        //puts("s");
        for (int x = max(1, 1 - i); x <= n; ++x) {
            int y = x + i;
            if (y > n) break;
            for (int j = head[x]; j; j = prev[j]) {
                int k = data[j];
                printf(" -- %d\n", k);
                if (k > 0) add(k, 1);
                else add(-k, -1);
            }
            if (!l[x][y] || !d[x][y]) continue;
            int det = std::min(x - l[x][y], y - d[x][y]);
            int t = sum(x - 1) - sum(x - det - 1);
            resu += t;
        }
    }
    printf("%lld\n", resu);
    return 0;
}
