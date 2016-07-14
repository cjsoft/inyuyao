#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
typedef long long ll;
const ll INF=2147483640;
ll a[351][351],g[351][351][351];
ll n,m,kk;
void init()
{
	scanf("%d%d%d",&n,&m,&kk);
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
	  	scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
	    for(int k=1;k<=m;k++)
	      g[i][j][k]=INF;
	for(int i=1;i<=n;i++)
	{
	  for(int j=1;j<m;j++)
	    for(int k=j+1;k<=m;k++)
	      for(int l=1;l<m;l++)
	        for(int o=l+1;o<=m;o++)
	          g[i][l][o]=min(g[i][l][o],g[i-1][j][k]+a[i][l]+a[i][o]+kk*abs(j-l)+kk*abs(k-o)); 
    }
	int minn=INF;
	for(int i=1;i<=m;i++)
	
	  for(int j=1;j<=m;j++)
	    if(g[n][i][j]<minn)  
	      minn=g[n][i][j];
	printf("%d\n",minn);
}
int main()
{
	freopen("hero.in","r",stdin);
	init();
	return 0;
}
