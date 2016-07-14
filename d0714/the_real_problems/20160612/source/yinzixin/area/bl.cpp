#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <climits>
using namespace std;

struct point {
	double x, y;
	point(double _x = 0, double _y = 0) {x = _x, y = _y;};
	point operator - (const point &a) {return point(x - a.x, y - a.y);}
	point operator + (const point &a) {return point(x + a.x, y + a.y);}
	bool operator < (const point &a) const {
		if (x == a.x) return y < a.y;
		return x < a.x;
	}
}p[maxn];
double cross(point a, point b) {return a.x * b.y - a.y * b.x;}
double mj(point a1, point a2, point a3, point a4) {
	return abs(cross(a2 - a1, a3 - a1) / 2) + abs(cross(a3 - a1, a4 - a1) / 2);
}

void solve(point a1, point a2, point a3, point a4) {
	

int n;
double ans;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++)
			for (int k = j; k <= n; k++)
				for (int s = k; s <= n; s++) 
					ans = max(ans, solve(p[i], p[j], p[k], p[s]));
	printf("%.1lf\n", ans);
	return 0;
}
