#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <algorithm>
#include <memory.h>
using namespace std;
//暴力一波保平安
typedef long long ll;
#define S 303
int n,m,K,t[S][S]; 
ll dp[2][S][S],dtf[2][S][S],dtz[2][S][S],qzm[2][S][S],hzm[2][S][S];
ll Abs(ll x) {return x>=0?x:-x;}
int Abs(int x) {return x>=0?x:-x;}
void gmin(ll& a,ll& b) {if(a>b) a=b;}
int gii()
{
	int a=0; char c;
	while(c=getchar(),c<'0'||c>'9');
	a=c-48;
	while(c=getchar(),c>='0'&&c<='9') a=a*10+c-48;
	return a;
}
#define R register
#define gi gii()
int main()
{
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	n=gi, m=gi, K=gi;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++) t[i][j]=gi;
	}
	const ll inf=1000000000000000000LL;
	int C=0;
	R ll ans=inf;
	for(R int i=1;i<=n;++i)
	{
		for(R int j=1;j<=m;++j)
		{
			for(R int k=1;k<=m;++k)
			{
				if(j==k) continue;
				dp[C][j][k]=((i==1)?0:(min(qzm[!C][j][k]+(ll)K*j,hzm[!C][j][k]-(ll)K*j)))+t[i][j]+t[i][k];
				dtf[C][j][k]=dp[C][j][k]+(ll)K*k;
				dtz[C][j][k]=dp[C][j][k]-(ll)K*k;
				if(i==n) ans=min(ans,dp[C][j][k]);
			}
		}
		for(R int j=1;j<=m;++j)
		dtf[C][j][0]=dtf[C][j][m+1]=dtz[C][j][0]=dtz[C][j][m+1]=dtf[C][j][j]=dtz[C][j][j]=inf;
		for(R int j=1;j<=m;++j)
		{
			for(int k=m+1;k;k--) gmin(dtf[C][j][k-1],dtf[C][j][k]), dtf[C][j][k]-=(ll)K*k;
			for(int k=0;k<=m;k++) gmin(dtz[C][j][k+1],dtz[C][j][k]), dtz[C][j][k]+=(ll)K*k;
		}
		for(R int k=1;k<=m;++k) qzm[C][0][k]=hzm[C][m+1][k]=inf;
		for(R int j=1;j<=m;++j)
			for(R int k=1;k<=m;++k)
			qzm[C][j][k]=min(qzm[C][j-1][k],min(dtf[C][j][k],dtz[C][j][k])-(ll)K*j);
		for(R int j=m;j;--j)
			for(R int k=1;k<=m;++k)
			hzm[C][j][k]=min(hzm[C][j+1][k],min(dtf[C][j][k],dtz[C][j][k])+(ll)K*j);
		C^=1;
	}
	cout<<ans<<"\n";
}
