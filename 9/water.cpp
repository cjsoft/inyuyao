#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MXN 100007
using namespace std;
typedef long long ll;
int arr[MXN];
int n, k;
ll resu = 0;
inline int getint();
bool cmp(int a, int b) {
    return a > b;
}
int jiecheng[MXN];
int trans() {
    int p = 1;
    ll lst = -0x3f3f3f3f3fLL, mtp;
    for (int i = 1; i < n; ++i) {
        mtp = (ll)(arr[i] - arr[i + 1]) * i + (ll)(arr[i + 1] - arr[i]) * (i + 1);
        if (mtp <= 0 && mtp > lst) {
            p = i;
            lst = mtp;
        }
    }
    resu += lst;
    return 1;
}
int main() {
    freopen("water.in", "r", stdin);
    freopen("water.out", "w", stdout);
    n = getint(); k = getint();
    jiecheng[0] = 1;
    for (int i = 1; i <= n; ++i) {
        arr[i] = getint();
        jiecheng[i] = jiecheng[i - 1] * i;
    }
    sort(arr + 1, arr + n + 1, cmp);
    resu = 0;
    if (k == 1) {
        for (int i = 1; i <= n; ++i) {
            resu += (ll)arr[i] * i;
        }
        printf("%lld\n", resu);
    } else {
        for (int i = 1; i <= n; ++i) {
            resu += (ll)arr[i] * i;
        }
        printf("%lld\n", resu);
        trans();
        printf("%lld\n", resu);
    }
    return 0;
}

int getint() {
    int rtn = 0, f = 1;
    char ch;
    for (ch = getchar(); ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') f = -f;
    for (rtn = ch - '0', ch = getchar(); ch >= '0' && ch <= '9'; ch = getchar()) rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
