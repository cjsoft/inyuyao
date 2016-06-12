#include <bits/stdc++.h>
using namespace std;
#define f(x, y, z) for (int x = (y), _end_ = z; x <= _end_; ++x)
#define g(x, y, z) for (int x = (y), _end_ = z; x >= _end_; --x)
#define fe(x, y, z) for (int x = (y), _end_ = z; x < _end_; ++x)
#define ge(x, y, z) for (int x = (y), _end_ = z; x > _end_; --x)
#define ms(a, b) memset(a, b, sizeof (a));
typedef long long ll;
typedef unsigned long long ull;
template <typename Num> void write(Num x);
template <typename Num> void read(Num &x);
const int maxn = 1e5 + 7;
// Varibles :
map<ll, bool> bits;
int a[70], top = 1;
ull tmp, tmp2;
int ans = 0;
int n;
int tot = 0;
bool flag;
// Functions :
namespace Brute_Force_40 {
	int a[70], top = 1;
	ull tmp;
	int ans = 0;
	bool flag;
	inline void print(ull x) {
		if (!x) return;
		print(x / 2);
		write(x % 2);
	}
	inline void solve() {
		top = 1;
		ms(a, 0);
		ans = 0, tmp = 0;
		int tot = 0;
		while (233) {
			tot++;
			if (bits[tot]) continue;
			flag = true;
			a[1]++;
			f(i, 1, top) {
				a[i + 1] += a[i] >> 1;
				a[i] &= 1;
			}
			if (a[top + 1]) top++;
			tmp = 0;
			g(i, top, 1) tmp = tmp * 10 + a[i];
			f(i, 1, top) {
				if ((tmp & (1 << i - 1)) && a[i]) continue;
				if (((tmp & (1 << i - 1)) == 0) && a[i] == 0) continue;
				else {
					flag = false;
					int tmp = log2(tot);
					f(i, tmp + 1, 25) bits[tot + (1 << i)] = true;
					break;
				}
			}
			if (flag) {
				ans++;
				if (ans == n) {
					print(tot);
					cout << endl;
					return;
				}
			}
		}
	}
}
// Program :
int main() {
	freopen("quiz.in", "r", stdin);
	freopen("quiz.out", "w", stdout);
	cin >> n;
	Brute_Force_40::solve();
	fclose(stdin);
	fclose(stdout);
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
