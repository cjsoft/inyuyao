#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 305
using namespace std;
int a[N][N],dp[N][N],f1[N][N],f2[N][N],f3[N][N],f4[N][N];
int i,j,n,m,K,k,ans,inf;
int main()
{
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	scanf("%d%d%d",&n,&m,&K);
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	inf=1e9;
	for (i=1;i<=m;i++)
		for (j=1;j<=m;j++)
			if (i!=j)dp[i][j]=a[1][i]+a[1][j];
				else dp[i][j]=inf;
	for (i=1;i<=m;i++)f4[0][i]=inf;
	for (i=1;i<=m;i++)
	{
		f4[i][0]=inf;
		for (j=1;j<=m;j++)
			f4[i][j]=min(f4[i-1][j],min(f4[i][j-1],dp[i][j]-i*K-j*K));
	}
	for (i=1;i<=m;i++)f3[0][i]=inf;
	for (i=1;i<=m;i++)
	{
		f3[i][m+1]=inf;
		for (j=m;j;j--)
			f3[i][j]=min(f3[i-1][j],min(f3[i][j+1],dp[i][j]-i*K+j*K));
	}
	for (i=1;i<=m;i++)f2[m+1][i]=inf;
	for (i=m;i;i--)
	{
		f2[i][0]=inf;
		for (j=1;j<=m;j++)
			f2[i][j]=min(f2[i+1][j],min(f2[i][j-1],dp[i][j]+i*K-j*K));
	}
	for (i=1;i<=m;i++)f1[m+1][i]=inf;
	for (i=m;i;i--)
	{
		f1[i][m+1]=inf;
		for (j=m;j;j--)
			f1[i][j]=min(f1[i+1][j],min(f1[i][j+1],dp[i][j]+i*K+j*K));
	}
	//printf("?%d\n",f1[1][2]);
	/*for (i=1;i<=m;i++)
	{
		for (j=1;j<=m;j++)
			printf("%d ",dp[i][j]);
		puts("");
	}*/
	for (k=2;k<=n;k++)
	{
		//printf("? %d\n",f4[1][2]);
		for (i=1;i<=m;i++)
			for (j=1;j<=m;j++)
				if (i!=j)
				{
					dp[i][j]=f1[i][j]-i*K-j*K;
					dp[i][j]=min(dp[i][j],f2[i][j]-i*K+j*K);
					dp[i][j]=min(dp[i][j],f3[i][j]+i*K-j*K);
					dp[i][j]=min(dp[i][j],f4[i][j]+i*K+j*K);
					dp[i][j]+=a[k][i]+a[k][j];
				}else dp[i][j]=inf;
	/*for (i=1;i<=m;i++)
	{
		for (j=1;j<=m;j++)
			printf("%d ",dp[i][j]);
		puts("");
	}*/
		for (i=1;i<=m;i++)f4[0][i]=inf;
		for (i=1;i<=m;i++)
		{
			f4[i][0]=inf;
			for (j=1;j<=m;j++)
				f4[i][j]=min(f4[i-1][j],min(f4[i][j-1],dp[i][j]-i*K-j*K));
		}
		for (i=1;i<=m;i++)f3[0][i]=inf;
		for (i=1;i<=m;i++)
		{
			f3[i][m+1]=inf;
			for (j=m;j;j--)
				f3[i][j]=min(f3[i-1][j],min(f3[i][j+1],dp[i][j]-i*K+j*K));
		}
		for (i=1;i<=m;i++)f2[m+1][i]=inf;
		for (i=m;i;i--)
		{
			f2[i][0]=inf;
			for (j=1;j<=m;j++)
				f2[i][j]=min(f2[i+1][j],min(f2[i][j-1],dp[i][j]+i*K-j*K));
		}
		for (i=1;i<=m;i++)f1[m+1][i]=inf;
		for (i=m;i;i--)
		{
			f1[i][m+1]=inf;
			for (j=m;j;j--)
				f1[i][j]=min(f1[i+1][j],min(f1[i][j+1],dp[i][j]+i*K+j*K));
		}
	}
	ans=inf;
	for (i=1;i<=m;i++)
		for (j=1;j<=m;j++)
			ans=min(ans,dp[i][j]);
	printf("%d\n",ans);
}