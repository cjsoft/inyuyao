#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MXN 100007
using namespace std;
typedef long long ll;
int a[MXN];
int n;
int main() {
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    scanf("%d", &n);
    ll resu = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        resu += (ll)a[i] * a[i];
    }
    while (true) {
        int add = 0, l = 1, r = 1;
        for (int i = 1; i < n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if ((ll)(a[i] & a[j]) * (a[i] & a[j]) + (ll)(a[i] | a[j]) * (a[i] | a[j]) - (ll)a[i] * a[i] - (ll)a[j] * a[j] > add) {
                    add = (ll)(a[i] & a[j]) * (a[i] & a[j]) + (ll)(a[i] | a[j]) * (a[i] | a[j]) - (ll)a[i] * a[i] - (ll)a[j] * a[j];
                    l = i; r = j;
                }
            }
        }
        if (add <= 0) break;
        resu += add;
        int q = a[l] & a[r], w = a[l] | a[r];
        a[l] = q; a[r] = w;
    }
    printf("%lld\n", resu);
    return 0;
}
