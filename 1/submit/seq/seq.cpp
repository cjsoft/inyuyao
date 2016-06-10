#include <iostream>
#include <cstdio>
#include <algorithm>
#define MXN 10007

typedef long long ll;

ll seq[MXN];

inline ll sum(int l, int r) {
    ll rtn = 0;
    for (int i = l; i <= r; ++i) {
        rtn += seq[i] >= 0 ? seq[i] : -seq[i];
    }
    return rtn;
}
inline void flip(int l, int r) {
    for (int i = l; i <= r; ++i) {
        seq[i] = -seq[i];
    }
}
inline void add(int l, int r, ll data) {
    for (int i = l; i <= r; ++i) {
        seq[i] += data;
    }
}
int n, m;
int main() {
    freopen("seq.in", "r", stdin);
    freopen("seq.out", "w", stdout);
    scanf("%d %d", &n, &m);
    int a, b, c;
    ll d;
    for (int i = 0; i < n; ++i) {
        scanf("%I64d", seq + i);
    }
    while (m--) {
        scanf("%d %d %d", &a, &b, &c);
        if (a == 0) {
            scanf("%I64d", &d);
            add(b, c, d);
        } else if (a == 1) {
            flip(b, c);
        } else {
            printf("%I64d\n", sum(b, c));
        }
    }
}
