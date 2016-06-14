#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MXN 100007
using namespace std;
typedef long long ll;
int a[MXN], b[MXN];
int n;
int main() {
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
    scanf("%d", &n);
    ll resu = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
    }
    for (int i = 0; i < 19; ++i) {
        int cnt = 0;
        for (int j = 1; j <= MXN; ++j) {
            if (a[j] >> i & 1) ++cnt;
        }
        for (int j = 1; j <= cnt; ++j) {
            b[j] |= 1 << i;
        }
    }
    for (int i = 1; i <= n; ++i) {
        resu += (ll)b[i] * b[i];
    }
    printf("%I64d\n", resu);
    return 0;
}
