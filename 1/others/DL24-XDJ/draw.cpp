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
typedef std::pair<int, int> PII;
int col[2003][2003];
int row[2003][2003];
inline int get(int *fa, int x) {
	int tee = fa[x], q;
	while (tee != fa[tee]) tee = fa[tee];
	while (x != tee) {
		q = fa[x]; fa[x] = tee; x = q;
	}
	return tee;
}
inline void unite(int *fa, int x, int y) {
	if (rand() & 1) fa[get(fa, x)] = get(fa, y);
	else fa[get(fa, y)] = get(fa, x);
}
inline bool same(int *fa, int x, int y) {
	return get(fa, x) == get(fa, y);
}
struct node {
	PII s, t;
	inline void read() {
		scanf("%d%d%d%d", &s.first, &s.second, &t.first, &t.second);
		if (s > t) std::swap(s, t);
		if (s.second == t.second) {
//			int *cnx = ::cnx[s.second];
//			for (int i = s.first; i <= t.first; i = cnx[i]) {
//				unite(col[s.second], i, s.first);
//			}
			g(i, s.first, t.first) unite(col[s.second], i, s.first);
		} else {
//   		int *rnx = ::rnx[s.first];
//			for (int i = s.second; i <= t.second; i = rnx[i]) {
//				unite(col[s.first], i, s.second);
//			}
			g(i, s.second, t.second) unite(row[s.first], i, s.second);
		}
	}
} a[MAXN];
int ans;
int k, l;
bool b1, b2, b3, b4;
int main() {
#ifndef LOCAL
  freopen("draw.in", "r", stdin);
  freopen("draw.out", "w", stdout);
#endif

	scanf("%d%d", &n, &m);
	g(i, 0, n) g(j, 0, n) {
		row[i][j] = col[i][j] = j;
	}
	f(i, 0, m) {
		a[i].read();
	}
/*
	g(i, 0, n) {
		g(j, 0, n) printf("%d ", get(row[i], j)); puts("");
	}
	puts("");
	g(j, 0, n) {
		g(i, 0, n) printf("%d ", get(col[j], i)); puts("");
	}
*/
	ans = 0;
	g(i, 0, n) g(j, 0, n) {
		 g(step, 1, std::min(n - i, n - j)) {
			k = step + i; l = step + j;
			if (same(row[i], j, l) && same(col[j], i, k)) {
				if (same(row[k], j, l) && same(col[l], i, k)) {
					//printf("```%d %d %d %d, %d\n", i, j, k, l, step);
					++ans;
				}	
			} else break;
		}
	}
	printf("%d\n", ans);

#ifndef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}

/*
5 15
0 1 0 5
1 0 1 5
2 0 2 2
2 3 2 5
3 1 3 2
3 3 3 5
4 0 4 5
5 2 5 5
0 0 5 0
0 1 1 1
2 1 5 1
0 2 5 2
1 3 5 3
0 4 5 4
0 5 3 5
*/
