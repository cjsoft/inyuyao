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

const int Mod = 1e9 + 7;

const int oo = 0x3f3f3f3f;

const int maxn = 5000, maxm = 10000;

struct edge
{
	int id, g, nxt;

	edge() { }
	edge(int _id, int _g, int _nxt): id(_id), g(_g), nxt(_nxt) { }

};

int st[maxn + 5], en = 0;
edge e[(maxm << 1) + 5];

inline void add_edge(int x, int y, int z) { e[en] = edge(y, z, st[x]); st[x] = en++; }

int n, m, T;

int dis[maxn + 5][maxn + 5];

int ans = 0;

inline LL cross(int x0, int y0, int x1, int y1, int x2, int y2)
{
	return (LL)(x1 - x0) * (y2 - y0) - (LL)(x2 - x0) * (y1 - y0);
}

int main()
{
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
	memset(st, -1, sizeof st), en = 0;
	scanf("%d%d%d", &n, &m, &T);
	REP(i, 0, m)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z), --x, --y;
		add_edge(x, y, z), add_edge(y, x, z);
	}
	memset(dis, oo, sizeof dis);
	dis[0][0] = 0;
	REP(i, 0, n) REP(j, 0, n) if (dis[i][j] < oo) for (int k = st[j]; k != -1; k = e[k].nxt)
		chkmin(dis[i + 1][e[k].id], dis[i][j] + e[k].g);
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < n; ++j)
			printf("%d\n", dis[i][j]);
	}
	return 0;
	REP(i, 0, n)
	{
		static int stk[maxn + 5];
		int tot = 0;
		for (int j = n - 1; j >= 0; --j)
		{
			if (dis[j][i] >= oo) continue;
			while (tot > 1)
			{
				if (cross(stk[tot - 2], dis[stk[tot - 2]][i], stk[tot - 1], dis[stk[tot - 1]][i], j, dis[j][i]) < 0) break;
				--tot;
			}
			stk[tot++] = j;
		}
		static int from[maxn + 5];
		from[0] = 0;
		REP(j, 1, tot) from[j] = (dis[stk[j]][i] - dis[stk[j - 1]][i] + stk[j - 1] - stk[j] - 1) / (stk[j - 1] - stk[j]);
		REP(j, 0, tot) chkmax(from[j], 0);
		int to = T + 1;
		for (int j = tot - 1; j >= 0; --j)
		{
			if (from[j] >= to) continue;
			(ans += (LL)(to - from[j]) * (dis[stk[j]][i]) % Mod) %= Mod;
			(ans += ((LL)(from[j] + to - 1) * (to - from[j]) >> 1) % Mod * stk[j]) %= Mod;
			to = from[j];
		}
	}
	(ans += Mod) %= Mod;
	printf("%d\n", int(ans));
	return 0;
}

