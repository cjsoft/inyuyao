#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef long double LD;
typedef double DB;

const int maxn = 100005;

int n, m;

struct Vector {
	int x, y;

	Vector(int a = 0, int b = 0) {
		x = a; y = b;
	}

	bool operator < (const Vector &a) const {
		return x != a.x ? x < a.x : y < a.y;
	}

	Vector operator - (const Vector &a) {
		return Vector(x - a.x, y - a.y);
	}
} p[maxn], cov[maxn];

inline LL cross(Vector a, Vector b) {
	return (LL)a.x * b.y - (LL)a.y * b.x;
}

inline void Andrew() {
	sort(p + 1, p + 1 + n);
	for(int i = 1, k = 1; i <= n; i++) {
		for(; m > k && cross(cov[m] - cov[m - 1], p[i] - cov[m - 1]) <= 0; m--);
		cov[++m] = p[i];
	}
	for(int i = n - 1, k = m; i; i--) {
		for(; m > k && cross(cov[m] - cov[m - 1], p[i] - cov[m - 1]) <= 0; m--);
		cov[++m] = p[i];
	}
	if(n > 1) m--;
}

int main() {
	freopen("area.in", "r", stdin);
	freopen("area.ans", "w", stdout);
	scanf("%d", &n);
	if(n <= 2) {
		printf("0.0\n");
		return 0;
	}
	for(int i = 1; i <= n; i++) scanf("%d%d", &p[i].x, &p[i].y);

	Andrew();

	if(m == 3) {
		LL ans = cross(cov[2] - cov[1], cov[3] - cov[1]);
		printf("%lld.%d", ans / 2, ans & 1 ? 5 : 0);
		return 0;
	}

	LL ans = 0;
	for(int i = 1, a, b; i <= m; i++) {
		a = i + 1; b = i + 3;
		if(a > m) a -= m;
		if(b > m) b -= m;
		for(int j = i + 2; j <= m; j++) {
			for(; a != j && cross(cov[a + 1] - cov[i], cov[j] - cov[i]) > cross(cov[a] - cov[i], cov[j] - cov[i]); a == m ? a = 1 : a++);
			for(; b != i && cross(cov[j] - cov[i], cov[b + 1] - cov[i]) > cross(cov[j] - cov[i], cov[b] - cov[i]); b == m ? b = 1 : b++);
			ans = max(ans, cross(cov[a] - cov[i], cov[j] - cov[i]) + cross(cov[j] - cov[i], cov[b] - cov[i]));
		}
	}

	printf("%lld.%d", ans / 2, ans & 1 ? 5 : 0);
	return 0;
}

