#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define min(a,b) (a < b ? a : b)

using namespace std;

const int MAXN = 305;

typedef long long LL;

LL F[2][MAXN][MAXN],Mi[MAXN];
int N,M,K,T[MAXN][MAXN];

int main()
{
	freopen("hero.in","r",stdin),freopen("hero.out","w",stdout);
	scanf("%d%d%d", &N, &M, &K);
	for(int i = 1;i <= N;i ++)
		for(int j = 1;j <= M;j ++)
			scanf("%d", &T[i][j]);
	for(int i = 1;i <= M;i ++)
		for(int j = 1;j <= M;j ++)
			if (i != j) F[1][i][j] = T[1][i] + T[1][j];
	int cr = 0;
	for(int i = 2;i <= N;i ++)
	{
		cr ^= 1;
		//a <= x b <= y
		for(int a = 1;a <= M;a ++)
			for(int b = 1;b <= M;b ++) F[cr ^ 1][a][b] = (1ll << 58);
		for(int b = 1;b <= M;b ++) Mi[b] = (1ll << 58);
		for(int a = 1;a <= M;a ++)
		{
			LL mi = (1ll << 58);
			for(int b = 1;b <= M;b ++)
				if (a != b)
				{
					Mi[b] = min(Mi[b],F[cr][a][b] - (a + b) * K);
					mi = min(mi,Mi[b]);
					LL v = (a + b) * K + mi;
					if (v < F[cr ^ 1][a][b]) F[cr ^ 1][a][b] = v;
				}
		}
		//a <= x b >= y
		for(int b = 1;b <= M;b ++) Mi[b] = (1ll << 58);
		for(int a = 1;a <= M;a ++)
		{
			LL mi = (1ll << 58);
			for(int b = M;b;b --)
				if (a != b)
				{
					Mi[b] = min(Mi[b],F[cr][a][b] - (a - b) * K);
					mi = min(mi,Mi[b]);
					LL v = (a - b) * K + mi;
					if (v < F[cr ^ 1][a][b]) F[cr ^ 1][a][b] = v;
				}
		}
		//a >= x b <= y
		for(int b = 1;b <= M;b ++) Mi[b] = (1ll << 58);
		for(int a = M;a;a --)
		{
			LL mi = (1ll << 58);
			for(int b = 1;b <= M;b ++)
				if (a != b)
				{
					Mi[b] = min(Mi[b],F[cr][a][b] - (b - a) * K);
					mi = min(mi,Mi[b]);
					LL v = (b - a) * K + mi;
					if (v < F[cr ^ 1][a][b]) F[cr ^ 1][a][b] = v;
				}
		}
		//a >= x b >= y
		for(int b = 1;b <= M;b ++) Mi[b] = (1ll << 58);
		for(int a = M;a;a --)
		{
			LL mi = (1ll << 58);
			for(int b = M;b;b --)
				if (a != b)
				{
					Mi[b] = min(Mi[b],F[cr][a][b] - (-b - a) * K);
					mi = min(mi,Mi[b]);
					LL v = (-b - a) * K + mi;
					if (v < F[cr ^ 1][a][b]) F[cr ^ 1][a][b] = v;
				}
		}
		for(int a = 1;a <= M;a ++)
			for(int b = 1;b <= M;b ++)
				if (a != b) F[cr ^ 1][a][b] += T[i][a] + T[i][b];
	}
	cr ^= 1;
	LL ans = (1ll << 60);
	for(int a = 1;a <= M;a ++)
		for(int b = 1;b <= M;b ++)
			if (a != b) ans = min(ans, F[cr][a][b]);
	cout << ans << endl;
	return 0;
}
