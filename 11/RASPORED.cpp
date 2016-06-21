#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MXT 100007
#define MXN 200007
#define lowbit(x) (x & -x)
using namespace std;
typedef long long ll;
int n, c;
ll L[MXN];
ll T[MXN];
ll sortingArray[MXN];
ll global_resu;
ll sigmaL;
ll ta[MXN];
int ta2[MXN];
void add(int pos, int data) {
    for (; pos < MXT; pos += lowbit(pos)) {
        ta[pos] += data;
        if (data > 0) ++ta2[pos];
        else --ta2[pos];
    }
}
ll sum(int pos) {
    ll rtn = 0;
    for (; pos > 0; pos -= lowbit(pos)) {
        rtn += ta[pos];
    }
    return rtn;
}
int sum2(int pos) {
    int rtn = 0;
    for (; pos > 0; pos -= lowbit(pos)) {
        rtn += ta2[pos];
    }
    return rtn;
}
inline int getint();
// inline void change(int pos, int nl, int nt) {
    // global_resu += sum(MXT) - sum(T[pos]);
    // global_resu -= (n - sum2(T[pos]) + 1) * T[pos];
    // add(T[pos], -T[pos]);
    // add(nt, nt);
    // global_resu -= sum(MXT) - sum(nt);
    // global_resu += (n - sum2(nt) + 1) * nt;
    // sigmaL += nl - L[pos];
    // T[pos] = nt;
    // L[pos] = nl;
// }
inline void change(int pos, int nl, ll nt) {
    // global_resu -= sum2(T[pos] - 1) * T[pos] + T[pos];
    // global_resu -= (sum2(T[pos]) - n - 1) * T[pos];
    // global_resu -= sum(MXT) - sum(T[pos]);
    global_resu -= (sum2(T[pos]) - n - 1) * T[pos];
    global_resu -= sum(MXT) - sum(T[pos]);
    add(T[pos], -T[pos]);
    global_resu += (sum2(nt) - n) * nt;
    global_resu += sum(MXT) - sum(nt);
    add(nt, nt);
    // global_resu += sum(MXT) - sum(nt);
    // global_resu += (sum2(nt - 1) - n) * nt;
    // global_resu += sum2(nt - 1) * nt + nt;
    sigmaL += nl - L[pos];
    T[pos] = nt;
    L[pos] = nl;
}
// void fix(int cpos, int idx, int sgn) {
    // global_resu += sgn * (ll)(sum2(MXT) - sum2(cpos) + 1) * T[idx];
    // global_resu += sgn * sum(cpos - 1);
    // add(cpos, sgn * T[idx]);
// }
int main() {
    n = getint(); c = getint();
    sigmaL = 0;
    global_resu = 0;
    for (int i = 1; i <= n; ++i) {
        L[i] = getint(); T[i] = getint();
        sortingArray[i] = T[i];
        sigmaL += L[i];
        add(T[i], T[i]);
    }
    sort(sortingArray + 1, sortingArray + 1 + n);
    for (int i = 1; i <= n; ++i) {
        global_resu += (i - n - 1) * sortingArray[i];
    }
    printf("%I64d\n", sigmaL + global_resu);
    int r, l, t;
    for (int i = 0; i < c; ++i) {
        r = getint(); l = getint(); t = getint();
        // fix(T[r], r, -1);
        // T[r] = t;
        // fix(t, r, 1);
        // sigmaL -= L[r] - l;
        // L[r] = l;
        change(r, l, t);
        printf("%I64d\n", sigmaL + global_resu);
    }
    return 0;
}
int getint() {
    static int rtn, f;
    static char ch;
    rtn = 0; f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn;
}
