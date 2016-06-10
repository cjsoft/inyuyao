#include <cctype>
#include <cstdio>
#include <algorithm>

const int S = 64 << 20;

char buffer[S], *st = buffer;

inline int nextInt() {
  while (!isdigit(*st)) ++st;
  int res = *st++ - '0';
  while (isdigit(*st)) res = 10 * res + *st++ - '0';
  return res;
}

typedef long long i64;

const int N = 2000 + 10, E = 2 * N;

int n;

int l[N][N], r[N][N], u[N][N], d[N][N];

int bit[N];

inline int query(int p) {
  if (p < 0) return 0;
  int res = 0;
  for (; p; p ^= p & -p) res += bit[p];
  return res;
}

inline void add(int p, int v) {
  for (; p <= n; p += p & -p) bit[p] += v;
}

int que[N], tag[E], next[E], cnt = 2;

inline void link(int a, int b) {
  tag[cnt] = b;
  next[cnt] = que[a];
  que[a] = cnt++;
}

int main() {
  freopen("draw.in", "r", stdin);
  freopen("draw.out", "w", stdout);
  fread(buffer, sizeof(char), S, stdin);
  n = nextInt() + 1;
  for (int m = nextInt(); m--;) {
    int x1 = nextInt() + 1, y1 = nextInt() + 1, x2 = nextInt() + 1, y2 = nextInt() + 1;
    if (x1 == x2) {
      if (y1 > y2) std::swap(y1, y2);
      for (int i = y1; i <= y2; ++i) d[x1][i] = y1, u[x1][i] = y2;
    } else {
      if (x1 > x2) std::swap(x1, x2);
      for (int i = x1; i <= x2; ++i) l[i][y1] = x1, r[i][y1] = x2;
    }
  }
  i64 ans = 0;
  for (int i = -n; i <= n; ++i) {
    cnt = 2;
    for (int j = 1; j <= n; ++j) bit[j] = que[j] = 0;
    for (int x = std::max(1 - i, 1); x <= n; ++x) {
      int y = x + i;
      if (y > n) break;
      if (!r[x][y] || !u[x][y]) continue;
      int det = std::min(r[x][y] - x, u[x][y] - y);
      link(x, x);
      if (x + det + 1 <= n) link(x + det + 1, -x);
    }
    for (int x = std::max(1 - i, 1); x <= n; ++x) {
      int y = x + i;
      if (y > n) break;
      for (int j = que[x]; j; j = next[j]) {
        int k = tag[j];
        if (k > 0) add(k, 1); else add(-k, -1);
      }
      if (!l[x][y] || !d[x][y]) continue;
      int det = std::min(x - l[x][y], y - d[x][y]);
      int t = query(x - 1) - query(x - det - 1);
      ans += t;
    }
  }
  printf("%lld\n", ans);
  return 0;
}
