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
int cnt[23];
int n, x;
LL ans;
inline void upd(int x) {
	int c = 0;
	while (x) {
		cnt[c] += x & 1;
		x >>= 1;
		++c;
	}
}
void solve() {
	int c = 0;
	ans = 0LL;
	gd(i, 20, 0) {
	//	printf("%d %d\n", i, cnt[i]);
		g(l, 1, cnt[i]) {
			LL x = 0LL;
			gd(j, i, 0) {
				if (cnt[j]) {
					--cnt[j]; x |= 1LL << j;
				}
			}
			ans += x * x;
		//printf(LLD"??\n", x);
		}
	}				
	printf(LLD"\n", ans);
}
int main() {
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);

//	double st = clock();
	read(n);
	f(i, 0, n) {
		read(x); upd(x);
	}
//	f(i, 0, 20) printf("%d ", cnt[i]); puts("");
	solve();

	return 0;
}


