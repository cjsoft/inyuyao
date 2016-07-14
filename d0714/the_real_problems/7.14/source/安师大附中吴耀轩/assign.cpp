#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <memory.h>
#include <time.h>
using namespace std;
const int maxn = 30;
int L[maxn],R[maxn],n,K;
double f[maxn][maxn];
double g[maxn][maxn];
double ans1[maxn],ans2[maxn];
double exp1(const int &t,const int &l) { //<=l
	return max(0.0,(min(R[t],l)-L[t]+1)/(double)(R[t]-L[t]+1));
}
double exp2(const int &t,const int &l) { //>l
	return max(0.0,(R[t]-max(L[t],l+1)+1)/(double)(R[t]-L[t]+1));
}
double exp3(const int &t,const int &l) { //<l
	return max(0.0,(min(R[t],l-1)-L[t]+1)/(double)(R[t]-L[t]+1));
}
double exp4(const int &t,const int &l) { //>=l
	return max(0.0,(R[t]-max(L[t],l)+1)/(double)(R[t]-L[t]+1));
}
void dp(int i,int j,double p) {
	memset(f,0,sizeof(f));
	f[0][0]=1.0;
	for (register int t=1;t<i;t++) {
		f[t][0]=f[t-1][0]*exp3(t,j);
		for (register int k=1;k<=t;k++)
			f[t][k]=f[t-1][k-1]*exp4(t,j)+f[t-1][k]*exp3(t,j);
	}
	for (register int k=1;k<=i;k++)
		f[i][k]=f[i-1][k-1];
	for (register int t=i+1;t<=n;t++) {
		f[t][0]=f[t-1][0]*exp1(t,j);
		for (register int k=1;k<=t;k++)
			f[t][k]=f[t-1][k-1]*exp2(t,j)+f[t-1][k]*exp1(t,j);
	}
	
	memset(g,0,sizeof(g));
	g[n+1][0]=1.0;
	for (register int t=n;t>i;t--) {
		g[t][0]=g[t+1][0]*exp1(t,j);
		for (register int k=1;k<=n-t+1;k++)
			g[t][k]=g[t+1][k-1]*exp2(t,j)+g[t+1][k]*exp1(t,j);
	}
	for (int k=1;k<=n-i+1;k++)
		g[i][k]=g[i+1][k-1];
	for (int t=i-1;t>=1;t--) {
		g[t][0]=g[t+1][0]*exp3(t,j);
		for (register int k=1;k<=n-t+1;k++)
			g[t][k]=g[t+1][k-1]*exp4(t,j)+g[t+1][k]*exp3(t,j);
	}
	
	for (register int t=1;t<i;t++)
	for (register int k=0;k<K;k++)
	if (k%4==0||k%4==3)
		ans1[t]+=p*f[t-1][k]*g[t+1][K-k-1]*exp4(t,j);
	else
		ans2[t]+=p*f[t-1][k]*g[t+1][K-k-1]*exp4(t,j);
	for (register int k=0;k<K;k++)
	if (k%4==0||k%4==3)
		ans1[i]+=p*f[i-1][k]*g[i+1][K-k-1];
	else
		ans2[i]+=p*f[i-1][k]*g[i+1][K-k-1];
	for (register int t=n;t>i;t--)
	for (register int k=0;k<K;k++)
	if (k%4==0||k%4==3)
		ans1[t]+=p*f[t-1][k]*g[t+1][K-k-1]*exp2(t,j);
	else
		ans2[t]+=p*f[t-1][k]*g[t+1][K-k-1]*exp2(t,j);
}
int main()
{
	#ifndef ONLINE_JUDGE
		freopen("assign.in","r",stdin);
		freopen("assign.out","w",stdout);
	#endif
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&L[i]);
	for (int i=1;i<=n;i++)
		scanf("%d",&R[i]);
	scanf("%d",&K);
	for (int i=1;i<=n;i++)
	for (int j=L[i];j<=R[i];j++)
		dp(i,j,1.0/(R[i]-L[i]+1));
	for (int i=1;i<=n;i++)
		printf("%.6lf %.6lf\n",ans1[i],ans2[i]);
//		printf("%d\n",clock());
	return 0;
}	
