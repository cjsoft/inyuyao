#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define MXN 2007
#define EPS 1e-7
using namespace std;
struct point {
    double x, y;
    double ang;
    int id;
    point(double a, double b) {
        x = a; y     = b;
    }
    point(double a) {
        ang = a;
        x = cos(a); 
        y = sin(a);
    }
    point() {x = y = ang = 0;}
    bool operator<(const point &b) const {
        return ang < b.ang;
    }
    point operator-(point &b) {
        return point(x - b.x, y - b.y);
    }
    point operator+(point &b) {
        return point(x + b.x, y + b.y);
    }
    double operator*(point b) {
        return x * b.y - b.x * y;
    }
} bufs[MXN << 1 | 1];

double Area(point &a, point &b, point &c) {
    printf("   %f\n", fabs((b - a) * (c - a)));
    return fabs((b - a) * (c - a));
}
double dp[MXN << 1 | 1][MXN << 1 | 1];
int pre[2][MXN][MXN];
int n, K;
const double pi = acos(-1);
int main() {
    scanf("%d %d", &n, &K);
    double tmp;
    for (int i = 1; i <= n; ++i) {
        scanf("%lf", &tmp);
        bufs[i] = point(tmp);
        bufs[i].id = i;
    }
    sort(bufs + 1, bufs + 1 + n);
    int now = 0, last = 1;
    for (int i = 1 + n; i < 1 + n + n; ++i) bufs[i] = bufs[i - n], bufs[i].ang += 2 * pi;
    for (int i = 1; i <= n; ++i) {
        swap(now, last);
        memset(&pre[now][0][0], 0, sizeof(pre[0]));
        memset(dp, 0, sizeof(dp));
        for (int j = i + 2; j <= i + n; ++j) {
            for (int k = 1; k < min(K, j - i); ++k) {
                for (int l = j - 1; l > i; --l) {
                    if (bufs[j].ang - bufs[l].ang >= pi || fabs(bufs[j].ang - bufs[l].ang) < EPS) break;
                    tmp = Area(bufs[i], bufs[j], bufs[l]);
                    if (tmp + dp[l][k - 1] > dp[j][k]) {
                        pre[now][j][k] = l;
                        dp[j][k] = tmp + dp[l][k - 1];
                    }
                }
            }
        }
        double ans = 0;
        for (int j = i + K; j <= i + n; ++j) {
            ans = max(ans, dp[j][K]);
        }
        printf("%f", ans);
    }
    return 0;
}