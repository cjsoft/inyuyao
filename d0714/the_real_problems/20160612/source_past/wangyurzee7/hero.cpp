#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define N 305
#define INF (2e9)

using namespace std;
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while ('0'<=ch&&ch<='9'){
		ret=ret*10-48+ch;
		ch=getchar();
	}
	return ret;
}

int n,m,kk;
int val[N][N];
int dp[N][N];

int main(){
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	n=read();m=read();kk=read();
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			val[i][j]=read();
	memset(dp,0,sizeof(dp));
	for (int i=1;i<=n;++i){
		for (int j=1;j<=m;++j)
			for (int k=1;k<=j;++k)
				dp[j][k]=INF;
		for (int j=1;j<=m;++j)
			for (int k=j+1;k<=m;++k)
				dp[j][k]+=val[i][j]+val[i][k];
		for (int j=1;j<=m;++j){
			for (int k=2;k<=m;++k)dp[j][k]=min(dp[j][k],dp[j][k-1]+kk);
			for (int k=m-1;k;--k) dp[j][k]=min(dp[j][k],dp[j][k+1]+kk);
		}
		for (int k=1;k<=m;++k){
			for (int j=2;j<=m;++j)dp[j][k]=min(dp[j][k],dp[j-1][k]+kk);
			for (int j=m-1;j;--j) dp[j][k]=min(dp[j][k],dp[j+1][k]+kk);
		}
	}
	int ans=INF;
	for (int j=1;j<=m;++j)
		for (int k=j+1;k<=m;++k)
			ans=min(ans,dp[j][k]);
	printf("%d\n",ans);
	return 0;
}
