#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <climits>
using namespace std;

const int maxn = 100005;
int n;
struct point {
	double x, y;
	point(double _x = 0, double _y = 0) {x = _x, y = _y;};
	point operator - (const point &a) {return point(x - a.x, y - a.y);}
	point operator + (const point &a) {return point(x + a.x, y + a.y);}
	bool operator < (const point &a) const {
		if (x == a.x) return y < a.y;
		return x < a.x;
	}
}p[maxn], sta[maxn];
int top;
double cross(point a, point b) {return a.x * b.y - a.y * b.x;}
double mj(point a1, point a2, point a3, point a4) {
	return abs(cross(a2 - a1, a3 - a1) / 2) + abs(cross(a3 - a1, a4 - a1) / 2);
}
int k1, k2;
double ans;
void solve2(int a, int c) {
	int b, d = c;
	for (b = a + 1; b <= c; b++) {
		while(1) {
			ans = max(ans, mj(sta[a], sta[b], sta[c], sta[d]));
			if (d <= k2 && cross(sta[b] - sta[b + 1], sta[d + 1] - sta[d]) > 0) d++;
			else break;
		}
	}
}

void solve() {
	int a, c = k1;
	for (a = 1; a < k1; a++) {
		while(1) {
			solve2(a, c);
			if (c <= k2 && cross(sta[a] - sta[a + 1], sta[c + 1] - sta[c]) > 0) c++;
			else break;
		}
	}
	printf("%.1lf\n", ans);
}

int main() {
	freopen("area.in", "r", stdin);
	freopen("area.out", "w", stdout);
	scanf("%d", &n);
	if (n <= 2) {
		puts("0");
		return 0;
	}
	for (int i = 1; i <= n; i++) scanf("%lf%lf", &p[i].x, &p[i].y);
	sort(p + 1, p + 1 + n);
	for (int i = 1; i <= n; i++) {
		while(top > 1 && cross(sta[top - 1] - sta[top], sta[top - 1] - p[i]) > 0) top--;
		sta[++top] = p[i];
	}
	k1 = top;
	for (int i = n - 1; i >= 1; i--) {
		while(top > k1 && cross(sta[top - 1] - sta[top], sta[top - 1] - p[i]) > 0) top--;
		sta[++top] = p[i];
	}
	k2 = top;
	sta[++top] = sta[2];
	if (k2 == 4) printf("%.1lf\n", mj(sta[1], sta[2], sta[3], sta[4]));
	else solve();
	return 0;
}
