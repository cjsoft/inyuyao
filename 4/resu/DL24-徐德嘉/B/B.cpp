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
#ifndef LOCAL
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif

//	double st = clock();
	read(n);
	f(i, 0, n) {
		read(x); upd(x);
	}
//	f(i, 0, 20) printf("%d ", cnt[i]); puts("");
	solve();
//	double ed = clock();
//	fprintf(stderr, "time: %lf\n", (ed - st) / CLOCKS_PER_SEC);

#ifndef LOCAL
	fclose(stdin);
	fclose(stdout);
#endif
	return 0;
}

/*
100
88 371 267 378 614 432 182 504 597 561 558 340 24 544 615 656 909
566 337 874 495 585 171 41 918 606 478 333 94 832 1011 841 721 387 770
1017 573 370 805 942 872 3 214 179 402 71 834 600 420 269 805 600 486
960 760 255 771 719 556 806 181 262 88 177 265 50 8 1014 354 20 447 936
489 124 672 913 818 80 544 942 990 509 986 443 323 497 326 409 230 360
447 471 264 250 973 689 42 35 930 1006
*/

