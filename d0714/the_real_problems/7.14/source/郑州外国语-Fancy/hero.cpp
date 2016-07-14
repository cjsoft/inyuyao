#include <iostream>
#include <cstdio>
#include <cmath>
const int N=301;
int n,m,k,g[N];
int min,f[N][N][N];
int main()
{
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&g[j]);
			for(int k=1;k<j;k++)
				f[i][j][k]=g[j]+g[k];
		}
	for(int i=2;i<=n;i++)
	{
		for(int a=1;a<=m;a++)
		{
			for(int b=1;b<a;b++)
			{
				min=0x7fffffff;
				for(int pa=1;pa<=m;pa++)
				{
					for(int pb=1;pb<pa;pb++)
					{
						min=std::min(min,f[i-1][pa][pb]+k*std::min(abs(pa-a)+abs(pb-b),abs(pa-b)+abs(pb-a)));
					}
				}
				f[i][a][b]+=min;
			}
		}
	}
	min=0x7fffffff;
	for(int i=1;i<=m;i++)
		for(int j=1;j<i;j++)
			min=std::min(min,f[n][i][j]);
	printf("%d\n",min);
}
