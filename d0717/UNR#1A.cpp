#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define mid(_l, _r) (_l + (_r - _l) / 2)
#define iterate(x, i) for (edge *i = head[x]; i; i = i->prev)
#define MXN 500007
#define MOD 998244353
#define INF 0x3f3f3f3f
template <typename T> inline void checkmax(T &a, T b) { if (b > a) a = b; }
using namespace std;
typedef long long ll;
int a[MXN], b[MXN], f[MXN], n;
int ans = 0, now = 0;
inline int getint() {
    static int rtn, f;
    static char ch;
    rtn = 0; f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
void solve(int l, int r) {
// f[i] 长度为i的结果与长度为i-1的结果之差
// a[i] 为原数组
// b[i] 为临时数组，用于存放b[i, mid]/[mid + 1, i]的最大值
    if (l > r) return;
    if (l == r) {
        f[1] = (f[1] + a[l]) % MOD;
        f[2] = (f[2] - a[l] + MOD) % MOD;
        return;
    }
    int m = mid(l, r), now, pre;
    solve(l, m); solve(m + 1, r);
    b[m] = a[m];
    for (int i = m - 1; i >= l; --i) b[i] = max(b[i + 1], a[i]);
    b[m + 1] = a[m + 1];
    for (int i = m + 2; i <= r; ++i) b[i] = max(b[i - 1], a[i]);
    b[r + 1] = INF; b[l - 1] = INF;
    now = m + 1;
    for (int i = m; i >= l; --i) {
        while (b[now] <= b[i]) ++now;
        f[m - i + 2] = (f[m - i + 2] + b[i]) % MOD;
        f[now - i + 1] = (f[now - i + 1] - b[i] + MOD) % MOD;
    }
    now = m;
    for (int i = m + 1; i <= r; ++i) {
        while (b[now] < b[i]) --now;
        f[i - m + 1] = (f[i - m + 1] + b[i]) % MOD;
        f[i - now + 1] = (f[i - now + 1] - b[i] + MOD) % MOD;
    }
}
int main() {
    n = getint();
    for (int i = 1; i <= n; ++i) a[i] = getint();
    solve(1, n);
    ans = now = 0;
    for (int i = 1; i <= n; ++i) {
        now = ((now + f[i]) % MOD + MOD) % MOD;
        ans ^= now;
    }
    printf("%d\n", ans);
    return 0;
}