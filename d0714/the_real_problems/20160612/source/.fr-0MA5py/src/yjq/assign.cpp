#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 25 + 2, M = 1000 + 10;

int n, th, l[N], r[N];

double ans[N][2];

double calc(int a, int b, int x, int y) {
  b = std::min(b, y);
  a = std::max(a, x);
  if (a > b) return 0.;
  return (b - a + 1.) / (y - x + 1.);
}

void solve(int s, int p) {
  static double f[N][N], g[N][N];
  memset(f, 0, sizeof f);
  f[1][0] = 1.;
  for (int i = 1; i <= n; ++i) {
    double lt = calc(0, s - 1, l[i], r[i]), eq = calc(s, s, l[i], r[i]), gt = calc(s + 1, M, l[i], r[i]);
    if (i <= p) gt += eq; else lt += eq;
    for (int j = 0; j <= i && j <= th; ++j) {
      double cur = f[i][j];
      if (i == p) {
        f[i + 1][j + 1] += f[i][j] * eq;
      } else {
        f[i + 1][j] += cur * lt;
        f[i + 1][j + 1] += cur * gt;
      }
    }
  }
  memset(g, 0, sizeof g);
  g[n][0] = 1.;
  for (int i = n; i > 0; --i) {
    double lt = calc(0, s - 1, l[i], r[i]), eq = calc(s, s, l[i], r[i]), gt = calc(s + 1, M, l[i], r[i]);
    if (i <= p) gt += eq; else lt += eq;
    for (int j = 0; j <= n - i + 1 && j <= th; ++j) {
      double cur = g[i][j];
      if (i == p) {
        g[i - 1][j + 1] += cur * eq;
      } else {
        g[i - 1][j] += cur * lt;
        g[i - 1][j + 1] += cur * gt;
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    double eq = calc(s, s, l[i], r[i]), gt = calc(s + 1, M, l[i], r[i]);
    if (i <= p) gt += eq;
    for (int j = 0; j < i && j < th; ++j) {
      int t = ((j + 1) % 4 > 1);
      double cur = f[i][j] * g[i][th - 1 - j];
      if (i != p) ans[i][t] += cur * gt; else ans[i][t] += cur * eq;
    }
  }
}

int main() {
  freopen("assign.in", "r", stdin);
  freopen("assign.out", "w", stdout);
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", &l[i]);
  for (int i = 1; i <= n; ++i) scanf("%d", &r[i]);
  scanf("%d", &th);
  for (int i = 1; i <= n; ++i)
    for (int j = l[i]; j <= r[i]; ++j)
      solve(j, i);
  for (int i = 1; i <= n; ++i) printf("%.6f %.6f\n", ans[i][0], ans[i][1]);
  return 0;
}
