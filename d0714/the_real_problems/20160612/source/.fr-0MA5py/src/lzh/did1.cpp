#include<iostream>
#include<cstdio>
#include<algorithm>
#define N 301
using namespace std;
long long f[2][N][N];
int a[N][N];
int n,m,K;
int main(){
	freopen("hero.in","r",stdin);
	freopen("did1.out","w",stdout);
	scanf("%d %d %d",&n,&m,&K);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	int bz=0,bz1=1;
	for (int i=1;i<=m;i++)
		for (int j=1;j<=m;j++)
			if (i!=j)
				f[bz][i][j]=a[1][i]+a[1][j];
	for (int i=2;i<=n;i++,bz^=1,bz1^=1)
		for (int j=1;j<=m;j++)
			for (int k=1;k<=m;k++)
				if (f[bz][j][k]){
					for (int l=1;l<=m;l++){
						long long v1=a[i][l]+(long long)K*abs(j-l);
						for (int ll=1;ll<=m;ll++)
							if (l!=ll)
								if (!f[bz1][l][ll]||f[bz1][l][ll]>f[bz][j][k]+v1+a[i][ll]+(long long)K*abs(k-ll))
									f[bz1][l][ll]=f[bz][j][k]+v1+a[i][ll]+(long long)K*abs(k-ll);
					}	
					f[bz][j][k]=0;
				}
	long long ans=0;
	for (int i=1;i<=m;i++)
		for (int j=1;j<=m;j++)
			if (f[bz][i][j]&&(!ans||ans>f[bz][i][j]))ans=f[bz][i][j];
	printf("%lld\n",ans);
	return 0;
}