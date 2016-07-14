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

const int N=50;

int n,l[N],r[N],k;
double f[N][N],g[N][N],p[N],x[N],AnsA[N],AnsB[N];

void dp(int t)
{
	memset(f,0,sizeof f);
	f[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=i&&j<=k;j++)
		{
			f[i][j]=f[i-1][j]*(1-p[i]);
			if(j)
				f[i][j]+=f[i-1][j-1]*p[i];
		}
	memset(g,0,sizeof g);
	g[n+1][0]=1;
	for(int i=n;i;i--)
		for(int j=0;j<=k;j++)
		{
			g[i][j]=g[i+1][j]*(1-p[i]);
			if(j)
				g[i][j]+=g[i+1][j-1]*p[i];
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=k;j++)
		{
			double v=f[i-1][j-1]*p[i]*g[i+1][k-j]/(r[t]-l[t]+1);
			if((j&3)<2)
				AnsA[i]+=v;
			else
				AnsB[i]+=v;
		}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&l[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&r[i]);
	scanf("%d",&k);
	for(int i=1;i<=n;i++)
		for(int v=l[i];v<=r[i];v++)
		{
			for(int j=1;j<i;j++)
				if(v<=l[j])
					p[j]=1;
				else if(v>r[j])
					p[j]=0;
				else
					p[j]=(r[j]-v+1.)/(r[j]-l[j]+1.);
			for(int j=i+1;j<=n;j++)
				if(v<l[j])
					p[j]=1;
				else if(v>=r[j])
					p[j]=0;
				else
					p[j]=(r[j]-v)/(r[j]-l[j]+1.);
			p[i]=1;dp(i);
		}
	for(int i=1;i<=n;i++)
		printf("%.6lf %.6lf\n",AnsA[i],AnsB[i]);
	return 0;
}
