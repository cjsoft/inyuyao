#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <algorithm>

typedef long long i64;

const int N = 200000 + 10;

int n;

struct Point {
  int x, y;
  Point() {}
  Point(int _x, int _y): x(_x), y(_y) {}
  inline bool operator< (const Point &rhs) const {
    return x < rhs.x || (x == rhs.x && y < rhs.y);
  }
} point[N];

inline i64 cross(const Point &o, const Point &a, const Point &b) {
  return ((i64)a.x - o.x) * (b.y - o.y) - ((i64)a.y - o.y) * (b.x - o.x);
}

void build() {
  static Point inf[N], sup[N];
  int a = 0, b = 0;
  std::sort(point + 1, point + n + 1);
  for (int i = 1; i <= n; ++i) {
    while (a > 1 && cross(inf[a - 1], inf[a], point[i]) <= 0) --a;
    while (b > 1 && cross(sup[b - 1], sup[b], point[i]) >= 0) --b;
    inf[++a] = sup[++b] = point[i];
  }
  n = 0;
  for (int i = 1; i <= a; ++i) point[++n] = inf[i];
  for (int i = b - 1; i > 1; --i) point[++n] = sup[i];
}

Point range[N];

i64 ternary(int a, int b, int l, int r) {
  i64 res = 0;
  while (r - l > 10) {
    int p = l + (r - l) / 3, q = p + (r - l) / 3;
    if (llabs(cross(point[a], point[b], point[p])) > llabs(cross(point[a], point[b], point[q]))) r = q; else l = p;
  }
  for (int i = l; i <= r; ++i) res = std::max(res, llabs(cross(point[a], point[b], point[i])));
  return res;
}

inline i64 calc(int a, int b) { return ternary(a, b, a + 1, b - 1) + ternary(a, b, b + 1, a + n - 1); }

i64 ans = 0;

void solve(int l, int r) {
  if (l > r) return;
  int mid = (l + r) / 2;
  int cur = range[mid].x;
  i64 val = calc(mid, cur);
  for (int i = range[mid].x + 1; i <= range[mid].y; ++i) {
    i64 temp = calc(mid, i);
    if (temp > val) cur = i, val = temp;
  }
  ans = std::max(ans, val);
  for (int i = l; i < mid; ++i) range[i].y = std::min(range[i].y, cur);
  for (int i = r; i > mid; --i) range[i].x = std::max(range[i].x, cur);
  solve(l, mid - 1);
  solve(mid + 1, r);
}

int main() {
  freopen("area.in", "r", stdin);
  freopen("area.out", "w", stdout);
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d%d", &point[i].x, &point[i].y);
  build();
  for (int i = 1; i <= n; ++i) point[i + n] = point[i], range[i] = Point(i + 1, i + n - 1);
  solve(1, n);
  printf("%lld.%d\n", ans / 2, (ans & 1) ? 5 : 0);
  //    std::cout << std::fixed << std::setprecision(1) << ans / 2.L << std::endl;
  return 0;
}
