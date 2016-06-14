#pragma optimize GCC("O2")
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
	int f = 1;
	char c = getchar();
	while (c < '0'|| c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	x *= f;
}
int n, q;
int t, l, r, x;
int a[MAXN];
int b[MAXN];
int tag[MAXN];
bool good[MAXN];
int sz;
inline void build(int x) {
	int ll = x * sz, rr = std::min(ll + sz, n);
	memcpy(b + ll, a + ll, (rr - ll) * sizeof(int));
	std::sort(b + ll, b + rr);
	good[x] = 1;
}
inline void release(int x) {
	int ll = x * sz, rr = std::min(ll + sz, n);
	if (tag[x]) f(i, ll, rr) a[i] += tag[x];
	tag[x] = 0;
}
inline void add(int id, int ll, int rr, int v) {
	int l = id * sz, r = std::min(l + sz, n);
	if (ll <= l && r - 1 <= rr) {
		tag[id] += v;
		return;
	}
	release(id);
	for (int i = std::max(l, ll); i < r && i <= rr; ++i) a[i] += v;
	build(id);
}
inline int get(int id, int ll, int rr, int v) {
	int l = id * sz, r = std::min(l + sz, n);
	if (ll <= l && r - 1 <= rr) {
		if (!good[id]) release(id);
//	printf("%d %d %d %d\n", v - tag[id], l, r, std::upper_bound(b + l, b + r, v - tag[id]) - b - l);
		return std::upper_bound(b + l, b + r, v - tag[id]) - b - l;
	}
	release(id);
	int cnt = 0;
	for (int i = std::max(l, ll); i < r && i <= rr; ++i) if (a[i] <= v) ++cnt;
//	good[id] = 0;
//	printf("%d %d %d %d\n", v, l, r, cnt);
	return cnt;
}
inline int check(int l, int r, int v) {
	int cnt = 0;
	g(i, l / sz, r / sz) cnt += get(i, l, r, v);
//	printf("%d %d %d %d\n", l, r, v, cnt);
	return cnt;
}
void query(int l, int r, int x) {
	int lb = -5000000, rb = 5000000, md, ans = 0;
	//while (rb - lb > 1) {
	while (lb <= rb) {
		md = lb + (rb - lb >> 1);
		if (check(l, r, md) >= x) {
	//					rb = md;
			rb = md - 1;
			ans = md;
		} else {
	//			lb = md;
			lb = md + 1;
		}
	}
	printf("%d\n", ans);
	//printf("%d\n", rb);
}
int main() {
#ifndef LOCAL
	freopen("kth.in", "r", stdin);
	freopen("kth.out", "w", stdout);
#endif

	read(n);
	f(i, 0, n) read(a[i]);
	sz = .35 * sqrt(n) + 0.7;
//	printf("%d\n", sz);
	f(i, 0, n / sz) build(i);
	read(q);
	f(i, 0, q) {
		read(t); read(l); read(r); read(x);
		--l; --r;
		if (t == 1) {
			g(i, l / sz, r / sz) add(i, l, r, x);
		} else {
			query(l, r, x);
		}
	}

#ifndef LOCAL
	fclose(stdin);
	fclose(stdout);
#endif
	return 0;
}
/*
4
2 1 1 3
3
2 2 4 2
1 1 3 3
2 1 4 3
*/

