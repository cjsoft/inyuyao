#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <ctime>

using namespace std;

inline int rd(int x) {
	return rand() % x + 1;
}

int main() {
	freopen("hero.in", "w", stdout);
	srand(time(0));

	int n = rd(50), m = rd(50), k = rd(1000000);
	printf("%d %d %d\n", n, m, k);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) printf("%d ", rd(1000000));
		printf("\n");
	}
	return 0;
}

