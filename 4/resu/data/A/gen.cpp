#include "testlib.h"
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

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

const int maxabs = 400000;
const int maxn = 2500;

int n, m, T, tmp;

set<pair<int, int> > all;
vector<pair<pair<int, int>, int> > ed;

inline bool add(int x, int y, int z)
{
	if (x == y) return 0;
	if (z < 1 || z > maxabs) return 0;
	if (x > y) swap(x, y);
	if (all.count(mp(x, y))) return 0;
	all.insert(mp(x, y));
	ed.pb(mp(mp(x, y), z));
	--m;
	return 1;
}

inline int get(int x)
{
	return x * x + (rnd.next(0, 1) ? -1 : 1) * (rnd.wnext(x * x, -x));
}

int main(int argc, char *argv[])
{
    registerGen(argc, argv, 1);
	n = atoi(argv[1]), m = atoi(argv[2]), T = atoi(argv[3]), tmp = int(atoi(argv[4]));
	assert(m >= n - 1 && m <= (n * (n - 1) >> 1));
	static int P[maxn + 5];
	REP(i, 0, n) P[i] = i + 1;
	shuffle(P + 1, P + n);
	all.clear();
	REP(i, 1, n) 
	{
		int p = rnd.wnext(0, i - 1, i);
		assert(add(p, i, get(i - p) + tmp));
	}
	while (m)
	{
		int l = rnd.next(0, n - 1), r = rnd.next(0, n - 1);
		if (l == r) continue;
		if (l > r) swap(l, r);
		add(l, r, get(r - l) + tmp);
	}
	shuffle(ALL(ed));
	REP(i, 0, SZ(ed)) if (rnd.next(0, 1)) swap(ed[i].x.x, ed[i].x.y);
	printf("%d %d %d\n", n, SZ(ed), T);
	REP(i, 0, SZ(ed)) printf("%d %d %d\n", P[ed[i].x.x], P[ed[i].x.y], ed[i].y);
	return 0;
}

