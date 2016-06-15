#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define MXN 5000007
using namespace std;
typedef long long ll;
int blk[MXN], raw[MXN];
int atag[MXN];
int n, size;

int qqsolve(int a, int b, int k) {
    int l = a, r = b, mid, x = a / size;
    while (l + 1 < r) {
        mid = l + ((r - l) >> 1);
        if (blk[mid] + atag[x] < k) l = mid;
        else r = mid;
    }
    if (!x || (blk[a] + atag[x] >= k && a == l)) return l - a;
    else return l - a + 1;
}
inline void build(int x) {
    int r = std::min(x * size + size, n + 1);
    // release(x);
    for (int i = x * size; i < r; ++i) {
        blk[i] = raw[i];
    }
    sort(blk + x * size, blk + r);
}
inline int count_lower(int p, int q, int x) {
    int l = p / size, r = q / size;
    int cnt = 0;
    if (l == r) {
        for (int i = p; i <= q; ++i) 
            if (i && raw[i] + atag[l] < x) ++cnt;
        return cnt;
    }
    for (int i = p; i < l * size + size; ++i) {
        if (i && raw[i] + atag[l] < x) ++cnt;
    }
    for (int i = l + 1; i < r; ++i) {
        cnt += qqsolve(i * size, i * size + size, x);
    }
    for (int i = r * size; i <= q; ++i) {
        if (raw[i] + atag[r] < x) ++cnt;
    }
    return cnt;
}
// inline int query(int a, int b, int c) {
//     int l = a / size, r = b / size;
//     int u = MXN, d = -MXN + 6, mid;
//     while (d < u) {
//         mid = (d + u + 1) / 2;
//         if (count_lower(a, b, mid) <= c - 1) d = mid;
//         else u = mid - 1;
//     }
//     // if (d == -4643)
//     //     puts("1");
//     return d;
// }
int query(int a, int b, int k) {
    int l = -MXN, r = MXN, mid;
    while (l + 1 < r) {
        mid = l + ((r - l) >> 1);
        if (count_lower(a, b, mid) > k - 1) r = mid;
        else l = mid;
    }
    return l;
}
inline void add(int a, int b, int data) {
    int l = a / size, r = b / size;
    if (l == r) {
        for (int i = a; i <= b; ++i) {
            raw[i] += data;
        }
        build(l);
        return;
    }
    for (int i = a; i < l * size + size; ++i) {
        if (i) raw[i] += data;
    }
    build(l);
    for (int i = l + 1; i < r; ++i) {
        atag[i] += data;
    }
    for (int i = r * size; i <= b; ++i) {
        raw[i] += data;
    }
    build(r);
}
int getint() {
    int rtn = 0, f = 1;
    char ch;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}

int main() {
    freopen("kth.in", "r", stdin);
    freopen("kth.out", "w", stdout);
    n = getint();
    size = max(1., 1.4 * sqrt(n * 1.));
    raw[0] = -MXN;
    for (int i = 1; i <= n; ++i) {
        raw[i] = getint();
    }
    for (int i = 0; i <= n / size; ++i)
        build(i);
    int Q, a, b, c, d;
    Q = getint();
    for (int i = 0; i < Q; ++i) {
        a = getint(); b = getint(); c = getint(); d = getint();
        if (a == 1) {
            add(b, c, d);
        } else {
            printf("%d\n", query(b, c, d));
        }
    }
}
