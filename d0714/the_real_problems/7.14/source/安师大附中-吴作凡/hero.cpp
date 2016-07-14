#include<algorithm>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include  <stdio.h>
#include   <time.h>
#include   <math.h>
#include   <bitset>
#include   <vector>
#include    <queue>
#include      <set>
#include      <map>
using namespace std;

const int N=305,oo=1<<30;

int K,n,m,f[2][N][N],t[N][N],Min[N][N];

void dp(int i,int g[][N],int f[][N])
{
	for(int l=1;l<=m;l++)
		for(int r=1;r<=m;r++)
			f[l][r]=oo;
	for(int l=1;l<=m;l++)
		for(int r=1;r<=m;r++)
		{
			Min[l][r]=g[l][r]-K*(l+r);
			if(l!=1)
				Min[l][r]=min(Min[l][r],Min[l-1][r]);
			if(r!=1)
				Min[l][r]=min(Min[l][r],Min[l][r-1]);
			f[l][r]=min(f[l][r],Min[l][r]+K*(l+r));
		}
	for(int l=1;l<=m;l++)
		for(int r=m;r;r--)
		{
			Min[l][r]=g[l][r]+K*(r-l);
			if(l!=1)
				Min[l][r]=min(Min[l][r],Min[l-1][r]);
			if(r!=m)
				Min[l][r]=min(Min[l][r],Min[l][r+1]);
			f[l][r]=min(f[l][r],Min[l][r]+K*(l-r));
		}
	for(int l=m;l;l--)
		for(int r=1;r<=m;r++)
		{
			Min[l][r]=g[l][r]+K*(l-r);
			if(l!=m)
				Min[l][r]=min(Min[l][r],Min[l+1][r]);
			if(r!=1)
				Min[l][r]=min(Min[l][r],Min[l][r-1]);
			f[l][r]=min(f[l][r],Min[l][r]+K*(r-l));
		}
	for(int l=m;l;l--)
		for(int r=m;r;r--)
		{
			Min[l][r]=g[l][r]+K*(l+r);
			if(l!=m)
				Min[l][r]=min(Min[l][r],Min[l+1][r]);
			if(r!=m)
				Min[l][r]=min(Min[l][r],Min[l][r+1]);
			f[l][r]=min(f[l][r],Min[l][r]-K*(l+r));
		}
	for(int l=1;l<=m;l++)
		for(int r=1;r<=m;r++)
			f[l][r]+=t[i][l]+t[i][r];
	for(int l=1;l<=m;l++)
		f[l][l]=oo;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&t[i][j]);
	for(int i=1;i<=n;i++)
		dp(i,f[!(i&1)],f[i&1]);
	int Ans=oo;
	for(int i=1;i<=m;i++)
		for(int j=i+1;j<=m;j++)
			Ans=min(Ans,f[n&1][i][j]);
	cout<<Ans<<endl;
	return 0;
}
