#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), _end_ = (b); i < _end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

#ifdef __WIN32
#define LLFORMAT "I64"
#define Rand() ((rand() << 15) | rand())
#else
#define LLFORMAT "ll"
#define Rand() (rand())
#endif

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

inline int fpm(LL b, int e, int m)
{
	b %= m;
	LL t = 1;
	for ( ; e; e >>= 1, (b *= b) %= m)
		if (e & 1) (t *= b) %= m;
	return t;
}

const int Mod = 1e9 + 7;

const int oo = 0x3f3f3f3f;

const int maxn = 100000;

int n;

int w[maxn + 5];

int fa[maxn + 5];

int val[maxn + 5][2];

int sum_down[maxn + 5], sum[maxn + 5];
int sz[maxn + 5];

vector<int> children[maxn + 5];

struct data
{
	int x, y, z;

	data() { }
	data(int _z): x(0), y(0), z(_z) { }
	data(int _x, int _y, int _z): x(_x), y(_y), z(_z) { }

	friend data operator+(const data &x, const data &y) { return data((x.x + y.x) % Mod, (x.y + y.y) % Mod, (x.z + y.z) % Mod); }
	friend data operator-(const data &x, const data &y) { return data((x.x - y.x) % Mod, (x.y - y.y) % Mod, (x.z - y.z) % Mod); }
	friend data operator*(const data &x, const int &y) { return data((LL)x.x * y % Mod, (LL)x.y * y % Mod, (LL)x.z * y % Mod); }

};

int inv[maxn + 5];

inline void calc()
{
	REP(i, 1, n + 1) inv[i] = fpm(i, Mod - 2, Mod);
	static data coe[maxn + 5][2];
	coe[0][0] = coe[0][1] = coe[n][0] = coe[n][1] = data(0, 0, 0);
	coe[1][0] = data(1, 0, 0), coe[1][1] = data(0, 1, 0);
	REP(i, 1, n - 1)
	{
		coe[i + 1][1] = (coe[i][1] - data((i != 1) * inv[n]) - coe[i - 1][1] * ((LL)(i - 1) * inv[n] % Mod) - coe[i - 1][0] * inv[n]) * ((LL)n * inv[n - i] % Mod);
		coe[i + 1][0] = (coe[i][0] - data(inv[n]) - coe[i + 1][1] * inv[n] - coe[i - 1][0] * ((LL)i * inv[n] % Mod)) * ((LL)n * inv[n - i - 1] % Mod);
	}
	data val0 = coe[n - 1][0] - coe[n - 2][0] * ((LL)(n - 1) * inv[n] % Mod);
	data val1 = coe[n - 1][1] - inv[n] - coe[n - 2][1] * ((LL)(n - 2) * inv[n] % Mod) - coe[n - 2][0] * inv[n];
	int det = ((LL)val0.x * val1.y - (LL)val0.y * val1.x) % Mod;
	assert(det);
	det = fpm(det, Mod - 2, Mod);
	int valx = ((LL)-val0.z * val1.y - (LL)val0.y * -val1.z) % Mod * det % Mod;
	int valy = ((LL)val0.x * -val1.z - (LL)-val0.z * val1.x) % Mod * det % Mod;
	REP(i, 0, n + 1) REP(j, 0, 2) val[i][j] = ((LL)valx * coe[i][j].x + (LL)valy * coe[i][j].y + coe[i][j].z) % Mod;
	REP(i, 0, n + 1) REP(j, 0, 2) (val[i][j] += Mod) %= Mod;
}

int main()
{
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
	scanf("%d", &n);
	calc();
	static char s[maxn + 5];
	scanf("%s", s);
	int cnt = 0;
	REP(i, 0, n) w[i] = s[i] == '1', cnt += w[i];
	fa[0] = -1;
	REP(i, 1, n) scanf("%d", fa + i), --fa[i], children[fa[i]].pb(i);
	for (int i = n - 1; i >= 0; --i) 
	{
		++sz[i], sz[fa[i]] += sz[i];
		REP(k, 0, SZ(children[i]))
		{
			int j = children[i][k];
			(sum_down[i] += sum_down[j] + sz[j]) %= Mod;
		}
	}
	memcpy(sum, sum_down, sizeof sum);
	REP(i, 0, n)
		REP(k, 0, SZ(children[i]))
		{
			int j = children[i][k];
			(sum[j] += (sum[i] - sum_down[j] + n - (sz[j] << 1)) % Mod) %= Mod;
		}
	int ans = 0;
	REP(i, 0, n) (ans += sum[i]) %= Mod;
	ans = (LL)ans * fpm(n, Mod - 2, Mod) % Mod;
	REP(i, 0, n) (ans += (LL)val[cnt][w[i]] * sum[i] % Mod) %= Mod;
	ans = (LL)ans * fpm(n, Mod - 2, Mod) % Mod;
	(ans += Mod) %= Mod;
	printf("%d\n", ans);
	return 0;
}

