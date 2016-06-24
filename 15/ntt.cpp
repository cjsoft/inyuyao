#include <iostream>
#include <cstdio>
#include <complex>
#include <cmath>
#define MXN 280007
using namespace std;
typedef int comp;
typedef long long ll;
const int MOD = 479 * (1 << 21) + 1;
const int yuangen = 3;
const int MXLEN = 21;
comp buffer[2][MXN], temp[MXN];
comp epi[MXN], revepi[MXN];
int bitrev[MXN];
int qpow(int x, int y) {
    int resu = 1;
    for (; y > 0; y >>= 1) {
        if (y & 1) {
            resu = (ll)resu * x % MOD;
        }
        x = (ll)x * x % MOD;
    }
    return resu;
}
inline int upp(int n) {int l = 1; for (; l < n; l <<= 1); return l;}
int ntt(int n, comp buffer[], comp epi[], int notconj) {
    int l = 0, t = 1;
    for (; t < n; t <<= 1, ++l);
    for (int i = 1; i < t; ++i) {
        bitrev[i] = (bitrev[i >> 1] >> 1) | ((i & 1) << (l - 1));
    }
    for (int i = 0; i < t; ++i) if (i < bitrev[i]) swap(buffer[i], buffer[bitrev[i]]);
    for (int i = 1, id = 1; i < t; i <<= 1, ++id) {
        int wn = epi[id];
        for (int j = 0; j < t; j += i << 1) {
            comp w = 1;
            for (int k = 0; k < i; ++k, w = (ll)w * wn % MOD) {
                comp x = buffer[j + k], y = (ll)w * buffer[j + k + i] % MOD;
                buffer[j + k] = (x + y) % MOD;
                buffer[j + k + i] = (x - y + MOD) % MOD;
            }
        }
    }
    int inv = qpow(t, MOD - 2);
    if (notconj == -1) for (int i = 0; i < t; ++i) buffer[i] = (ll)buffer[i] * inv % MOD;
    return t;
}
inline void init_epi() {
    epi[MXLEN] = qpow(yuangen, (MOD - 1) / (1 << MXLEN));
    for (int i = MXLEN - 1; i >= 0; --i)
        epi[i] = (ll)epi[i + 1] * epi[i + 1] % MOD;
    revepi[MXLEN] = qpow(epi[MXLEN], MOD - 2);
    for (int i = MXLEN - 1; i >= 0; --i)
        revepi[i] = (ll)revepi[i + 1] * revepi[i + 1] % MOD;
}
int n, m;
int main() {
    scanf("%d %d", &n, &m);
    int temp;
    int t = upp(n + m + 1);
    init_epi();
    for (int i = 0; i <= n; ++i) {
        scanf("%d", &temp);
        buffer[0][i] = temp;
        // buffer[0][i] = comp(temp, 0);
    }
    for (int i = 0; i <= m; ++i) {
        scanf("%d", &temp);
        // buffer[1][i] = comp(temp, 0);
        buffer[1][i] = temp;
    }
    ntt(t, buffer[0], epi, 1);
    ntt(t, buffer[1], epi, 1);
    for (int i = 0; i < t; ++i)
        buffer[1][i] = buffer[1][i] * (ll)buffer[0][i] % MOD;
    ntt(t, buffer[1], revepi, -1);
    for (int i = 0; i < n + m + 1; ++i) {
        printf("%d ", buffer[1][i]);
    }
}