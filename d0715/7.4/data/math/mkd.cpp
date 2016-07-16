#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

int n, k, p;

inline void work() {
	printf("%d %d\n", n, k);
	for (int i = 1; i <= n; i++) printf("%d ", rand() * rand() % p + 1);
	printf("\n");
}

int main() {
	n = 10; k = 2; p = 10;
	freopen("math0.in", "w", stdout); work();
	n = 10; k = 3; p = 10;
	freopen("math1.in", "w", stdout); work();
	n = 100; k = 10; p = 100;
	freopen("math2.in", "w", stdout); work();
	n = 500; k = 20; p = 1000;
	freopen("math3.in", "w", stdout); work();
	n = 1000; k = 30; p = 100000;
	freopen("math4.in", "w", stdout); work();
	n = 1000; k = 50; p = 100000;
	freopen("math5.in", "w", stdout); work();
	n = 10000; k = 50; p = 100000;
	freopen("math6.in", "w", stdout); work();
	n = 10000; k = 50; p = 100000;
	freopen("math7.in", "w", stdout); work();
	n = 100000; k = 50; p = 100000;
	freopen("math8.in", "w", stdout); work();
	n = 100000; k = 50; p = 100000;
	freopen("math9.in", "w", stdout); work();
	n = 200000; k = 50; p = 100000;
	freopen("math10.in", "w", stdout); work();
	n = 200000; k = 50; p = 100000;
	freopen("math11.in", "w", stdout); work();
	n = 200000; k = 50; p = 100000;
	freopen("math12.in", "w", stdout); work();
	n = 200000; k = 50; p = 100000;
	freopen("math13.in", "w", stdout); work();
	n = 200000; k = 50; p = 100000;
	freopen("math14.in", "w", stdout); work();
	n = 200000; k = 50; p = 100000;
	freopen("math15.in", "w", stdout); work();
	n = 200000; k = 50; p = 100000;
	freopen("math16.in", "w", stdout); work();
	n = 200000; k = 50; p = 100000;
	freopen("math17.in", "w", stdout); work();
	n = 200000; k = 50; p = 100000;
	freopen("math18.in", "w", stdout); work();
	n = 200000; k = 50; p = 100000;
	freopen("math19.in", "w", stdout); work();
}

