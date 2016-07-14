#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>

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
struct point {
	double x, y;
	inline void read() {
		scanf("%lf%lf", &x, &y);
	}
	inline point(double xx = 0.0, double yy = 0.0):x(xx), y(yy) {}
	inline point operator - (const point& T) const {
		return point(x - T.x, y - T.y);
	}
	inline bool operator < (const point& T) const {
		return x < T.x || (x == T.x && y < T.y);
	}
	inline bool operator == (const point& T) const {
		return x == T.x && y == T.y;
	}
};
point a;
std::vector<point> points, res;
inline double cross(const point& a, const point& b) {
	return a.x * b.y - a.y * b.x;
}
inline double dot(const point& a, const point& b) {
	return a.x * b.x + a.y * b.y;
}
inline double dis2(const point& a, const point& b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
int n;
std::vector<point> convexHull(std::vector<point>& p) {
	std::sort(p.begin(), p.end());
	p.erase(std::unique(p.begin(), p.end()), p.end());
	int n = p.size(), m = 0;
	std::vector<point> ch(n + 1);
	f(i, 0, n) {
		while (m > 1 && cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0) --m;
		ch[m++] = p[i];
	}
	int k = m;
	gd(i, n - 2, 0) {
		while (m > k && cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0) --m;
		ch[m++] = p[i];
	}
	if (n > 1) --m;
	ch.resize(m);
	return ch;
}
int sz;
point c[4];
void magic() {
	double ans = 0.0, cur;
	f(i, 0, 10000000) {
//	f(i, 0, 1000000 / ((sz / 10) + 1)) {
		if (clock() > 0.95 * CLOCKS_PER_SEC) break;
		f(j, 0, 4) c[j] = res[rand() % sz];
		std::sort(c, c + 4);
		cur = 0.0;
		f(j, 0, 4) {
			cur += cross(c[j], c[(j + 1) % 4]);
		}
		if (fabs(cur) > ans) ans = fabs(cur);
	}
	printf("%.01lf\n", ans / 2.0);
}
void wisdom() {
	// size of convexHull leq 500
	double ans = 0.0;
	double cur = 0.0;
//	f(i, 0, sz) printf("``%lf %lf\n", res[i].x, res[i].y);
	if (sz < 4) {
		//std::sort(res.begin(), res.end());
		f(i, 0, sz) {
			cur += cross(res[i], res[(i + 1) % sz]);
		}
		printf("%.01lf\n", fabs(cur) / 2.0);
		return;
	}
//	printf("%d\n", sz);
	if (sz <= 100) {
		cur = ans = 0.0;
		f(i, 0, sz) f(j, i + 1, sz) f(k, j + 1, sz) f(l, k + 1, sz) {
			cur = 0;
			cur += cross(res[i], res[j]);
			cur += cross(res[j], res[k]);
			cur += cross(res[k], res[l]);
			cur += cross(res[l], res[i]);
			if (ans < fabs(cur)) ans = fabs(cur);
		}
		printf("%.01lf\n", ans / 2.0);
		return;
	}
	int id;
	double mx;
	f(i, 0, sz) {
		if ((cur = dis2(res[0], res[i])) > mx) {
			mx = cur;
			id = i;
		}
	}
//	printf("= =");
	f(i, 0, sz) {
		while (dis2(res[i], res[id]) < dis2(res[i], res[(id + 1) % sz])) {
			id = (id + 1) % sz;
		}
		f(j, 0, sz) if (j != i && j != id) f(k, 0, sz) if (k != i && k != id && k != j) {
			c[0] = res[i]; c[1] = res[j]; c[2] = res[k]; c[3] = res[id];
//			f(i, 0, 4) printf("%lf %lf ", c[i].x, c[i].y); puts("");
			std::sort(c, c + 4);
			cur = 0.0;
			f(w, 0, 4) {
				cur += cross(c[w], c[(w + 1) % 4]);
			}
	//		printf("%lf\n", fabs(cur));
			if (fabs(cur) > ans) ans = fabs(cur);
		}
	}
	printf("%.01lf\n", ans / 2.0);
}
int main() {
#ifndef LOCAL
	freopen("area.in", "r", stdin);
	freopen("area.out", "w", stdout);
#endif

	scanf("%d", &n);
	f(i, 0, n) {
		a.read();
		points.push_back(a);
	}
	res = convexHull(points);
	sz = res.size();
	if (sz > 500) {
		magic();
		return 0;
	}
	wisdom();

#ifndef LOCAL
	fclose(stdin); fclose(stdout);
#endif
	return 0;
}

