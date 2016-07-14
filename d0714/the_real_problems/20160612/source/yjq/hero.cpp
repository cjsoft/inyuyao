#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long i64;

const int N = 300 + 10;
const i64 INF = 0x3f3f3f3f3f3f3f3fLL;

inline void check(i64 &lhs, i64 rhs) {
  if (rhs < lhs) lhs = rhs;
}

int n, m, k, t[N][N];
i64 f[N][N], g[N][N];

int main() {
  freopen("hero.in", "r", stdin);
  freopen("hero.out", "w", stdout);
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      scanf("%d", &t[i][j]);
  for (int i = 1; i <= m; ++i) f[i][i] = INF;
  for (int i = 1; i <= n; ++i) {
    memset(g, 0x3f, sizeof g);
    static i64 mem[N][N];
    memset(mem, 0x3f, sizeof mem);
    for (int x = 1; x <= m; ++x)
      for (int y = 1; y <= m; ++y)
        mem[x][y] = std::min(f[x][y] - k * x - k * y, std::min(mem[x - 1][y], mem[x][y - 1]));
    for (int a = 1; a <= m; ++a)
      for (int b = 1; b <= m; ++b)
        check(g[a][b], mem[a][b] + k * a + k * b);
    memset(mem, 0x3f, sizeof mem);
    for (int x = 1; x <= m; ++x)
      for (int y = m; y > 0; --y)
        mem[x][y] = std::min(f[x][y] - k * x + k * y, std::min(mem[x - 1][y], mem[x][y + 1]));
    for (int a = 1; a <= m; ++a)
      for (int b = 1; b <= m; ++b)
        check(g[a][b], mem[a][b] + k * a - k * b);
    memset(mem, 0x3f, sizeof mem);
    for (int x = m; x > 0; --x)
      for (int y = 1; y <= m; ++y)
        mem[x][y] = std::min(f[x][y] + k * x - k * y, std::min(mem[x + 1][y], mem[x][y - 1]));
    for (int a = 1; a <= m; ++a)
      for (int b = 1; b <= m; ++b)
        check(g[a][b], mem[a][b] - k * a + k * b);
    memset(mem, 0x3f, sizeof mem);
    for (int x = m; x > 0; --x)
      for (int y = m; y > 0; --y)
        mem[x][y] = std::min(f[x][y] + k * x + k * y, std::min(mem[x + 1][y], mem[x][y + 1]));
    for (int a = 1; a <= m; ++a)
      for (int b = 1; b <= m; ++b)
        check(g[a][b], mem[a][b] - k * a - k * b);
    for (int a = 1; a <= m; ++a)
      for (int b = 1; b <= m; ++b)
        f[a][b] = g[a][b] + t[i][a] + t[i][b];
    for (int j = 1; j <= m; ++j) f[j][j] = INF;
  }
  i64 ans = INF;
  for (int a = 1; a <= m; ++a)
    for (int b = 1; b <= m; ++b)
      check(ans, f[a][b]);
  printf("%lld\n", ans);
  return 0;
}
