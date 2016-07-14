#include <cstdio>
#include <algorithm>
using namespace std;

int read()
{
	int v = 0;
	char c = getchar();
	while (c < 48 || 57 < c) c = getchar();
	while (48 <= c && c <= 57) v = v * 10 + c - 48, c = getchar();
	return v;
}

const int N = 1000;
int A[N], B[N], C[N], l[N], r[N], n, K;
double p[N], ans[N][2];
void dfs(int u, int v, double s)
{
	if (u > n)
	{
		if (A[0] < K && A[0] + B[0] >= K)
		{
			int i = 1, j = 1;
			C[0] = 0;
			while (i <= A[0] && j <= K - A[0])
				if (A[i] < B[j])
					C[++C[0]] = A[i++];
				else
					C[++C[0]] = B[j++];
			while (i <= A[0])
				C[++C[0]] = A[i++];
			while (j <= K - A[0])
				C[++C[0]] = B[j++];
			for (int i = 1; i <= C[0]; i++)
				if (i % 4 == 0 || i % 4 == 1)
					ans[C[i]][0] += s;
				else
					ans[C[i]][1] += s;
		}
		return ;
	}
	if (v < l[u])
	{
		if (A[0] + 1 < K)
		{
			A[++A[0]] = u;
			dfs(u + 1, v, s);
			A[0]--;
		}
	}
	if (v > r[u])
		dfs(u + 1, v, s);
	if (l[u] <= v && v <= r[u])
	{
		B[++B[0]] = u;
		dfs(u + 1, v, s * p[u]);
		B[0]--;
		if (l[u] < v)
			dfs(u + 1, v, s * p[u] * (double) (v - l[u]));
		if (v < r[u])
		{
			if (A[0] + 1 < K)
			{
				A[++A[0]] = u;
				dfs(u + 1, v, s * p[u] * (double) (r[u] - v));
				A[0]--;
			}
		}
	}
}
int main()
{
	freopen("assign.in", "r", stdin);
	freopen("assign.out", "w", stdout);
	n = read();
	for (int i = 1; i <= n; i++) l[i] = read();
	for (int i = 1; i <= n; i++) r[i] = read();
	for (int i = 1; i <= n; i++) p[i] = (double) 1 / (double) (r[i] - l[i] + 1);
	K = read();
	for (int i = 0; i <= 200; i++)
		dfs(1, i, 1);
	for (int i = 1; i <= n; i++)
		printf("%.6lf %.6lf\n", ans[i][0], ans[i][1]);
}
