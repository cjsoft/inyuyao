#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

typedef long long i64;

const int N = 100000 + 10;

inline i64 nextInt() {
  char ch;
  while (ch = getchar(), ch != '-' && !isdigit(ch)) {}
  bool sig = false;
  if (ch == '-') ch = getchar(), sig = true;
  i64 res = ch - '0';
  while (isdigit(ch = getchar())) res = 10 * res + ch - '0';
  if (sig) res = -res;
  return res;
}

int n, size;
i64 a[N], b[N], sum[N];

bool sig[N], flag[N];
i64 det[N], res[N];

void release(int x) {
  int l = x * size, r = std::min(l + size, n);
  if (sig[x]) {
    for (int i = l; i < r; ++i) a[i] = -a[i];
    sig[x] = false;
  }
  if (det[x]) {
    for (int i = l; i < r; ++i) a[i] += det[x];
    det[x] = 0;
  }
}

void build(int x) {
  flag[x] = false;
  int l = x * size, r = std::min(l + size, n);
  memcpy(b + l, a + l, (r - l) * sizeof(i64));
  std::sort(b + l, b + r);
  sum[l] = b[l];
  for (int i = l + 1; i < r; ++i) sum[i] = sum[i - 1] + b[i];
}

void add(int x, int p, int q, i64 y) {
  int l = x * size, r = std::min(l + size, n);
  if (p <= l && r - 1 <= q) {
    det[x] += y;
    flag[x] = false;
    return;
  }
  release(x);
  for (int i = std::max(l, p); i < r && i <= q; ++i) a[i] += y;
  build(x);
}

void flip(int x, int p, int q) {
  int l = x * size, r = std::min(l + size, n);
  if (p <= l && r - 1 <= q) {
    det[x] = -det[x];
    sig[x] ^= 1;
    return;
  }
  release(x);
  for (int i = std::max(l, p); i < r && i <= q; ++i) a[i] = -a[i];
  build(x);
}

int bSearch(int l, int r, i64 x) {
  if (b[l] >= x) return l;
  if (b[r] < x) return r + 1;
  int res;
  while (l <= r) {
    int mid = (l + r) / 2;
    if (b[mid] >= x) {
      res = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  return res;
}

i64 query(int x, int p, int q) {
  int l = x * size, r = std::min(l + size, n);
  if (p <= l && r - 1 <= q) {
    if (flag[x]) return res[x];
    flag[x] = true;
    if (sig[x]) {
      int p = bSearch(l, r - 1, det[x]);
      i64 u = (p > l ? -sum[p - 1] + (p - l) * det[x] : 0), v = -sum[r - 1] + (r - l) * det[x] - u;
      return res[x] = u - v;
    } else {
      int p = bSearch(l, r - 1, -det[x]);
      i64 u = (p > l ? sum[p - 1] + (p - l) * det[x] : 0), v = sum[r - 1] + (r - l) * det[x] - u;
      return res[x] = v - u;
    }
  }
  i64 res = 0;
  for (int i = std::max(l, p); i < r && i <= q; ++i) res += llabs((sig[x] ? -a[i] : a[i]) + det[x]);
  return res;
}

int main() {
  freopen("seq.in", "r", stdin);
  freopen("seq.out", "w", stdout);
  n = nextInt();
  int m = nextInt();
  for (int i = 0; i < n; ++i) a[i] = nextInt();
  size = .35 * sqrt(n) + .5;
  for (int i = 0; i * size < n; ++i) build(i);
  while (m--) {
    int op = nextInt(), l = nextInt(), r = nextInt();
    if (op == 0) {
      i64 x = nextInt();
      for (int i = l / size, j = r / size; i <= j; ++i) add(i, l, r, x);
    } else if (op == 1) {
      for (int i = l / size, j = r / size; i <= j; ++i) flip(i, l, r);
    } else {
      i64 ans = 0;
      for (int i = l / size, j = r / size; i <= j; ++i) ans += query(i, l, r);
      printf("%lld\n", ans);
    }
  }
  return 0;
}
