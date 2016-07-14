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
#define nxt(x) ((x + 1) % n)
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

const int N = 100000 + 5;
int n;
struct Pt{ int x, y; } a[N];
inline Pt operator - (const Pt &a, const Pt &b){ return (Pt){a.x - b.x, a.y - b.y}; }
inline LL operator * (const Pt &a, const Pt &b){ return (LL)a.x * b.y - (LL)a.y * b.x; }
inline LL dis(const Pt &a){ return (LL)a.x * a.x + (LL)a.y * a.y; }
inline bool cmp(const Pt &a, const Pt &b){ return a * b > 0 || a * b == 0 && dis(a) < dis(b); }
void graham(){
	int S = 0;
	FOR(i, n) if (a[i].x < a[S].x || a[i].x == a[S].x && a[i].y > a[S].y) S = i;
	swap(a[0], a[S]);
	ROF(i, n) a[i] = a[i] - a[0];
	sort(a + 1, a + n, cmp);
	int m = 1;
	REP(i, 2, n){
		while (m && (a[i] - a[m - 1]) * (a[m] - a[m - 1]) >= 0) m--;
		a[++m] = a[i];
	}
	n = m;
}
LL calc(int i, int j, int k, int l){return (a[i] * a[j] + a[j] * a[k] + a[k] * a[l] + a[l] * a[i]); }
int main(){
	freopen("area.in", "r", stdin);
	freopen("area.out", "w", stdout);

	n = rint;
	FOR(i, n) a[i] = (Pt){rint, rint};
	graham();
	LL ans = 0;
	if (n == 2) ans = 0; else
	if (n == 3) ans = a[0] * a[1] + a[1] * a[2] + a[2] * a[0]; else{
		int j = 1, k = 2, l = 3, nj = 1, nl = 3;
		FOR(i, n){
			j = nj, l = nl;
			while (nxt(j) != k && calc(i, j, k, l) <= calc(i, nxt(j), k, l)) j = nxt(j);
			while (nxt(l) != i && calc(i, j, k, l) <= calc(i, j, k, nxt(l))) l = nxt(l);
			while (1){
				int nk = nxt(k); nj = j, nl = l;
				while (nxt(j) != nk && calc(i, nj, nk, nl) <= calc(i, nxt(nj), nk, nl)) nj = nxt(nj);
				while (nxt(l) !=  i && calc(i, nj, nk, nl) <= calc(i, nj, nk, nxt(nl))) nl = nxt(nl);
				if (calc(i, j, k, l) <= calc(i, nj, nk, nl)) j = nj, k = nk, l = nl;
				else break;
			}
			cmax(ans, calc(i, j, k, l));
		}
	}
	cout << ans / 2 << '.' << (ans & 1ll ? '5' : '0') << endl;
}
