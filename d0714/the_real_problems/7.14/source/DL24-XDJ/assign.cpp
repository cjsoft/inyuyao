#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>

#define f(x, y, z) for (int x = (y), __ = (z); x < __; ++x)
#define g(x, y, z) for (int x = (y), __ = (z); x <= __; ++x)
#define fd(x, y, z) for (int x = (y), __ = (z); x > __; --x)
#define gd(x, y, z) for (int x = (y), __ = (z); x >= __; --x)

typedef long long LL;
typedef long double real;

inline void read(int &x) {
	char c = getchar(); x = 0;
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
}
const int MAXN = 1e5 + 33;
int n, l[MAXN], r[MAXN], k;
typedef std::pair<int, int> PII;
PII a[MAXN], c[MAXN];
int c1, c2;
int num;
int cnt[MAXN];
inline bool cmp(const PII& a, const PII& b) {
	if (a.first != b.first) return a.first > b.first;
	return a.second < b.second;
}
inline bool cmp1(const PII& a, const PII& b) {
	return a.second < b.second;
}
void get() {
	std::sort(a + 1, a + n + 1, cmp);
	g(i, 1, k) c[i] = a[i];
	std::sort(a + 1, a + n + 1, cmp1);
	std::sort(c + 1, c + k + 1, cmp1);
	++num;
	g(i, 1, k) {
		if (i % 4 == 1 || i % 4 == 0) ++cnt[c[i].second];
	}
}
void dfs(int x) {
	if (x == n + 1) {
		get();
		return;
	}
	g(i, l[x], r[x]) {
		a[x] = PII(i, x);
		dfs(x + 1);
	}
}
int main() {
#ifndef LOCAL
	freopen("assign.in", "r", stdin);
	freopen("assign.out", "w", stdout);
#endif

	read(n);
	g(i, 1, n) read(l[i]);
	g(i, 1, n) read(r[i]);
	read(k);
	dfs(1);
//	g(i, 1, n) printf("%d ", cnt[i]); puts("");
	g(i, 1, n) printf("%.06lf %.06lf\n", double(cnt[i]) / num, 1 - (double)cnt[i] / num);

#ifndef LOCAL
	fclose(stdin); fclose(stdout);
#endif
	return 0;
}

