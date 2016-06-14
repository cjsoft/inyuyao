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

inline void read(int &x) {
	x = 0;
	char c = getchar();
	while (c < '0'|| c > '9') c = getchar();
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
}
int T;
int n;
int a[1003][1003];
int x[1003][1003];
int f[1003];
int ans, s;
bool c = 0;
double ti;
void solve() {
	ans = -1;
	if (n <= 20) {
		f(i, 0, 1 << n) {
			f(j, 0, n) if (i & (1 << j)) f[j] = 1; else f[j] = 0;
			f(j, 0, n) f(k, 0, n) x[j][k] = f[j] ^ f[k];
			s = 0; c = 1;
			f(j, 0, n) if (c) f(k, 0, n) if (!(x[j][k] || !a[j][k])) {
				c = 0; break;
			}
			if (!c) continue;
			f(j, 0, n) f(k, 0, n) if (!(a[j][k] || !x[j][k])) ++s;
			//printf("%d\n", s);
			if (ans == -1 || s > ans) ans = s;
		}
	} else {
		ans = -1;
	}
	printf("%d\n", ans);
}
int main() {
#ifndef LOCAL
	freopen("fxxk.in", "r", stdin);
	freopen("fxxk.out", "w", stdout);
#endif

	scanf("%d", &T);
	ti = CLOCKS_PER_SEC * 1.0 / T;
	while (T--) {
		scanf("%d", &n);
		f(i, 0, n) f(j, 0, n) scanf("%d", &a[i][j]);
		solve();
	}

#ifndef LOCAL
	fclose(stdin);
	fclose(stdout);
#endif
	return 0;
}



