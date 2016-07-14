#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <climits>
#include <queue>
#include <ctime>
using namespace std;

int main() {
	srand(time(0));
	freopen("hero.in", "w", stdout);
	int n = 300, m = 300, k = 1000000;
	printf("%d %d %d\n", n, m, k);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) printf("%d ", rand() % 10000 + 1);
		printf("\n");
	}
	return 0;
}
