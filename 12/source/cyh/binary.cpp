#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#define MASK 0xff
typedef int ushort;
ushort f[MASK + 1][MASK + 1];
int cnt[MASK + 1][MASK + 1];
char vis[MASK + 1];
using namespace std;
char op[7];
inline ushort calc(ushort a, ushort b) {
    if (op[0] == 'a') return a & b;
    if (op[0] == 'o') return a | b;
    if (op[0] == 'x') return a ^ b;
}
inline void add(ushort a) {
    ushort seg1 = a >> 8, seg2 = a & MASK;
    vis[seg1] = 1;
    for (ushort i = 0; i <= MASK; ++i) {
        ushort tmp = calc(i, seg2) & MASK;
        if (tmp > f[seg1][i]) {
            f[seg1][i] = tmp;
            cnt[seg1][i] = 1;
        }
        else if (tmp == f[seg1][i]) {
            ++cnt[seg1][i];
        }
    }
}
int ans1, ans2;
inline void ask(ushort a) {
    ushort seg1 = a >> 8, seg2 = a & MASK;
    ans1 = 0;
    ans2 = 0;
    for (ushort i = 0; i <= MASK; ++i) {
        if (vis[i]) {
            int k = calc(i, seg1) << 8 | f[i][seg2];
            if (k > ans1) {
                ans1 = k;
                ans2 = cnt[i][seg2];
            }
            else if (k == ans1) {
                ans2 += cnt[i][seg2];
            }
        }
    }
}
int n, type;
int tmp;
int main() {
    freopen("binary.in", "r", stdin);
    freopen("binary.out", "w", stdout);
    scanf("%d %s %d", &n, op, &type);
    
    scanf("%d", &tmp);
    add(tmp);
    for (int i = 1; i < n; ++i) {
        scanf("%d", &tmp);
        ask(tmp);
        if (type == 1) {
            printf("%d %d\n", ans1, ans2);
        }
        else {
            printf("%d\n", ans1);
        }
        add(tmp);
    }
    return 0;
}