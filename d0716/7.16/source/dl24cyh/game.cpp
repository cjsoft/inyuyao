#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MXN 50007
#define INF 0x3f3f3f3f3f3f3f3fLL
using namespace std;
typedef long long ll;
template<typename T> inline void checkmin(T &a, T b) { if (a > b) a = b; }
struct data {
    int type;
    ll a, b, c;
    bool operator<(const data &B) const {
        // return max(B.a, b) < max(a, B.b);
        return min(a, B.b) < min(B.a, b);
        if (type == B.type) {
            if (type == 1) return a < B.a;
            else if (type == 2) return a > B.a;
        } else {
            return type < B.type;
        }
    }
} buf[MXN];
char tag[MXN];
int seq[MXN];
int n;
ll global_resu;
void solve() {
    ll sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += buf[seq[i]].a;
        buf[seq[i]].c = max(buf[seq[i - 1]].c, sum) + buf[seq[i]].b;
    }
    // if (buf[seq[n]].c == 329) for (int i = 1; i <= n; ++i) printf("  %d\n", seq[i]);
    checkmin(global_resu, buf[seq[n]].c);
}
void init() {
    memset(buf, 0, sizeof(buf));
    for (int i = 0; i < MXN; ++i) seq[i] = i;
    memset(tag, 0, sizeof(tag));
    global_resu = INF;
}
void dfs(int pos) {
    if (pos > n) {
        solve();
        return;
    }
    for (int i = 1; i <= n; ++i) {
        if (!tag[i]) {
            tag[i] = 1;
            seq[pos] = i;
            dfs(pos + 1);
            tag[i] = 0;
            seq[pos] = 0;
        }
    }
}

int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    int T;
    scanf("%d", &T);
    while (T--) {
        init();
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%lld %lld", &buf[i].a, &buf[i].b);
            if (buf[i].a >= buf[i].b) buf[i].type = 2;
            else buf[i].type = 1;
        }
        if (n > 9 || 1) {
            sort(buf + 1, buf + 1 + n);
            solve();
        } else {
            dfs(1);
        }
        printf("%lld\n", global_resu);
    }
    return 0;
}
