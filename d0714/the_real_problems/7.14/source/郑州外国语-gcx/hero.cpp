#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int inf=0x3fffffff;
int n,m,k;
int a[25];
int f[25][25][25];

int cal(int a,int b)
{
	if(a>b) swap(a,b);
	return (b-a)*k;
}

int main()
{
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;++i) 
		for(int j=1;j<=m;++j)
		for(int k=1;k<=m;++k)
			f[i][j][k]=inf;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j) scanf("%d",a+j);
		for(int j1=1;j1<=m;++j1)
		for(int k1=j1+1;k1<=m;++k1)
			for(int j2=1;j2<=m;++j2)
			for(int k2=j2+1;k2<=m;++k2)
				f[i][j1][k1]=min(f[i][j1][k1],a[k2]+a[j2]+f[i-1][j2][k2]+min(cal(k1,k2)+cal(j1,j2),cal(k1,j2)+cal(k2,j1)));
	}
	int ans=inf;
	for(int j=1;j<=m;++j)
	for(int k=j+1;k<=m;++k)
		ans=min(f[n][j][k],ans);
	printf("%d",ans);
	return 0;
}

