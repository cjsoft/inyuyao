#include <bits/stdc++.h>
#define f(x, y, z) for (int x = (y), _end_ = (z); x <= _end_; ++x)
#define g(x, y, z) for (int x = (y), _end_ = (z); x >= _end_; --x)
#define fe(x, y, z) for (int x = (y), _end_ = (z); x < _end_; ++x)
#define ge(x, y, z) for (int x = (y), _end_ = (z); x > _end_; --x)
#define h(x, y) for (int x = head[(y)]; x; x = nxt[x])
#define ms(a, b) memset(a, b, sizeof (a));
#define mp make_pair
#define pb push_back
template <typename Num> void write(Num x);
template <typename Num> void read(Num &x);
using namespace std;
typedef long long ll;
typedef pair <int, int> PII;
const int maxn = 2e5 + 7;
const double eps = 1e-8;
// Varibles :
int n, a[maxn], b[maxn], c[maxn], mrk[maxn];
int size;
bool flag[maxn];
// Functions :
inline void RE(int x);
inline void B(int x);
inline void A(int x, int p, int q, int y);
inline bool J(int x, int l, int r, int k);
// Program :
int main() {
	freopen("kth.in", "r", stdin);
	freopen("kth.out", "w", stdout);
	read(n);
	fe(i, 0, n) read(a[i]);
	memcpy(c, a, sizeof a);
	sort(c, c + n);
	size = sqrt(n) + .5;
	for (int i = 0; i * size < n; ++i) B(i);
	int Q, L, R, X, O;
	read(Q);
	while (Q--) {
		read(O); read(L); read(R); read(X);
		L--, R--;
		if (O == 1) {
			for (int i = L / size, j = R / size; i <= j; ++i) A(i, L, R, X);
		} else {
			int l = 0, r = n - 1;
			for (int i = L / size, j = R / size; i <= j; ++i) RE(i);
			memcpy(c, a, sizeof a);
			sort(c, c + n);
			//cout << "!@#$%^&*()   "; fe(i, 0, n) cout << a[i] << ' '; cout << endl;
			//cout << "!@#$%^&*()   "; fe(i, 0, n) cout << c[i] << ' '; cout << endl;
			while (l <= r) {
				int mid = l + r >> 1;
				if (J(mid, L, R, X)) r = mid - 1;
				else l = mid + 1;
			}
			cout << c[l] << endl;
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}

inline void RE(int x) {
	int l = x * size, r = min(l + size, n);
	if (mrk[x]) {
		fe(i, l, r) a[i] += mrk[x];
		mrk[x] = 0;
	}
}

inline void B(int x) {
	flag[x] = false;
	int l = x * size, r = min(l + size, n);
	memcpy(b + l, a + l, (r - l) * sizeof(int));
	sort(b + l, b + r);
}

inline void A(int x, int p, int q, int y) {
	int l = x * size, r = min(l + size, n);
	if (p <= l && r - 1 <= q) {
		mrk[x] += y;
		flag[x] = false;
		return;
	} RE(x);
	for (int i = max(l, p); i < r && i <= q; ++i) a[i] += y;
	B(x);
}

inline bool J(int x, int l, int r, int k) {
	int a1 = l / size;
	int a2 = r / size;
	int sum = 0;
	if (a1 == a2) {
		for (int i = l; i <= r; i++) if (a[i] <= c[x]) sum++;
		if (sum >= k) return true;
		return false;
	}
	for (int i = a1 + 1; i < a2; i++) {
		sum += upper_bound(b + i * size, b + (i + 1) * size, c[x]) - b - i * size;
	}
	for (int i = l; i < (a1 + 1) * size; i++) if (a[i] <= c[x]) sum++;
	for (int i = a2 * size; i <= r; i++) if (a[i] <= c[x]) sum++;
	if (sum >= k) return true;
	return false;
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
