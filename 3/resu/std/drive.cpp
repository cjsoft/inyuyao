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
#include <cassert>
const int N = 52001;
struct edge_node {
    int p, next;
}edge[N * 120];
int n;
int cnt;

queue<int> q;

LL sum;
struct node {
    map<int, int> S;
    vector<int> dl, dr;
    vector<int> v;
    int ll, rr;
    int l, r;
    vector<int> head;

    void ae(int a, int b) {
        edge[++cnt].p = b;
        edge[cnt].next = head[a];
        head[a] = cnt;
    }
    node() {
        S.clear(); dl.clear(), dr.clear();
    }
    void bfs() {
        while (!q.empty()) q.pop();
        dl.resize(v.size());
        dr.resize(v.size());
        dl[l] = 0;
        q.push(l);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            RED(k, u) {
                int v = edge[k].p;
                if (!dl[v] && v != l) {
                    dl[v] = dl[u] + 1;
                    q.push(v);
                }
            }
        }
        dr[r] = 0;
        q.push(r);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            RED(k, u) {
                int v = edge[k].p;
                if (!dr[v] && v != r) {
                    dr[v] = dr[u] + 1;
                    q.push(v);
                }
            }
        }
    }
    PII split() {
        int d = n + 1; PII p;
        REP(i, 0, v.size() - 1) {
            int u = i;
            RED(k, u) {
                int v = edge[k].p;
                if (v <= i + 1) continue;
                int l = v - i + 1;
                getmax(&l, (int)S.size() - l + 2);
                if (l < d) d = l, p = MP(i, v);
            }
        }
        return p;
    }

}tree[120000];

int mark[N];

int dep = 0;
int idx;

void build(int u) {
    //cerr << (++dep) << endl;
    if (tree[u].v.size() <= 3) {
        //   --dep;
        return;
    }
    PII tmp = tree[u].split();
    int L = tmp.FR, R = tmp.SC;
    assert(L != R);
    int l = ++idx, r = ++idx;
    tree[u].ll = l, tree[u].rr = r;
    tree[u].l = L, tree[u].r = R;
    int nl = 0, nr = 0;
    tree[u].bfs();
    REP(i, L, R) tree[l].v.PB(tree[u].v[i]), tree[l].S.insert(MP(tree[u].v[i], nl++));
    REP(i, 0, L) tree[r].v.PB(tree[u].v[i]), tree[r].S.insert(MP(tree[u].v[i], nr++));
    REP(i, R, tree[u].v.size() - 1) tree[r].v.PB(tree[u].v[i]), tree[r].S.insert(MP(tree[u].v[i], nr++));
    tree[l].head.resize(tree[l].v.size());
    tree[r].head.resize(tree[r].v.size());
    REP(i, L, R) for (int k = tree[u].head[i]; k; k = edge[k].next) {
        int v = edge[k].p;
        int y = tree[u].v[edge[k].p];
        int x = tree[u].v[i];
        if (v <= R && v >= L) tree[l].ae(tree[l].S[x], tree[l].S[y]);
    }
    REP(i, 0, L) for (int k = tree[u].head[i]; k; k = edge[k].next) {
        int v = edge[k].p;
        int y = tree[u].v[edge[k].p];
        int x = tree[u].v[i];
        if (v <= L || v >= R) tree[r].ae(tree[r].S[x], tree[r].S[y]);
    }
    REP(i, R, tree[u].v.size() - 1) for (int k = tree[u].head[i]; k; k = edge[k].next) {
        int v = edge[k].p;
        int y = tree[u].v[edge[k].p];
        int x = tree[u].v[i];
        if (v <= L || v >= R) tree[r].ae(tree[r].S[x], tree[r].S[y]);
    }
    build(l); 
    build(r);
    // --dep;
}
int query(int u, int x, int y) {
    if (tree[u].v.size() == 3) return 1;
    vector<int> &dl = tree[u].dl;
    vector<int> &dr = tree[u].dr;
    map<int, int> &S = tree[u].S;
    if (S[x] >= tree[u].l && S[x] <= tree[u].r) {
        if (S[y] >= tree[u].l && S[y] <= tree[u].r) return query(tree[u].ll, x, y);
        else 
            return min(dl[S[x]] + dl[S[y]], dr[S[x]] + dr[S[y]]);
    } else {
        if (S[y] >= tree[u].l && S[y] <= tree[u].r) return min(dl[S[x]] + dl[S[y]], dr[S[x]] + dr[S[y]]);
        else 
            return query(tree[u].rr, x, y);
    }
}
int main() {
	freopen("drive.in", "r", stdin);
	freopen("drive.out", "w", stdout);
    cin >> n;
    idx = 1;
    REP(i, 1, n) tree[1].v.PB(i), tree[1].S.insert(MP(i, i - 1));
    tree[1].head.resize(n);
    REP(i, 0 , n - 2) tree[1].ae(i, i + 1), tree[1].ae(i + 1, i);
    tree[1].ae(n - 1, 0); tree[1].ae(0, n - 1);
    REP(i, 1, n - 3) {
        int x, y;
        read(&x); read(&y);
        x--, y--;
        tree[1].ae(x, y); tree[1].ae(y, x);
    }
    build(1);
    int q;
    cin >> q;
    while (q--) {
        int x, y;
        read(&x); read(&y);
        if (x == y) printf("0\n");
        else 
            printf("%d\n", query(1, x, y));
    }
    return 0;
}
