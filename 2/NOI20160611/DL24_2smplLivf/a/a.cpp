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
const int infi = 0x7fffffff;
struct node {
	int ls, rs, cnt;
} tree[(maxn << 4) + (maxn << 2)];
// Varibles :
int cur, rt[maxn], cnt;
int ans1, ans2, ans3, lastans = 0;
int n, m, q;
int a[maxn];
int x, y, k;
int tot, head[maxn], to[maxn << 1], nxt[maxn << 1];
int dep[maxn], fa[maxn], vis[maxn], size[maxn], son[maxn];
int top[maxn], f[maxn], times, w[maxn];
// Functions :
inline void add(int f, int t);
inline void S1(int x, int depth);
inline void S2(int x, int up);
inline int B(int l, int r);
inline int update(int o, int l, int r, int pos, int val);
inline void Q(int a, int b, int com);
inline void ask(int l, int r, int o, int v, int k);
inline void pushup(const int x);
// Program :
int main() {
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	read(n); read(m); read(q);
	f(i, 1, n) read(a[i]);
	fe(i, 1, n) {
		read(x); read(y);
		add(x, y); add(y, x);
	}
	S1(1, 1);
	S2(1, 1);
	cnt = times;
	rt[0] = B(1, cnt);
	f(i, 1, cnt) rt[i] = update(rt[i - 1], 1, cnt, w[i], 1);
	while (q--) {
		read(x); read(y); read(k);
		x ^= lastans, y ^= lastans, k ^= lastans;
		ans1 = ans2 = ans3 = 0;
		Q(x, y, k);
		write(ans1); putchar(' ');
		write(ans2); putchar(' ');
		write(ans3); putchar('\n');
		lastans = ans1 ^ ans2 ^ ans3;
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
inline void ask(int l, int r, int o, int v, int k) {
	if (r < k) {
		ans1 += tree[v].cnt - tree[o].cnt;
		return;
	} else if (l > k) {
		ans3 += tree[v].cnt - tree[o].cnt;
		return;
	} else if (l == r && l == k) {
		ans2 += tree[v].cnt - tree[o].cnt;
		return;
	} else {
		int mid = l + r >> 1;
		ask(l, mid, tree[o].ls, tree[v].ls, k);
		ask(mid + 1, r, tree[o].rs, tree[v].rs, k);
	}
}
inline void Q(int a, int b, int com) {
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) swap(a, b);
		ask(1, cnt, rt[f[top[a]] - 1], rt[f[a]], com);
		a = fa[top[a]];
	}
	if (f[a] > f[b]) swap(a, b);
	ask(1, cnt, rt[f[a] - 1], rt[f[b]], com);
}
inline int update(int o, int l, int r, int pos, int val) {
	int k = cur ++;
	tree[k] = tree[o];
	if (l == r) {
		tree[k].cnt += 1;
		return k;
	}
	int mid = l + r >> 1;
	if (pos <= mid) tree[k].ls = update(tree[o].ls, l, mid, pos, val);
	else tree[k].rs = update(tree[o].rs, mid + 1, r, pos, val);
	pushup(k);
	return k;
}
inline void pushup(const int x) {
	tree[x].cnt = tree[tree[x].ls].cnt + tree[tree[x].rs].cnt;
}
inline int B(int l, int r) {
	int k = cur ++;
	if (l == r) {
		tree[k].cnt = 0;
		return k;
	}
	int mid = l + r >> 1;
	tree[k].ls = B(l, mid);
	tree[k].rs = B(mid + 1, r);
	pushup(k);
	return k;
}
inline void S1(int x, int depth) {
	size[x] = vis[x] = 1;
	dep[x] = depth;
	int maxsize = -1;
	for (int i = head[x]; i; i = nxt[i])
		if (!vis[to[i]]) {
			fa[to[i]] = x;
			S1(to[i], depth + 1);
			size[x] += size[to[i]];
			if (size[to[i]] > maxsize) {
				maxsize = size[to[i]];
				son[x] = to[i];
			}
		}
}
inline void S2(int x, int up) {
	vis[x] = 2;
	top[x] = up;
	w[++times] = a[x];
	f[x] = times;
	if (son[x]) S2(son[x], up);
	for (int i = head[x]; i; i = nxt[i])
		if (vis[to[i]] & 1) S2(to[i], to[i]);
}
inline void add(int f, int t) {
	to[++tot] = t;
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
