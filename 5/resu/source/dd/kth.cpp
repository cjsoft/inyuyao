#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#define MXN 80007
#define INF 5000003
using namespace std;
int n, q;
int blk[MXN], raw[MXN];
int atag[MXN];
int size;
void build(int x) {
    int r = std::min(x * size + size, n + 1);
    for (int i = x * size; i < x * size + size; ++i) {
        blk[i] = raw[i];
    }
    sort(blk + x * size, blk + r);
}
void add(int a, int b, int k) {
    int l = a / size, r = b / size;
    if (l == r) {
        for (int i = a; i <= b; ++i) raw[i] += k;
        build(l);
        return;
    }
    for (int i = a; i < l * size + size; ++i) raw[i] += k;
    build(l);
    for (int i = l + 1; i < r; ++i) atag[i] += k;
    for (int i = r * size; i < r * size + size; ++i) raw[i] += k;
    build(r);
}
int count_lower(int a, int b, int k) {
    int l = a / size, r = b / size;
    int cnt = 0;
    if (l == r) {
        for (int i = a; i <= b; ++i) if (raw[i] + atag[l] < k) ++cnt;
        return cnt;
    }
    for (int i = a; i < l * size; ++i) if (raw[i] + atag[l] < k) ++cnt;
    for (int i = l + 1; i < r; ++i) cnt += lower_bound(blk + i * size, blk + i * size + size,  k - atag[i]) - blk;
    for (int i = r * size; i <= b; ++i) if (raw[i] + atag[r] < k) ++cnt;
    return cnt;
}
int query(int a, int b, int k) {
    int l = -INF, r = INF, mid;
    while (l + 1 < r) {
        mid = l + ((r - l) >> 1);
        if (count_lower(a, b, mid) > k - 1) r = mid;
        else l = mid;
    }
    return l;
}
int getint();
void printint(int);
int main() {
    // printint(231);
    freopen("kth.in", "r", stdin);
    // freopen("kth.out", "w", stdout);
    n = getint();
    size = max(1., 1.4 * sqrt(n));
    raw[0] = -INF;
    for (int i = 1; i <= n; ++i) raw[i] = getint();
    for (int i = 0; i <= n / size; ++i) build(i);
    q = getint();
    int a, b, c, d;
    while (q--) {
        a = getint(); b = getint(); c = getint(); d = getint();
        if (a == 1) {
            add(b, c, d);
        } else {
            printf("%d\n", query(b, c, d));
        }
    }
    return 0;
}
int rtn, f, ch;
int getint() {
    rtn = 0, f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}