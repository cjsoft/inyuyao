#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<math.h>
using namespace std;
int n,T,y[25],ans;
int a[25][25],b[25][25];
void dfs(int x)
{
	if (x==n+1)
	{
		for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		b[i][j]=y[i]^y[j];
		for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		if (((!a[i][j])|b[i][j])==0)
		return ;
		int tot=0;
		for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		if (((!b[i][j])|a[i][j])==0)
		tot++;
		ans=max(ans,tot);
		return ;
	}
	y[x]=1;
	dfs(x+1);
	y[x]=0;
	dfs(x+1);
}
int main()
{
	freopen("fxxk.in","r",stdin);
	freopen("fxxk.out","w",stdout);
scanf("%d",&T);
while(T--)
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	for (int j=1;j<=n;j++)
	scanf("%d",&a[i][j]);
	ans=-1;
	dfs(1);
	printf("%d\n",ans);
}
}
