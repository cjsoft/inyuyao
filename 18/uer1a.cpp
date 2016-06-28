#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;
ll g, l;
inline ll getll() {
    static ll rtn, f;
    static char ch;
    rtn = 0; f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
int main() {
    int T = getll();
    while (T--) {
        g = getll(); l = getll();
        printf("%lld %lld\n", 2 * ll(sqrt((double)l / g) + 0.5) * g, g * (l / g) + g);
    }
    return 0;
}