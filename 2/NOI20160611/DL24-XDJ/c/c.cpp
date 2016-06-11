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

int n, m;
double u;
double a[2003][1024];
double res[2033], mn = 1e100;
double cur, c;
double x[2033];
void gauss() {
  int r;
  f(i, 0, m) {
    r = i;
    f(j, i + 1, m) if (fabs(a[j][i]) > fabs(a[r][i])) r = j;
    // if (fabs(a[r][i]) <= EPS) continue;
    if (r != i) g(j, 0, n) std::swap(a[r][j], a[i][j]);
    gd(j, n, i) f(k, i + 1, m) a[k][j] -= a[k][i] / a[i][i] * a[i][j];
  }
  gd(i, m - 1, 0) {
    f(j, i + 1, n) a[i][n] -= a[j][n] * a[i][j];
    a[i][n] /= a[i][i];
  }
}
int main() {
#ifndef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

	scanf("%d%d%lf", &m, &n, &u);
	f(i, 0, m) g(j, 0, n) scanf("%lf", &a[i][j]);
	/*
	double st = clock();
	while (clock() - st <= CLOCKS_PER_SEC * 2.8) {
		f(num, 0, 10) {
			cur = 0;
			f(i, 0, n) x[i] = (((rand() % 400) * (rand() % 400)) % 32000 - 16000) / 8.0;
			f(i, 0, m) {
				c = 0;
				f(j, 0, n) c += map[i][j] * x[j];
				cur += (c - map[i][n]) * (c - map[i][n]);
			}
		}
		if (cur < mn) f(i, 0, n) res[i] = x[i];
	}
	f(i, 0, n) printf("%.012lf\n", res[i]);
	*/
	gauss();
	f(i, 0, n) printf("%.12lf\n", a[i][n]);

#ifndef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}
/*
4 3 3
1 0 0 3
1 1 1 2
1 2 4 4
1 3 9 4
*/

