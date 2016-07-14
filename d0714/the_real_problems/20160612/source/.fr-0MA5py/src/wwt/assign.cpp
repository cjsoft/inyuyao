#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 30;

double F[MAXN][MAXN][MAXN],G[MAXN][MAXN][MAXN],S[MAXN][MAXN][MAXN],Ch[MAXN][MAXN];
int L[MAXN],R[MAXN],N,K;

double Calc(int i,int j,int l,int r)
{
	i = max(i,l),j = min(j,r);
	if (i > j) return 0;
	return (j - i + 1) / 1.0 / (r - l + 1);
}

int main()
{
	freopen("assign.in","r",stdin),freopen("assign.out","w",stdout);
	scanf("%d", &N);
	for(int i = 1;i <= N;i ++)
		scanf("%d", &L[i]);
	int mx = 0;
	for(int i = 1;i <= N;i ++)
		scanf("%d", &R[i]),mx = max(mx,R[i]);
	scanf("%d", &K);
	for(int src = 0;src <= mx;src ++)
	{
		for(int i = 1;i <= N;i ++)
		{
			for(int a = 0;a < i;a ++)
				for(int b = 0;b < i - a;b ++) F[i][a][b] = 0;
			for(int a = 0;a <= N - i;a ++)
				for(int b = 0;b <= N - i - a;b ++) G[i][a][b] = S[i][a][b] = 0;
		}
		F[1][0][0] = 1;
		for(int i = 1;i <= N;i ++)
		{
			double pr1 = Calc(src + 1,R[i],L[i],R[i]),pr = Calc(src,src,L[i],R[i]);
			for(int a = 0;a < i;a ++)
				for(int b = 0;b < i;b ++)
				{
					F[i + 1][a + 1][b] += F[i][a][b] * pr1;
					F[i + 1][a][b + 1] += F[i][a][b] * pr;
					F[i + 1][a][b] += F[i][a][b] * (1 - pr1 - pr);
				}
		}
		G[N][0][0] = 1,S[N][0][0] = 1;
		for(int i = N;i;i --)
		{
			double pr1 = Calc(src + 1,R[i],L[i],R[i]),pr = Calc(src,src,L[i],R[i]);
			for(int a = 0;a <= N - i;a ++)
				for(int b = N - i;b >= 0;b --)
				{
					G[i - 1][a + 1][b] += G[i][a][b] * pr1;
					G[i - 1][a][b + 1] += G[i][a][b] * pr;
					G[i - 1][a][b] += G[i][a][b] * (1 - pr1 - pr);
					S[i][a][b] = S[i][a][b + 1] + G[i][a][b];
				}
		}
		for(int i = 1;i <= N;i ++)
		{
			double pr1 = Calc(src + 1,R[i],L[i],R[i]),pr = Calc(src,src,L[i],R[i]);
			for(int a = 0;a < i;a ++)
				for(int b = 0;b < i - a;b ++)
					if (F[i][a][b])
						for(int c = 0;c <= N - i && a + c < K;c ++)
						{
							//Type0 i choose pr1
							int least = K - (a + c + 1);
							double cr = F[i][a][b] * pr1 * S[i][c][max(least - b,0)];
							if (least) Ch[i][a + min(b,least)] += cr;
							//Type1 i choose pr
							least = K - (a + c);
							if (least - b <= 0) continue;
							cr = F[i][a][b] * pr * S[i][c][least - b - 1];
							Ch[i][a + b] += cr;
						}
		}
	}
	for(int i = 1;i <= N;i ++)
	{
		for(int j = 0;j < 2;j ++)
		{
			double pr = 0;
			for(int k = 0;k < i;k ++)
				if (j == ((k % 4 == 1 || k % 4 == 2))) pr += Ch[i][k];
			pr += 1e-9;
			printf("%.6f%c", pr, j ? '\n' : ' ');
		}
	}
	return 0;
}
