#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int getint();
char ops[7];
int a[100007];
int mx[100007];
int n, type;
int main() {
    freopen("binary.in", "r", stdin);
    freopen("binary.out", "w", stdout);
    n = getint(); scanf("%s", ops); type = getint();
    for (int i = 1; i <= n; ++i) a[i] = getint();
    if (ops[0] == 'a') {
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                mx[i] = max(mx[i], a[i] & a[j]);
            }
        }
    } else if (ops[0] == 'o') {
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                mx[i] = max(mx[i], a[i] | a[j]);
            }
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                mx[i] = max(mx[i], a[i] ^ a[j]);
            }
        }
    }
    if (type == 0) {
        for (int i = 2; i <= n; ++i)
            printf("%d\n", mx[i]);
    } else {
        for (int i = 2; i <= n; ++i) {
            int ans = 0;
            for (int j = 1; j < i; ++j) {
                if (ops[0] == 'a') {
                    if ((a[i] & a[j]) == mx[i]) ++ans;
                } else if (ops[0] == 'o') {
                    if ((a[i] | a[j]) == mx[i]) ++ans;
                } else {
                    if ((a[i] ^ a[j]) == mx[i]) ++ans;
                }
            }
            printf("%d %d\n", mx[i], ans);
        }
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
    return rtn * f;
}
