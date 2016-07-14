#include <cstdio>
const long long INF = 1ll << 60;
long long f[301][301], a[301][301], K;
int N, M;
int I()
{
	char c = getchar();
	int r = 0;
	while (c < 48 || c > 57)
		c = getchar();
	while (c > 47 && c < 58)
		r = (r << 3) + r + r + c - 48, c = getchar();
	return r;
}
inline void min(long long &x, long long y)
{
	if (y < x)
		x = y;
}
int main()
{
	freopen("hero.in", "r", stdin);
	freopen("hero.out", "w", stdout);
	N = I(), M = I(), K = I();
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			a[i][j] = I();
	for (int i = 1; i <= M; i++)
		for (int j = 1; j <= M; j++)
			f[i][j] = i == j ? INF : a[1][i] + a[1][j];
	for (int i = 2; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			for (int k = 2; k <= M; k++)
				min(f[j][k], f[j][k - 1] + K);
			for (int k = M - 1; k; k--)
				min(f[j][k], f[j][k + 1] + K);
		}
		for (int j = 1; j <= M; j++)
		{
			for (int k = 2; k <= M; k++)
				min(f[k][j], f[k - 1][j] + K);
			for (int k = M - 1; k; k--)
				min(f[k][j], f[k + 1][j] + K);
		}
		for (int j = 1; j <= M; j++)
			for (int k = 1; k <= M; k++)
				f[j][k] = j == k ? INF : f[j][k] + a[i][j] + a[i][k];
	}
	long long O = INF;
	for (int i = 1; i <= M; i++)
		for (int j = 1; j <= M; j++)
			min(O, f[i][j]);
	printf("%lld\n", O);
	return 0;
}
