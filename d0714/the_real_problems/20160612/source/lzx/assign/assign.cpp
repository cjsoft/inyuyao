#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define zero(x) (fabs(x) < eps)
using namespace std;

const int N = 30;
const double eps = 1e-8;
int l[N], r[N], p[N], que[N], tank[N];
int n, k, Mx;
double ans[2][N], f[22][220], sum[22][220];

void init()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i)
		scanf("%d", &l[i]);
	for (int i = 1; i <= n; ++ i)
		scanf("%d", &r[i]), Mx = max(Mx, r[i]);
	scanf("%d", &k);
}

double calc()
{
	memset(f, 0, sizeof(f));
	f[0][0] = 1;
	for (int i = 0; i <= Mx; ++ i) sum[0][i] = 1;
	for (int i = 1; i <= n; ++ i)
	{
		double cur = 0, len = 1 / double(r[que[i]] - l[que[i]] + 1);
		memset(sum[i], 0, sizeof(sum[i]));
		for (int j = r[que[i]]; j >= l[que[i]]; -- j)
		{
			if (que[i] > que[i - 1])
				f[i][j] = sum[i - 1][j] * len;
			else 
				f[i][j] = sum[i - 1][j + 1] * len;
			sum[i][j] = sum[i][j + 1] + f[i][j];
		}
		for (int j = l[que[i]] - 1; j + 1; -- j)
			sum[i][j] = sum[i][j + 1];
		if (zero(sum[i][l[que[i]]])) return 0;
	}
	return sum[n][l[que[n]]];
}

void dfs(int dep)
{
	if (dep > n)
	{
		double pro = calc();
		for (int i =1 ; i <= k; ++ i)
			tank[i] = que[i];
		sort(tank + 1, tank + 1 + k);
		for (int i = 1; i <= k; ++ i)
		{
			int t = (i % 4) > 1;
			ans[t][tank[i]] += pro;
		}
		return;
	}
	for (int i = 1; i <= n; ++ i) if (!p[i])
	{
		p[i] = 1, que[dep] = i;
		dfs(dep + 1);
		p[i] = 0;
	}
}

void brute1()
{
	dfs(1);
	for (int i = 1; i <= n; ++ i)
	{
		for (int t = 0; t < 2; ++ t)
			printf("%.6f ", ans[t][i]);
		puts("");
	}
}

int main()
{
	freopen("assign.in", "r", stdin);
	freopen("assign.out", "w", stdout);
	init();
	brute1();
	/*else 
		brute2();*/
}