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
const int MAXN = 250033;

int n, m, k;
int map[MAXN][4];
int b[MAXN];
int c[MAXN];
void noob() {
	f(i, 0, m) f(j, 0, n) scanf("%d", &map[j][i]);
	f(i, 0, n) scanf("%d", b + i);
	f(i, 0, n) {
		f(j, 0, n) c[i] += map[j][b[i * j % n]];
	}
	std::nth_element(c, c + n - k, c + n);
	printf("%d\n", c[n - k]);
//	f(i, 0, n) printf("%d ", c[i]);
}
void magic() {
	int num = 500;
	f(i, 0, m) f(j, 0, n) scanf("%d", &map[j][i]);
	f(i, 0, n) scanf("%d", b + i);
	f(i, 0, num) {
		int rnd = rand() % n;
		f(j, 0, n) c[i] += map[j][b[rnd * j % n]];
		if (num < k) k = num - 1;
		std::nth_element(c, c + num - k, c + num);
	}
	printf("%d\n", c[num - k]);
}
int main() {
#ifndef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

	scanf("%d%d%d", &n, &m, &k);
	if (n <= 65521) {
	  noob();
		return 0;
	}
	magic();

#ifndef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}
/*
5 3 4
3 2 7 6 8
6 5 5 3 6
1 3 1 0 7
0 1 2 1 0
*/

