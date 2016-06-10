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
int n, m, l, r, opt;
ll a[maxn], x;
// Define Functions :


int main() {
	freopen("seq.in", "r", stdin);
	freopen("seq.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	f(i, 1, n) cin >> a[i];
	while (m--) {
		cin >> opt;
		if (!opt) {
			cin >> l >> r >> x;
			l++, r++;
			f(i, l, r) a[i] += x;
		} else if (opt == 1) {
			cin >> l >> r;
			l++, r++;
			f(i, l, r) a[i] *= -1;
		} else {
			cin >> l >> r;
			l++, r++;
			ll tmp = 0;
			f(i, l, r) tmp += fabs(a[i]);
			cout << tmp << endl;
		}
	}
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
