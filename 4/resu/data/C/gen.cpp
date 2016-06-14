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

const int maxn = 100000;

int n;

int w[maxn + 5], fa[maxn + 5];

int main(int argc, char *argv[])
{
    registerGen(argc, argv, 1);
	n = atoi(argv[1]);
	REP(i, 0, n) w[i] = rnd.next(0, 1);
	w[rnd.next(1, n - 1)] = !w[0];
	vector<int> all;
	REP(i, 0, n >> 1) all.pb(i);
	REP(i, 1, n >> 1) fa[i] = rnd.wnext(0, i - 1, i);
	shuffle(ALL(all));
	REP(i, n >> 1, n) fa[i] = all[rnd.wnext(0, SZ(all) - 1, SZ(all))];
	printf("%d\n", n);
	REP(i, 0, n) printf("%d", w[i]);
	printf("\n");
	REP(i, 1, n) printf("%d\n", fa[i] + 1);
	return 0;
}

