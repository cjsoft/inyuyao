#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
int n, m;
bool connect[2][307][307][307];
void proceed() {
    for (int p = 0; p < 2; ++p) {
        for (int q = 0; q <= n; ++q) {
            for (int i = 2; i <= n; ++i) {
                for (int j = 0; j < i; ++j) {
                    for (int k = j + 1; k < i; ++k) {
                        connect[p][q][j][i] |= connect[p][q][j][k] && connect[p][q][k][i];
                    }
                }
            }
        }
    }
}
int main() {
    freopen("draw.in", "r", stdin);
    freopen("draw.out", "w", stdout);

    scanf("%d %d", &n, &m);
    int x1, y1, x2, y2;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        if (y1 == y2) {
            for (int j = x1; j < x2; ++j)
                connect[0][y1][j][j + 1] = true;
        } else {
            for (int j = y1; j < y2; ++j)
                connect[1][x1][j][j + 1] = true;
        }
    }
    proceed();
    int s, ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            s = std::min(n - i, n - j);
            for (int k = 1; k <= s; ++k) {
                if (connect[0][j][i][i + k] && connect[0][j + k][i][i + k] &&
                    connect[1][i][j][j + k] && connect[1][i + k][j][j + k])
                    ++ans;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
