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
const int inf = 0x7fffffff;
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

const int Bk = 100;
const int N = 25 + 3;
double pre[N][N], suf[N][N], ans[N][2];
int l[N], r[N], s[N], p[N], q[N];
int main(){
	freopen("assign.in", "r", stdin);
	freopen("assign.out", "w", stdout);
	int n = rint;
	REP(i, 1, n) l[i] = rint;
	REP(i, 1, n) r[i] = rint;
	int k = rint;
	REP(now, 1, n) REP(cur, l[now], r[now]){
		REP(i, 1, n) 
			if (i == now) s[i] = 1, p[i] = 1, q[i] = 0;
			else s[i] = r[i] - l[i] + 1, p[i] = min(max(r[i] - cur + (i < now), 0), s[i]), q[i] = s[i] - p[i];
		MEM(pre, 0), MEM(suf, 0);
		pre[0][0] = Bk, suf[n + 1][0] = Bk;
		REP(i, 1, n) REP(j, 0, min(i, k - 1)) 
			pre[i][j] = (j ? pre[i - 1][j - 1] * p[i] / s[i] : 0) + pre[i - 1][j] * q[i] / s[i];
		PER(i, n, 1) REP(j, 0, min(n - i + 1, k - 1))
			suf[i][j] = (j ? suf[i + 1][j - 1] * p[i] / s[i] : 0) + suf[i + 1][j] * q[i] / s[i];
		REP(i, 1, n) FOR(j, k){
			int tmp = (j & 3) == 1 || (j & 3) == 2;
			ans[i][tmp] += pre[i - 1][j] * suf[i + 1][k - j - 1] * p[i] / s[i] / (r[now] - l[now] + 1);
		}
	}
	REP(i, 1, n) printf("%.6lf %.6lf\n", ans[i][0] / Bk / Bk, ans[i][1] / Bk / Bk);
}
