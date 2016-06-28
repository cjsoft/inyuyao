#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MXK 43
#define MXN 43
#define MOD 1000000007
using namespace std;
typedef long long ll;
ll fac[MXK], inv[MXK];
inline ll getll();
void init_fac();
int main() {

    return 0;
}
ll qpow(ll x, int y) {
    ll rtn = 1;
    for (; y; y >>= 1) {
        if (y & 1) rtn = rtn * x % MOD;
        x = x * x % MOD
    }
}
void init_fac() {
    int n = MXK - 1;
}

ll getll() {
    static ll rtn, f;
    static char ch;
    rtn = 0; f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}