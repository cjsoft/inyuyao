#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int, int> PII;
#define MP make_pair
#define fi first
#define se second

const int N = 1000;
int a[N][N], n, m, K;
int f[N][N];
int read()
{
	int v = 0;
	char c = getchar();
	while (c < 48 || 57 < c) c = getchar();
	while (48 <= c && c <= 57) v = v * 10 + c - 48, c = getchar();
	return v;
}
int main()
{
	freopen("hero.in", "r", stdin);
	freopen("hero.out", "w", stdout);
	n = read(), m = read(), K = read();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			a[i][j] = read();
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= m; j++)
			f[i][j] = a[1][i] + a[1][j];
	for (int k = 2; k <= n; k++)
	{
		for (int i = 1; i <= m; i++) f[i][i] = 1000000000;
		for (int i = 2; i <= m; i++)
			for (int j = 1; j <= m; j++)
				f[i][j] = min(f[i][j], f[i - 1][j] + K);
		for (int i = m - 1; i >= 1; i--)
			for (int j = 1; j <= m; j++)
				f[i][j] = min(f[i][j], f[i + 1][j] + K);
		for (int i = 1; i <= m; i++)
			for (int j = 2; j <= m; j++)
				f[i][j] = min(f[i][j], f[i][j - 1] + K);
		for (int i = 1; i <= m; i++)
			for (int j = m - 1; j >= 1; j--)
				f[i][j] = min(f[i][j], f[i][j + 1] + K);
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= m; j++)
				f[i][j] += a[k][i] + a[k][j];
	}
	int ans = 1000000000;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= m; j++)
			if (i != j)
				ans = min(ans, f[i][j]);
	printf("%d\n", ans);
}
