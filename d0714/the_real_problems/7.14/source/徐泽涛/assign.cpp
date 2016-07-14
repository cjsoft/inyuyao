#include <cstdio>
int N, L[27], R[27], K;
long double H[27][27], T[27][27], O[27][27], M[27], TMP;
inline long double more(int l, int r, int m) // >= m
{
	return m <= l ? 1 : (m > r ? 0 : (long double)(r - m + 1) / (r - l + 1));
}
inline long double less(int l, int r, int m) // <= m
{
	return more(-r, -l, -m);
}
inline int min(int x, int y)
{
	return x < y ? x : y;
}
inline int max(int x, int y)
{
	return x > y ? x : y;
}
int main()
{
	freopen("assign.in", "r", stdin);
	freopen("assign.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", L + i);
	for (int i = 1; i <= N; i++)
		scanf("%d", R + i);
	scanf("%d", &K);
	for (int i = 1; i <= N; i++)
		for (int j = L[i]; j <= R[i]; j++)
		{
			H[0][0] = T[N + 1][0] = 1;
			for (int k = 1; k <= K; k++)
				H[0][k] = T[N + 1][k] = 0;
			for (int k = 1; k < i; k++)
			{
				long double MORE = more(L[k], R[k], j), LESS = less(L[k], R[k], j - 1);
				H[k][0] = H[k - 1][0] * LESS;
				for (int l = 1; l <= K; l++)
					H[k][l] = H[k - 1][l - 1] * MORE + H[k - 1][l] * LESS;
			}
			for (int k = N; k > i; k--)
			{
				long double MORE = more(L[k], R[k], j + 1), LESS = less(L[k], R[k], j);
				T[k][0] = T[k + 1][0] * LESS;
				for (int l = 1; l <= K; l++)
					T[k][l] = T[k + 1][l - 1] * MORE + T[k + 1][l] * LESS;
			}
			if (K >= 2)
			{
				for (int k = 0; k <= K; k++)
					M[k] = T[i + 1][k];
				for (int k = i - 1; k; k--)
				{
					for (int I1 = 0; I1 <= K - 2; I1++)
						O[k][I1] += H[k - 1][I1] * more(L[k], R[k], j) / (R[i] - L[i] + 1) * M[K - 2 - I1];
					long double MORE = more(L[k], R[k], j), LESS = less(L[k], R[k], j - 1);
					for (int l = K; l; l--)
						M[l] = M[l - 1] * MORE + M[l] * LESS;
					M[0] *= LESS;
				}
				for (int k = 0; k <= K; k++)
					M[k] = H[i - 1][k];
				for (int k = i + 1; k <= N; k++)
				{
					for (int I3 = 0; I3 <= K - 2; I3++)
						O[k][K - 1 - I3] += T[k + 1][I3] * more(L[k], R[k], j + 1) / (R[i] - L[i] + 1) * M[K - 2 - I3];
					long double MORE = more(L[k], R[k], j + 1), LESS = less(L[k], R[k], j);
					for (int l = K; l; l--)
						M[l] = M[l - 1] * MORE + M[l] * LESS;
					M[0] *= LESS;
				}
			}
			for (int k = 0; k < K; k++)
				O[i][k] += H[i - 1][k] / (R[i] - L[i] + 1) * T[i + 1][K - k - 1];
		}
	for (int i = 1; i <= N; i++)
	{
		long double O1 = 0, O2 = 0;
		for (int j = 0; j < K; j++)
			((j & 3) == 0 || (j & 3) == 3 ? O1 : O2) += O[i][j];
		printf("%.6Lf %.6Lf\n", O1, O2);
	}
	return 0;
}
