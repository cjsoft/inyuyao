#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
#define min(a,b) ((a)<(b)?(a):(b))
using namespace std;
int n,m,p,x[310][310],f[310][310],g[310][310][310];
int main()
{
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	int i,j,k;
	scanf("%d%d%d",&n,&m,&p);
	for(i=1;i<=n;i++)
	  for(j=1;j<=m;j++)
	    scanf("%d",&x[i][j]);
	for(i=0;i<=m+1;i++)
	  f[0][i]=f[i][m+1]=f[i][i]=1000000000;
	for(k=1;k<n;k++)
	  {
	   for(i=1;i<m;i++)
	     for(j=i+1;j<=m;j++)
	       f[i][j]+=x[k][i]+x[k][j];
	   for(i=1;i<m;i++)
	     for(j=i+1;j<=m;j++)
	       f[i][j]=min(f[i][j],min(f[i-1][j],f[i][j-1])+p);
	   for(i=m-1;i>0;i--)
	     for(j=m;j>i;j--)
	       f[i][j]=min(f[i][j],min(f[i+1][j],f[i][j+1])+p);
	  }
	p=1000000000;
	for(i=1;i<m;i++)
	  for(j=i+1;j<=m;j++)
	    p=min(p,f[i][j]+x[n][i]+x[n][j]);
	printf("%d\n",p);
	return 0;
}

