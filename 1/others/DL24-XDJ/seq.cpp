/**
 * @author SCaffrey(sirius.caffrey@gmail.com)
 * @copyright MIT
 */
#include <cstdio>// NOLINT
#include <cstring>// NOLINT
#include <bits/stdc++.h>// NOLINT
#include <cmath>// NOLINT
#define x1 x11
#define y1 y11

#define f(x, y, z) for (int x = (y), __ = (z); x < __; ++x)
#define g(x, y, z) for (int x = (y), __ = (z); x <= __; ++x)
#define fd(x, y, z) for (int x = (y), __ = (z); x > __; --x)
#define gd(x, y, z) for (int x = (y), __ = (z); x >= __; --x)

#ifdef WIN32
  #define LLD "%I64d"
  #define LLU "%I64u"
#else
  #define LLD "%lld"
  #define LLU "%llu"
#endif

typedef long long LL;// NOLINT
typedef long double real;

const double INF = 1e100;
const int oo = ~0u >> 2;
const double pi = acos(-1.0);
const double EPS = 1e-8;
const int MAXN = 100033;

LL n, m;
LL a[MAXN];
LL s, l, r, x;
int main() {
#ifndef LOCAL
  freopen("seq.in", "r", stdin);
  freopen("seq.out", "w", stdout);
#endif

	scanf(LLD""LLD, &n, &m);
	f(i, 0, n) scanf(LLD, a + i);
	f(i, 0, m) {
		scanf(LLD""LLD""LLD, &s, &l, &r);
		if (s == 0) {
			scanf(LLD"", &x);
			g(j, l, r) a[j] += x;
		} else if (s == 1) {
			g(j, l, r) a[j] *= -1;
		} else if (s == 2) {
			LL sum = 0;
			g(j, l, r) sum += abs(a[j]);
			printf(LLD"\n", sum);
		}
	}

#ifndef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}

/*
4 4
-2 -1 0 1
2 0 3
1 1 3
0 0 1 2
2 0 2
*/

