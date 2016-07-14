#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int N = 5e2 + 10;

typedef long long i64;

struct Dot {
	i64 x, y;
	Dot() {}
	Dot(i64 _x, i64 _y) {
		x = _x, y = _y;
	}
};

inline Dot operator -(const Dot &a, const Dot &b) {
	return Dot(a.x - b.x, a.y - b.y);
}
inline i64 cro(const Dot &a, const Dot &b) {
	return a.x * b.y - a.y * b.x;
}

int n;
Dot a[N], b[N];

inline bool Cmp(const Dot &a, const Dot &b) {
	return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}

Dot q[N];

inline i64 Calc(int n) {
	sort(b + 1, b + n + 1, Cmp);
	int tl = 0;
	for (int i = 1; i <= n; ++i) {
		for (; tl > 1 && cro(q[tl] - q[tl - 1], b[i] - q[tl]) <= 0; --tl);
		q[++tl] = b[i];
	}
	int hd = tl + 1;
	for (int i = n - 1; i; --i) {
		for (; tl >= hd && cro(q[tl] - q[tl - 1], b[i] - q[tl]) <= 0; --tl);
		q[++tl] = b[i];
	}
	i64 sum = 0;
	for (int i = 1; i < tl; ++i)
		sum += cro(q[i], q[i + 1]);
	return max(sum, -sum);
}

int main() {
	freopen("area.in", "r", stdin);
	freopen("area.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%I64d %I64d", &a[i].x, &a[i].y);
	i64 ans = 0;
	for (int i = 1; i <= n; ++i) {
		b[1] = a[i];
		for (int j = i + 1; j <= n; ++j) {
			b[2] = a[j];
			for (int k = j + 1; k <= n; ++k) {
				b[3] = a[k];
				ans = max(ans, Calc(3));
				for (int l = k + 1; l <= n; ++l) {
					b[4] = a[l];
					ans = max(ans, Calc(4));
				}
			}
		}
	}
	printf("%.1f\n", ans / 2.0);

	return 0;
}
