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
const int maxn = 1e5 + 7;
const double eps = 1e-8;
const ll FLOWER_DANCE = 1e9 + 7;
// Varibles :
int n, m, t, x, y;
ll z;
int tot, to[maxn], nxt[maxn], head[maxn];
ll v[maxn];
queue <int> q;
ll dist[maxn];
bool in[maxn];
int lyf = 0;
// Functions :
inline void add(int f, int t, ll w);
inline void spfa();
// Program :
namespace Brute_Force_Thirty {
	inline void SOLVE() {
		ll ans = 0, tmp = 0;
		spfa();
		tmp = 0;
		f(i, 1, n) ans = (ans + dist[i]) % FLOWER_DANCE;
		f(i, 1, t) {
			f(j, 1, tot) v[j]++;
			spfa();
			f(j, 1, n) ans = (ans + dist[j]) % FLOWER_DANCE;
		}
		cout << ans << endl;
	}
}
namespace Brute_Force_Sixty {
	inline void SOLVE() {
		ll ans = 0;
		ll tmp1 = 0, tmp2 = 0, cha, end;
		ll out = 0;
		spfa();
		f(i, 1, n) {
			ans = (ans + dist[i]) % FLOWER_DANCE;
			out += dist[i];
		}
		f(i, 1, min(200001, t)) {
			f(j, 1, tot) v[j]++;
			spfa();
			out = 0;
			f(j, 1, n) ans = (ans + dist[j]) % FLOWER_DANCE, out += dist[j];
		}
		if (t <= 200001) goto prin;
		spfa();
		f(i, 1, n) tmp2 += dist[i];
		f(i, 1, tot) v[i]--;
		spfa();
		f(i, 1, n) tmp1 += dist[i];
		cha = tmp2 - tmp1;
		tmp2 += cha;
		end = (t - 200002) * cha + tmp2;
		ans += ((tmp2 + end) * (t - 200002 + 1) / 2) % FLOWER_DANCE;
		prin : cout << ans << endl;
		return;
	}
}
int main() {
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
	read(n); read(m); read(t);
	f(i, 1, m) {
		read(x); read(y); read(z);
		add(x, y, z);
		add(y, x, z);
	}
	if (n <= 50 && t <= 1000) Brute_Force_Thirty::SOLVE();
	else if (n <= 50) Brute_Force_Sixty::SOLVE();
	fclose(stdin);
	fclose(stdout);
	return 0;
}

inline void spfa() {
	ms(in, false);
	ms(dist, 0x3f);
	dist[1] = 0;
	in[1] = true;
	q.push(1);
	while (!q.empty()) {
		int now = q.front();
		for (int i = head[now]; i; i = nxt[i]) {
			if (dist[to[i]] > dist[now] + v[i]) {
				dist[to[i]] = dist[now] + v[i];
				if (!in[to[i]]) {
					in[to[i]] = true;
					q.push(to[i]);
				}
			}
		} in[now] = false;
		q.pop();
	}
	return;
}

inline void add(int f, int t, ll w) {
	to[++tot] = t;
	v[tot] = w;
	nxt[tot] = head[f];
	head[f] = tot;
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
