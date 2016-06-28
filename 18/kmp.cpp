#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MXN 100003
#define MOD 1000000007
using namespace std;
int fail[MXN];
int qqq[MXN];
int raw[MXN];
int global_resu = 0;
int n, c;
bool kmp(int[], int);
void dfs(int pos) {
    if (pos == n + 1) {
        if (kmp(raw, n) == true) {
            ++global_resu;
        }
        return;
    }
    for (int i = 1; i <= c; ++i) {
        raw[pos] = i;
        dfs(pos + 1);
    }
}
bool kmp(int raw[], int n) {
    memset(fail, 0, sizeof(fail));
    for (int i = 1; i <= n; ++i) {
        int j = i - 1;
        while (j > 0) {
            if (raw[i] == raw[j]) {
                fail[i] = j;
                if (i > 1 && qqq[i] != j) return false; 
                break;
            }
            j = fail[j];
        }
    }
    return true;
}
inline int getint() {
    static int rtn, f;
    static char ch;
    rtn = 0; f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
int main() {
    freopen("kmp.in", "r", stdin);
    freopen("kmp.out", "w", stdout);
    n = getint(); c = getint();
    for (int i = 2; i <= n; ++i) {
        qqq[i] = getint();
    }
    dfs(1);
    printf("%d\n", global_resu);
    return 0;
}
