#include <bits/stdc++.h>
using namespace std;
#define f(x, y, z) for (int x = (y), _end_ = z; x <= _end_; ++x)
#define g(x, y, z) for (int x = (y), _end_ = z; x >= _end_; --x)
#define fe(x, y, z) for (int x = (y), _end_ = z; x < _end_; ++x)
#define ge(x, y, z) for (int x = (y), _end_ = z; x > _end_; --x)
#define ms(a, b) memset(a, b, sizeof (a));
typedef long long ll;
template <typename Num> void write(Num x);
template <typename Num> void read(Num &x);
const int maxn = 1e5 + 7;
// Define Varibles :
int n, m;
double u;
// Define Functions :
inline int getrand() {
	int rtn = rand();
	f(i, 1, 10000) rtn %= rand();
	return rtn;
}

int main() {
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cout.tie(0);
	cin.tie(0);
	srand(int(time(0)));
	cin >> n;
	cout << setiosflags(ios::fixed) << setprecision(8);
	fe(i, 1, n) {
		cout << double(getrand()) * (double(rand()) / 2147483647.0) << endl;
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}

template <typename Num> void read(Num &x) {
	char c; int flag = 1;
	while ((c = getchar()) < '0' || c > '9') if (c == '-') flag *= -1;
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') x *= 10, x += c - '0';
	x *= flag;
}
template <typename Num> void write(Num x) {
	if (x == 0) { putchar('0'); return; }
	static int s[20]; int sl = 0;
	if (x < 0) putchar('-'), x = -x;
	while (x) s[sl++] = x % 10, x /= 10;
	while (sl--) putchar(s[sl] + '0');
}
