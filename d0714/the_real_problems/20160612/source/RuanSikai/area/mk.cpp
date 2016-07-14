#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <ctime>

using namespace std;

typedef long long LL;

inline int rd(int x) {
	return rand() % x + 1;
}

int main() {
	freopen("area.in", "w", stdout);
	srand(time(0));
/*	int n = 10000;
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) printf("%d %d\n", rand(), rand());
*/

	int n = 400;
	printf("%d\n", n);
	int x = 100000, y = 100000;
	for(int i = 1; i <= n / 4; i++) printf("%d %d\n", x, y), x += rd(10), y -= rd(10);
	for(int i = 1; i <= n / 4; i++) printf("%d %d\n", x, y), x += rd(10), y += rd(10);
	for(int i = 1; i <= n / 4; i++) printf("%d %d\n", x, y), x -= rd(10), y += rd(10);
	for(int i = 1; i <= n / 4; i++) printf("%d %d\n", x, y), x -= rd(10), y -= rd(10);

	return 0;
}

