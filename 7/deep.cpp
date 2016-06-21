#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define iterate(x, i) for (edge *i = head[x]; i; i = i->prev)
#define MXN 200007
using namespace std;

struct edge {
    int to;
    edge *prev;
} buf[MXN << 1 | 1], *head[MXN], *cur = buf;
int n, k;
int dp[MXN];
int sz[MXN], fa[MXN];
bool tag[MXN];
inline void addedge(int, int);
void dfs1(int root) {
    sz[root] = 1;
    iterate(root, i) {
        if (i->to == fa[root]) continue;
        fa[i->to] = root;
        dfs1(i->to);
        sz[root] += sz[i->to];
    }
}
// dp[i] > 0, i所在联通块包含果子
// 否则不包含
int limit;
void dfs2(int root) {
    if (sz[root] == 1) {
        if (tag[root])
            dp[root] = 1;
        else
            dp[root] = -1;
        return;
    }
    iterate(root, i) {
        if (i->to == fa[root]) continue;
        dfs2(i->to);
    }
    if (tag[root]) {
        dp[root] = 1;
        iterate(root, i) {
            if (i->to == fa[root]) continue;
            if (dp[i->to] < 0) dp[root] -= dp[i->to];
        }
    } else {
        int mxson = 0;
        iterate(root, i) {
            if (i->to == fa[root]) continue;
            if (dp[i->to] > 0 && dp[i->to] < dp[mxson]) mxson = i->to;
        }
        int sum = 1;
        iterate(root, i) {
            if (i->to == fa[root] && i->to == mxson) continue;
            if (dp[i->to] < 0) sum -= dp[i->to];
        }
        if (dp[mxson] != MXN && sum + dp[mxson] > limit) dp[root] = -sum;
        else if (dp[mxson] != MXN && sum + dp[mxson] <= limit) dp[root] = sum + dp[mxson];
        else dp[root] = -sum;
    }
    
}
bool validate(int x) {
    memset(dp, 0, sizeof(dp));
    dp[0] = MXN;
    limit = x;
    dfs2(1);
    if (dp[1] < 0) return false;
    else for (int i = 1; i <= n; ++i) if (dp[i] < -x || dp[i] > x) return false;
    return true;
}
inline int getint();
int main() {
    n = getint(); k = getint();
    int a, b;
    for (int i = 1; i < n; ++i) {
        a = getint();
        b = getint();
        addedge(a, b);
        addedge(b, a);
    }
    dfs1(1);
    for (int i = 0; i < k; ++i) {
        tag[getint()] = true;
    }
    int l = 0, r = n - k + 1;
    int mid;
    while (l + 1 < r) {
        mid = l + ((r - l) >> 1);
        if (validate(mid)) r = mid;
        else l = mid;
    }
    printf("%d\n", l + 1);
    return 0;
}
void addedge(int a, int b) {
    cur->to = b;
    cur->prev = head[a];
    head[a] = cur++;
}
int rtn, f;
char ch;
int getint() {
    rtn = 0; f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
