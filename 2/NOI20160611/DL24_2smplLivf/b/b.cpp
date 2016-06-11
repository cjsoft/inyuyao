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
const int maxn = 3e5 + 7;
// Define Varibles :
int n, m, k;
int a[maxn][4], b[maxn];
int c[maxn];
// Define Functions :
inline bool cmp(const int a, const int b) {return a > b;}
namespace brute {
	inline void solve() {
		fe(i, 0, n) fe(j, 0, n) c[i] += a[j][b[i * j % n]];
		sort(c, c + n, cmp);
		cout << c[k - 1] << endl;
	}
}
int main() {
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
	read(n); read(m); read(k);
	fe(i, 0, n) read(a[i][0]);
	fe(i, 0, n) read(a[i][1]);
	if (m >= 3) fe(i, 0, n) read(a[i][2]);
	if (m >= 4) fe(i, 0, n) read(a[i][3]);
	fe(i, 0, n) read(b[i]);
	brute::solve();
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
