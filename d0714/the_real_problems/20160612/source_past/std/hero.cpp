#include<bits/stdc++.h>
#define FT first
#define SC second
#define PB push_back
#define MP make_pair
#define REP(i, l, r) for(int i = (l); i <= (r); i++)
#define PER(i, r, l) for(int i = (r); i >= (l); i--)
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define ROF(i, n) for(int i = (n) - 1; i >= 0; i--)
#define VEP(i, x) for(int i = 0; i < x.size(); i++)
#define DFOR(i, x) for(int i = hd[x]; i; i = e[i].nxt)
#define MEM(a, b) memset(a, b, sizeof(a))
#define rint read<int>()
#define rll read<LL>()

using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PI;
const int inf = 0x3fffffff;
const int MOD = 1000000007;

template <typename tn>
inline tn read(){
	char ch; tn f = 1;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	tn x = ch - '0';
	while (isdigit(ch = getchar())) x = x * 10 + ch - '0';
	return x * f;
}
template <typename tn> inline void cmax(tn &a, tn b){ if (a < b) a = b; }
template <typename tn> inline void cmin(tn &a, tn b){ if (a > b) a = b; }

struct Data{int ans, i, j; };
const int N = 300 + 5;
int n, m, K, a[N][N], f[N][N];

priority_queue<Data> q;
inline bool operator < (const Data &a, const Data &b){ a.ans > b.ans; }
inline void update(int ans, int i, int j){ if (i < j && i > 0 && j <= m && ans < f[i][j]) q.push((Data){f[i][j] = ans, i, j}); }
	
int main(){
	freopen("hero.in", "r", stdin);
	freopen("hero.out", "w", stdout);

	n = rint, m = rint, K = rint;
	REP(i, 1, n) REP(j, 1, m) a[i][j] = rint;
	MEM(f, 0);
	REP(j, 0, m + 1) REP(k, 0, m + 1) if (j > 0 && k <= m && j < k); else f[j][k] = inf;
	REP(i, 1, n - 1){
		REP(j, 1, m) REP(k, j + 1, m) f[j][k] += a[i][j] + a[i][k];
		REP(j, 1, m) REP(k, j + 1, m) cmin(f[j][k], f[j - 1][k] + K), cmin(f[j][k], f[j][k - 1] + K);
		REP(j, 1, m) PER(k, m, j + 1) cmin(f[j][k], f[j - 1][k] + K), cmin(f[j][k], f[j][k + 1] + K);
		PER(j, m, 1) REP(k, j + 1, m) cmin(f[j][k], f[j + 1][k] + K), cmin(f[j][k], f[j][k - 1] + K);
		PER(j, m, 1) PER(k, m, j + 1) cmin(f[j][k], f[j + 1][k] + K), cmin(f[j][k], f[j][k + 1] + K);
	}
	int ans = inf;
	REP(i, 1, m) REP(j, i + 1, m) cmin(ans, f[i][j] + a[n][i] + a[n][j]);
	cout << ans << endl;
}
