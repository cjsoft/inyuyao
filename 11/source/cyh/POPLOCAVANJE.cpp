#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define BASE 23
#define MXN 300007
#define MXM 5007
#define MOD 21914624432020321LL
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n, m;
char raw[MXN];
char pattern[MXN];
int len[MXM];
ull hashes[MXM];
ull h[MXN];
int presummix[MXN];
ull hummix[MXN];
vector<int> hss[27];
inline int getint();
int main() {
    freopen("POPLOCAVANJE.in", "r", stdin);
    freopen("POPLOCAVANJE.out", "w", stdout);
    n = getint();
    h[0] = 1;
    for (int i = 1; i <= n; ++i)
        h[i] = h[i - 1] * BASE/* % MOD*/;
    scanf("%s", raw + 1);
    m = getint();
    for (int i = 0; i < m; ++i) {
        scanf("%s", pattern);
        len[i] = strlen(pattern);
        for (int j = 0; j < len[i]; ++j)
            hashes[i] = (hashes[i] * BASE/* % MOD*/ + pattern[j] - 'a' + 1)/* % MOD*/;
        hss[pattern[len[i] - 1] - 'a'].push_back(i);
        // printf("   %I64u\n", hashes[i]);
    }
    ull tmphash = 0;
    int tmp;
    for (int i = 1; i <= n; ++i) {
        hummix[i] = (hummix[i - 1] * BASE/* % MOD*/ + raw[i] - 'a' + 1)/* % MOD*/;
        for (int j = 0; j < hss[raw[i] - 'a'].size(); ++j) {
            tmp = hss[raw[i] - 'a'][j];
            if (i >= len[tmp] && hummix[i] - hummix[i - len[tmp]] * h[len[tmp]] == hashes[tmp]) {
                ++presummix[i - len[tmp] + 1];
                --presummix[i + 1];
            }
        }
    }
    int resu = 0;
    for (int i = 1; i <= n; ++i)
        presummix[i] += presummix[i - 1];
    for (int i = 1; i <= n; ++i)
        if (presummix[i] == 0)
            ++resu;
    printf("%d\n", resu);
    return 0;
}
int getint() {
    static int rtn, f;
    static char ch;
    rtn = 0;
    f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
