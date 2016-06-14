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

FILE *fscore, *freport, *fstd, *fin, *fout;

const int maxn = 18;

int n;
int a[(maxn << 1) + 5][maxn + 5];

bool pick[(maxn << 1) + 5];

bool check()
{
	assert(fscanf(fin, "%d", &n));
	REP(i, 0, n << 1) REP(j, 0, n) assert(fscanf(fin, "%d", a[i] + j));
	memset(pick, 0, sizeof pick);
	int x;
	int lst = 0;
	REP(i, 0, n)
	{
		if (!fscanf(fout, "%d", &x)) return 0;
		if (x <= lst) return 0;
		pick[x - 1] = 1;
		lst = x;
	}
	if (~fscanf(fout, "%d", &x)) return 0;
	static int A[maxn + 5][maxn + 5], B[maxn + 5][maxn + 5];
	int An = 0, Bn = 0;
	REP(i, 0, n << 1)
		if (pick[i]) { REP(j, 0, n) A[An][j] = a[i][j]; ++An; }
		else { REP(j, 0, n) B[Bn][j] = a[i][j]; ++Bn; }
	REP(i, 0, n) REP(j, 0, n) if (A[i][j] != B[j][i]) return 0;
	return 1;
}

int main(int argc,char *argv[])
{
	assert(argc > 6);
	int score = atoi(argv[4]);
	fscore = fopen(argv[5], "w");//得分文件
	freport = fopen(argv[6], "w");//报告文件
	fstd = fopen(argv[3], "r");//标准输出
	fin = fopen(argv[1],"r");//标准输入
	fout = fopen(argv[2], "r");//用户输出
	int tmp = (int)(score * check());
	fprintf(fscore, "%d",tmp);
	return 0;
}
