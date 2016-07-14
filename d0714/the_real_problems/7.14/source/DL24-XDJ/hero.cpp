#include <cstdio>
#include <cstring>
#include <algorithm>

#define f(x, y, z) for (int x = (y), __ = (z); x < __; ++x)
#define g(x, y, z) for (int x = (y), __ = (z); x <= __; ++x)
#define fd(x, y, z) for (int x = (y), __ = (z); x > __; --x)
#define gd(x, y, z) for (int x = (y), __ = (z); x >= __; --x)

typedef long long LL;
typedef long double real;

inline int read() {
	char c = getchar();int x = 0;
	int f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	x *= f;
	return x;
}
int n, m, k;
LL t[303][303];
LL dp[303][303];
LL cur, pre;
LL ans;
const LL oo = 10000000000000LL;
inline void update(LL &x, LL y) {
	if (x > y) x = y;
}
LL s[2][4][303][303];
// 0: up-left
// 1: up-right
// 2: down-left
// 3: down-right
//LL val[4][303][303];
void insert(int id, int x, int y) {
	//int val = dp[x][y];
//	root[id]->modify(x, y);
	s[id][0][x][y] = dp[x][y] + (LL)k * (-x - y);
	s[id][1][x][y] = dp[x][y] + (LL)k * (-x + y);
	s[id][2][x][y] = dp[x][y] + (LL)k * (x - y);
	s[id][3][x][y] = dp[x][y] + (LL)k * (x + y);
}
LL res[4];
LL query(int ti, int i, int j) {
	int id = (ti & 1) ^ 1;
	f(i, 0, 4) res[i] = oo;
	res[0] = s[id][0][i][j] + (LL)k * (i + j);
	if (j < m) res[1] = s[id][1][i][j + 1] + (LL)k * (i - j);
	if (i < m) res[2] = s[id][2][i + 1][j] + (LL)k * (j - i);
	if (i < m && j < m) res[3] = s[id][3][i + 1][j + 1] + (LL)k * (-i - j);
	LL mn = res[0];
	f(i, 1, 4) if (res[i] < mn) mn = res[i];
//	printf("res: %d %d %d: %lld\n", ti, i, j, mn);
	return mn + t[ti][i] + t[ti][j];
//	LL res = oo;
/*
	update(res, root[id]->query(1, 1, i, j, 0));
	update(res, root[id]->query(1, j, i, m, 1));
	update(res, root[id]->query(i, 1, m, j, 2));
	update(res, root[id]->query(i, j, m, m, 3));
	*/
	/*
	f(i, 0, 4) res[i] = oo;
	res[0] = root[id]->query(1, 1, i, j, 0) + k * (i + j);
	if (j < m) res[1] = root[id]->query(1, j + 1, i, m, 1) + k * (i - j);
	if (i < m) res[2] = root[id]->query(i + 1, 1, m, j, 2) + k * (-i + j);
	if (i < m && j < m) res[3] = root[id]->query(i + 1, j + 1, m, m, 3) + k * (-i - j);
	*/
/*
printf("%d %d %d:", id, i, j);
	f(i, 0, 4) printf(" %lld", res[i]);
	puts("");
	*/
	/*
	LL mn = res[0];
	f(i, 1, 4) if (res[i] < mn) mn = res[i];
	return mn + t[ti][i] + t[ti][j];
	*/
}
inline void maintain(int id) {
	f(i, 0, 4) g(a, 0, m) s[id][i][a][a] = oo;
	g(i, 1, m) g(j, 1, m) {
		s[id][0][i][j] = std::min(s[id][0][i][j], s[id][0][i][j - 1]);
	}
	g(j, 1, m) g(i, 1, m) {
		s[id][0][i][j] = std::min(s[id][0][i][j], s[id][0][i - 1][j]);
	}
	g(i, 1, m) gd(j, m, 1) {
		s[id][1][i][j] = std::min(s[id][1][i][j], s[id][1][i][j + 1]);
	}
	gd(j, m, 1) g(i, 1, m) {
		s[id][1][i][j] = std::min(s[id][1][i][j], s[id][1][i - 1][j]);
	}
	gd(i, m, 1) g(j, 1, m) {
		s[id][2][i][j] = std::min(s[id][2][i][j], s[id][2][i][j - 1]);
	}
	g(j, 1, m) gd(i, m, 1) {
		s[id][2][i][j] = std::min(s[id][2][i][j], s[id][2][i + 1][j]);
	}
	gd(i, m, 1) gd(j, m, 1) {
		s[id][3][i][j] = std::min(s[id][3][i][j], s[id][3][i][j + 1]);
	}
	gd(j, m, 1) gd(i, m, 1) {
		s[id][3][i][j] = std::min(s[id][3][i][j], s[id][3][i + 1][j]);
	}
}
int main() {
#ifndef LOCAL
	freopen("hero.in", "r", stdin);
	freopen("hero.out", "w", stdout);
#endif

//	read(n); read(m); read(k);
	n = read(); m = read(); k = read();
	f(i, 0, 2) f(j, 0, 4) g(a, 0, m + 1) g(b, 0, m + 1) s[i][j][a][b] = oo;
//	f(i, 0, 2) root[i] = new node(1, 1, 512, 512);
/*
	f(i, 0, 2) root[i] = new node(1, 1, m, m);
	*/
	g(i, 1, n) g(j, 1, m) t[i][j] = read();
//	g(i, 1, n) g(j, 1, m) read(t[i][j]);
	g(i, 1, m) g(j, 1, m) if (i != j) {
		dp[i][j] = t[1][i] + t[1][j];
		insert(1, i, j);
	}
	/*
	g(i, 1, m) {
		g(j, 1, m) printf("%lld ", s[1][3][i][j]); puts("");
	}
	g(i, 1, m) {
		g(j, 1, m) printf("%lld ", s[1][3][i][j]); puts("");
	}
	puts("");
	*/
	maintain(1);
	/*
	g(i, 1, m) {
		g(j, 1, m) printf("%lld ", dp[i][j]); puts("");
	}
	*/
	ans = oo;
	g(ti, 2, n) {
		cur = 0;
		g(i, 1, m) g(j, 1, m) if (i != j) {
			dp[i][j] = query((ti), i, j);
			if (ti == n) {
				if (ans > dp[i][j]) ans = dp[i][j];
			} else {
				insert(ti & 1, i, j);
			}
		}
/*
		g(i, 1, m) {
			g(j, 1, m) printf("%lld ", dp[i][j]); puts("");
		}
*/
		if (ti != n) {
			maintain(ti & 1);
		/*
			g(i, 1, m) {
				g(j, 1, m) printf("%lld ", s[0][3][i][j]); puts("");
			}
			g(i, 1, m) {
				g(j, 1, m) printf("%lld ", s[0][3][i][j]); puts("");
			}
		*/
		}
	}
	printf("%lld\n", ans);

#ifndef LOCAL
	fclose(stdin); fclose(stdout);
#endif
	return 0;
}

