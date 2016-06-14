#include <bits/stdc++.h>
#define f(x, y, z) for (int x = (y), _end_ = (z); x <= _end_; ++x)
#define g(x, y, z) for (int x = (y), _end_ = (z); x >= _end_; --x)
#define fe(x, y, z) for (int x = (y), _end_ = (z); x < _end_; ++x)
#define ge(x, y, z) for (int x = (y), _end_ = (z); x > _end_; --x)
#define h(x, y) for (int x = head[(y)]; x; x = nxt[x])
#define ms(a, b) memset(a, b, sizeof (a));
#define mp make_pair
#define pb push_back
#define rank LYF
using std::cout;
using std::endl;
template <typename Num> void write(Num x);
template <typename Num> void read(Num &x);
typedef long long ll;
const int maxn = 1e6 + 7;
const double eps = 1e-8;
// Varibles :
char c[maxn];
int a[maxn], n, sa[maxn], height[maxn], rank[maxn];
int tmp[maxn];
// Functions :
// Suffix Array
#define F(x) ((x) / 3 + ((x) % 3 == 1 ? 0 : tb))
#define G(x) ((x) < tb ? (x) * 3 + 1 : ((x) - tb) * 3 + 2)
int wa[maxn], wb[maxn], ws[maxn], wv[maxn];
inline int c0(int *r, int a, int b) {
    return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 1];
}
inline int cl2(int k, int *r, int a, int b) {
    if (k == 2) return r[a] < r[b] || r[a] == r[b] && cl2(1, r, a + 1, b + 1);
    else return r[a] < r[b] || r[a] == r[b] && wv[a + 1] < wv[b + 1];
}
inline void sort(int *r, int *a, int *b, int n, int m) {
    for (int i = 0; i < n; ++i) wv[i] = r[a[i]];
    for (int i = 0; i < m; ++i) ws[i] = 0;
    for (int i = 0; i < n; ++i) ws[wv[i]]++;
    for (int i = 1; i < m; ++i) ws[i] += ws[i - 1];
    for (int i = n - 1; i >= 0; i--) b[-- ws[wv[i]]] = a[i];
    return;
}
void dc3(int *r, int *sa, int n, int m) {
    int i, j, *rn = r + n, *san = sa + n, ta = 0, tb = (n + 1) / 3, tbc = 0, p;
    r[n] = r[n + 1] = 0;
    for (i = 0; i < n; ++i) if (i % 3 != 0) wa[tbc++] = i;
    sort(r + 2, wa, wb, tbc, m);
    sort(r + 1, wb, wa, tbc, m);
    sort(r, wa, wb, tbc, m);
    for (p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; ++i)
        rn[F(wb[i])] = c0(r, wb[i - 1], wb[i]) ? p - 1 : p++;
    if (p < tbc) dc3(rn, san, tbc, p);
    else for (i = 0; i < tbc; i++) san[rn[i]] = i;
    for (i = 0; i < tbc; ++i) if (san[i] < tb) wb[ta++] = san[i] * 3;
    if (n % 3 == 1) wb[ta++] = n - 1;
    sort(r, wb, wa, ta, m);
    for (i = 0; i < tbc; ++i) wv[wb[i] = G(san[i])] = i;
    for (i = 0, j = 0, p = 0; i < ta && j < tbc; p++)
        sa[p] = cl2(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
    for (; i < ta; p++) sa[p] = wa[i++];
    for (; j < tbc; p++) sa[p] = wb[j++];
    return;
}
bool cmp(int* r, int a, int b, int l) {
    return r[a] == r[b] && r[a + l] == r[b + l];
}
void da(int* r, int* sa, int n, int m) {
    int *x = wa, *y = wb;
    memset(ws, 0, sizeof(ws));
    for (int i = 0; i < n; ++i) ws[x[i] = r[i]]++;
    for (int i = 1; i < m; ++i) ws[i] += ws[i - 1];
    for (int i = n - 1; i >= 0; --i) sa[--ws[x[i]]] = i;
    int p = 1;
    for (int j = 1; p < n; j <<= 1, m = p) {
        p = 0;
        for (int i = n - j; i < n; ++i) y[p++] = i;
        for (int i = 0; i < n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
        memset(ws, 0, sizeof(ws));
        for (int i = 0; i < n; ++i) ws[wv[i] = x[y[i]]]++;
        for (int i = 1; i < m; ++i) ws[i] += ws[i - 1];
        for (int i = n - 1; i >= 0; --i) sa[--ws[wv[i]]] = y[i];
        std::swap(x, y);
        p = 1, x[sa[0]] = 0;
        for (int i = 1; i < n; ++i)
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
    }
}
void calheight(int* r, int* sa, int n) {
    for (int i = 1; i <= n; ++i) rank[sa[i]] = i;
    for (int i = 0, k = 0; i < n; height[rank[i++]] = k) {
        k ? k-- : 0;
        for (int j = sa[rank[i] - 1]; r[i + k] == r[j + k]; k++);
    }
}
bool cmpp(int a, int b) {
    return a > b;
}
ll ans = 0;
// Program :
int main() {
    freopen("sub.in", "r", stdin);
    freopen("sub.out", "w", stdout);
    gets(c);
    n = strlen(c);
    fe(i, 0, n) a[i] = c[i];
    da(a, sa, n + 1, 128);
    calheight(a, sa, n);
    int l = 1, r = l + 1;
    while (l < n) {
        while (height[r] != 0) r++;
        int len = r - l - 1;
        memcpy(tmp + 1, height + l + 1, (len) * sizeof (int));
        std::sort(tmp + 1, tmp + len + 1, cmpp);
        f(i, 1, len) ans = std::max(ans, (ll)tmp[i] * (i + 1));
        l = r; r++;
    }
    cout << ans << endl;
    fclose(stdin);
    fclose(stdout);
    return 0;
}
template <typename Num> void read(Num &x) {
    char c; int flag = 1;
    while ((c = getchar()) < '0' || c > '9') if (c == '-') flag *= -1;
    x = c - '0';
    while ((c = getchar()) >= '0' && c <= '9') x *= 10, x += c - '0';
    x *= flag;
}
template <typename Num> void write(Num x) {
    if (x == 0) { putchar('0'); return; }
    static int s[20]; int sl = 0;
    if (x < 0) putchar('-'), x = -x;
    while (x) s[sl++] = x % 10, x /= 10;
    while (sl--) putchar(s[sl] + '0');
}
