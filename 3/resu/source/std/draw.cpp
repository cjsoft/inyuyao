/* Copyright 2016 AcrossTheSky */
#include <iostream>
#include <cstdio>
#include <utility>
#include <cassert>
#include <map>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#define REP(i, a, b) for (int i = (a); i <= (b); ++i)
#define PER(i, a, b) for (int i = (a); i >= (b); --i)
#define RVC(i, c) fot (int i = 0; i < (c).size(); ++i)
#define RED(k, u) for (int k = head[(u)]; k; k = edge[k].next)
#define lowbit(x) ((x) & (-(x)))
#define CL(x, v) memset(x, v, sizeof x)
#define MP std::make_pair
#define PB push_back
#define FR first
#define SC second
#define rank rankk
#define next nextt
#define link linkk
#define index indexx
#define abs(x) ((x) > 0 ? (x) : (-(x)))
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

template<class T> inline
bool getmin(T *a, const T &b) {
    if (b < *a) {
        *a = b;
        return true;
    }
    return false;
}

template<class T> inline
bool getmax(T *a, const T &b) {
    if (b > *a) {
        *a = b;
        return true;
    }
    return false;
}

template<class T> inline
void read(T *a) {
    char c;
    while (isspace(c = getchar())) {}
    bool flag = 0;
    if (c == '-') flag = 1, *a = 0;
    else
        *a = c - 48;
    while (isdigit(c = getchar())) *a = *a * 10 + c - 48;
    if (flag) *a = -*a;
}
const int mo = 1000000007;
template<class T>
T pow(T a, T b, int c = mo) {
    T res = 1;
    for (T i = 1; i <= b; i <<= 1, a = 1LL * a * a % c) if (b & i) res = 1LL * res * a % c;
    return res;
}
/*======================= TEMPLATE =======================*/
const int N = 32001;
int mem[N][850];
int& g(int i, int j) {
    return mem[i][j + 420];
}
int dep[N], f[N], w[N];
int flag[N];
PII a[N];
int tot;
struct node {
    int p, next, w;
}edge[N * 2];
int n;
int cnt, head[N];
int h[N];
void ae(int a, int b, int c) {
    edge[++cnt].p = b;
    edge[cnt].next = head[a];
    edge[cnt].w = c;
    head[a] = cnt;
}

void dfs(int u, int fa) {
    h[u] = h[fa] + 1;
    RED(k, u) {
        int v = edge[k].p;
        if (v == fa) continue;
        dfs(v, u);
        w[v] = edge[k].w;
        getmax(&dep[u], dep[v] + 1);
        a[++tot] = MP(edge[k].w, v);
        f[v] = u;
    }
}

LL ans = 0;
int sum = 0;

void modify(int p) {
    for (int i = p, k = 0; i; k += flag[i] * 2 - 1, i = f[i]) if (i != p) {
        REP(j, -dep[p], dep[p]) g(i, j + k) -= g(p, j);
    }
    flag[p] = 1;
    for (int i = p, k = 0; i; k += flag[i] * 2 - 1, i = f[i]) if (i != p) {
        REP(j, -dep[p], dep[p]) g(i, j + k) += g(p, j);
    }
}

void getans(int p) {
    int tmp = 0;
    for (int i = p, k = 0; i != 1; k += flag[i] * 2 - 1, i = f[i]) {
        int t = k + flag[i] * 2 - 1;
      //  if (p == 5) cerr << t << endl;
        REP(j, -dep[p], dep[p]) {
            int x = (g(f[i], -j + 1 - t) - g(i, -j + 1 - 2 * t + k)) * g(p, j);
            tmp += x;
        }
    }
    ans += 1LL * tmp * w[p];
}


int main() {
    freopen("draw.in", "r", stdin);
    freopen("draw.out", "w", stdout);
    cin >> n;
    REP(i, 2, n) {
        int x, y, z;
        read(&x); read(&y); read(&z);
        ae(x, y, z);
        ae(y, x, z);
    }
    int mx = 0;
    dfs(1, 0);
    REP(i, 1, n) for (int j = i, k = 0; j; j = f[j], --k) g(j, k)++;
    sort(a + 1, a + n);
    REP(i, 1, n - 1) modify(a[i].SC), getans(a[i].SC);
    cout << ans << endl;
    return 0;
}
