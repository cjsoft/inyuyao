#include <stdio.h>
#include <iostream>
#include <cstring>
const int N=305;
const int inf=1<<30;
int n,m,cost,val[N][N];
int f[N][N][N];
int pre[N][N];
using namespace std;

inline int min(int x,int y){return x<y?x:y;}
int main()
{
	freopen ("hero.in","r",stdin);
	freopen ("hero.out","w",stdout);
	scanf ("%d %d %d",&m,&n,&cost);
	int i,j,a,b,x,y;
	for (i=1;i<=m;i++)
	for (j=1;j<=n;j++)
	scanf ("%d",&val[i][j]);
	for (i=1;i<=n;i++)
	for (j=i+1;j<=n;j++)
	f[1][i][j]=val[1][i]+val[1][j];
	for (i=1;i<=n;i++) pre[0][i]=pre[i][i]=pre[i][n+1]=inf;
	for (i=2;i<=m;i++)
	{
		for (a=1;a<=n;a++)
		for (b=a+1;b<=n;b++)
		pre[a][b]=min(min(pre[a][b-1],pre[a-1][b]),f[i-1][a][b]-cost*(a+b));
		for (a=1;a<=n;a++)
		for (b=a+1;b<=n;b++)
		f[i][a][b]=pre[a][b]+cost*(a+b);
		
		for (a=n;a>=1;a--)
		for (b=n;b>=a+1;b--)
		pre[a][b]=min(min(pre[a][b+1],pre[a+1][b]),f[i-1][a][b]+cost*(a+b));
		for (a=1;a<=n;a++)
		for (b=a+1;b<=n;b++)
		f[i][a][b]=min(f[i][a][b],pre[a][b]-cost*(a+b));
		
		for (a=1;a<=n;a++)
		for (b=n;b>=a+1;b--)
		pre[a][b]=min(min(pre[a][b+1],pre[a-1][b]),f[i-1][a][b]+cost*(b-a));
		for (a=1;a<=n;a++)
		for (b=a+1;b<=n;b++)
		f[i][a][b]=min(f[i][a][b],pre[a][b]-cost*(b-a));
		
		for (a=n;a>=1;a--)
		for (b=a+1;b<=n;b++)
		pre[a][b]=min(min(pre[a][b-1],pre[a+1][b]),f[i-1][a][b]-cost*(b-a));
		for (a=1;a<=n;a++)
		for (b=a+1;b<=n;b++)
		f[i][a][b]=min(f[i][a][b],pre[a][b]+cost*(b-a));
		
		for (a=1;a<=n;a++)
		for (b=a+1;b<=n;b++)
		f[i][a][b]+=val[i][a]+val[i][b];
	}
	int ans=inf;
	for (i=1;i<=n;i++)
	for (j=i+1;j<=n;j++)
	ans=min(ans,f[m][i][j]);
	printf ("%d",ans);
	return 0;
}

