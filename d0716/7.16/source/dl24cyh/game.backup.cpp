#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MXN 50007
using namespace std;
typedef long long ll;
template<typename T> inline void checkmin(T &a, T b) { if (a > b) a = b; }
struct data {
    int type;
    ll a, b, c;
    bool operator<(const data &B) const {
        if (type == B.type) {
            if (type == 1) return a < B.a;
            else if (type == 2) return a > B.a;
        } else {
            return type < B.type;
        }
    }
} buf[MXN];
int n;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%lld %lld", &buf[i].a, &buf[i].b);
            if (buf[i].a >= buf[i].b) buf[i].type = 2;
            else buf[i].type = 1;
        }
        sort(buf + 1, buf + 1 + n);
        ll sum = 0;
        for (int i = 1; i <= n; ++i) {
            sum += buf[i].a;
            buf[i].c = max(sum, buf[i - 1].c) + buf[i].b;
        }
        printf("%lld\n", buf[n].c);
    }
    return 0;
}
