#include<iostream>
#include<cstdio>
#include<algorithm>
#define N 301
using namespace std;
int n,m,K;
long long f[2][N][N];
int a[N][N];
int main(){
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	scanf("%d %d %d",&n,&m,&K);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	bool bz=0,bz1=1;
	for (int i=1;i<=m;i++)
		for (int j=1;j<=m;j++)
			if (i!=j)
				f[bz][i][j]=a[1][i]+a[1][j];
	for (int i=2;i<=n;i++){
		long long s;
		for (int k=1;k<=m;k++){
			s=0;
			for (int j=1;j<=m;j++){
				if (s)s+=K;
				if (f[bz][j][k]){
					if (!s||s>f[bz][j][k])s=f[bz][j][k];
				}
				if (s)
				if (!f[bz1][j][k]||f[bz1][j][k]>s+a[i][j])f[bz1][j][k]=s+a[i][j];
			}
			s=0;
			for (int j=m;j>=1;j--){
				if (s)s+=K;
				if (f[bz][j][k]){
					if (!s||s>f[bz][j][k])s=f[bz][j][k];
				}
				if (s)
				if (!f[bz1][j][k]||f[bz1][j][k]>s+a[i][j])f[bz1][j][k]=s+a[i][j];
			}
		}
		for (int j=1;j<=m;j++)
			for (int k=1;k<=m;k++)
				f[bz][j][k]=0;
		bz^=1,bz1^=1;
		for (int j=1;j<=m;j++){
			s=0;
			for (int k=1;k<=m;k++){
				if (s)s+=K;
				if (f[bz][j][k]){
					if (!s||s>f[bz][j][k])s=f[bz][j][k];
				}
				if (j!=k&&s)
				if (!f[bz1][j][k]||f[bz1][j][k]>s+a[i][k])f[bz1][j][k]=s+a[i][k];
			}
			s=0;
			for (int k=m;k>=1;k--){
				if (s)s+=K;
				if (f[bz][j][k]){
					if (!s||s>f[bz][j][k])s=f[bz][j][k];
				}
				if (j!=k&&s)
				if (!f[bz1][j][k]||f[bz1][j][k]>s+a[i][k])f[bz1][j][k]=s+a[i][k];
			}
		}
		
		for (int j=1;j<=m;j++)
			for (int k=1;k<=m;k++)
				f[bz][j][k]=0;
		bz^=1,bz1^=1;
	}
	long long ans=0;
	for (int i=1;i<=m;i++)
		for (int j=1;j<=m;j++)
			if (f[bz][i][j]&&(!ans||ans>f[bz][i][j]))ans=f[bz][i][j];
	printf("%lld\n",ans);
	return 0;
}