#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long LL;
const int N = 350;
LL f[2][N][N], min1[N], min2[N];
int n, m;
LL t[N][N], K;

void init()
{
	scanf("%d%d%lld", &n, &m, &K);
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= m; ++ j)
			scanf("%lld", &t[i][j]);
}

LL min(LL a, LL b)
{
	return a < b ? a : b;
}

void solve()
{
	int q = 0;
	for (int k = 1; k <= n; ++ k)
	{
		q ^= 1;
		memset(f[q], 60, sizeof(f[q]));
		memset(min1, 60, sizeof(min1));
		memset(min2, 60, sizeof(min2));
		for (int i = 1; i <= m; ++ i)
		{
			for (int j = i + 1; j <= m; ++ j)
			{
				min1[j] = min(min1[j], f[q ^ 1][i][j] - K * (i + j));
				min1[j] = min(min1[j], min1[j - 1]);
				f[q][i][j] = min(f[q][i][j], min1[j] + K * (i + j) + t[k][i] + t[k][j]);
			}
			for (int j = m; j > i; -- j)
			{
				min2[j] = min(min2[j], f[q ^ 1][i][j] + K * (j - i));
				min2[j] = min(min2[j], min2[j + 1]);
				f[q][i][j] = min(f[q][i][j], min2[j] + K * (i - j) + t[k][i] + t[k][j]);
			}
		} 
		memset(min1, 60, sizeof(min1));
		memset(min2, 60, sizeof(min2));
		for (int i = m; i; -- i)
		{
			for (int j = i + 1; j <= m; ++ j)
			{
				min1[j] = min(min1[j], f[q ^ 1][i][j] + K * (i - j));
				min1[j] = min(min1[j], min1[j - 1]);
				f[q][i][j] = min(f[q][i][j], min1[j] + K * (j - i) + t[k][i] + t[k][j]);
			}
			for (int j = m; j > i; -- j)
			{
				min2[j] = min(min2[j], f[q ^ 1][i][j] + K * (i + j));
				min2[j] = min(min2[j], min2[j + 1]);
				f[q][i][j] = min(f[q][i][j], min2[j] - K * (j + i) + t[k][i] + t[k][j]);
			}
		}
	}
	LL ans = f[q][0][0];
	for (int i = 1; i <= m; ++ i)
		for (int j = 1; j <= m; ++ j) if (i != j)
			ans = min(ans, f[q][i][j]);
	printf("%lld", ans);
}

int main()
{
	freopen("hero.in", "r", stdin);
	freopen("hero.out", "w", stdout);
	init();
	solve();
}