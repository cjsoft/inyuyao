#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

int n, m, a[51];

inline void work() {
	printf("%d %d\n", n, m);
	for (int i = 1; i <= n; i++)
		printf("%d %d %d\n", rand() % 21 - 10, rand() % 2001 - 1000, rand() % 2001 - 1000);
	for (int i = 1; i <= n; i++)
		a[i] = rand() % 201 - 100;
	for (int i = 1; i <= n; i++) {
		int l, r;
		for (;;) {
			l = rand() % 201 - 100;
			r = rand() % 201 - 100;
			if (l > r) swap(l, r);
			if (l <= a[i] && r >= a[i]) break;
		}
		printf("%d %d\n", l, r);
	}
	for (int i = 1; i <= m; i++) {
		int u, v, x;
		for (;;) {
			u = rand() % n + 1;
			v = rand() % n + 1;
			x = rand() % 201 - 100;
			if (u != v && a[u] <= a[v] + x) break;
		}
		printf("%d %d %d\n", u, v, x);
	}
}
 
int main() {
	n = 3; m = 3;
	freopen("maximum0.in", "w", stdout); work();
	n = 3; m = 3;
	freopen("maximum1.in", "w", stdout); work();
	n = 3; m = 6;
	freopen("maximum2.in", "w", stdout); work();
	n = 3; m = 6;
	freopen("maximum3.in", "w", stdout); work();
	n = 3; m = 10;
	freopen("maximum4.in", "w", stdout); work();
	n = 3; m = 10;
	freopen("maximum5.in", "w", stdout); work();
	n = 10; m = 100;
	freopen("maximum6.in", "w", stdout); work();
	n = 10; m = 100;
	freopen("maximum7.in", "w", stdout); work();
	n = 50; m = 100;
	freopen("maximum8.in", "w", stdout); work();
	n = 50; m = 100;
	freopen("maximum9.in", "w", stdout); work();
	n = 50; m = 100;
	freopen("maximum10.in", "w", stdout); work();
	n = 50; m = 100;
	freopen("maximum11.in", "w", stdout); work();
	n = 50; m = 100;
	freopen("maximum12.in", "w", stdout); work();
	n = 50; m = 100;
	freopen("maximum13.in", "w", stdout); work();
	n = 50; m = 100;
	freopen("maximum14.in", "w", stdout); work();
	n = 50; m = 100;
	freopen("maximum15.in", "w", stdout); work();
	n = 50; m = 100;
	freopen("maximum16.in", "w", stdout); work();
	n = 50; m = 100;
	freopen("maximum17.in", "w", stdout); work();
	n = 50; m = 100;
	freopen("maximum18.in", "w", stdout); work();
	n = 50; m = 100;
	freopen("maximum19.in", "w", stdout); work();
}
