#include<iostream>
#include<algorithm>
#include<cstdio>
#define N 30
#define M 1001
using namespace std;
long double fr[N][M][N][N],ba[N][M][N][N];
int n,K;
int L[N],R[N];
long double min(long double x,long double y){
	return x<y?x:y;
}
int main(){
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&L[i]);
	for (int i=1;i<=n;i++)
		scanf("%d",&R[i]);
	scanf("%d",&K);
	for (int i=0;i<M;i++)
		fr[0][i][0][0]=1,ba[n+1][i][0][0]=1;
	for (register int i=0;i<n;i++)
		for (register int j=0;j<M;j++)
			for (register int k=0;k<=K;k++)
				for (register int sig=0;sig<=K;sig++)
					if (fr[i][j][k][sig]>0){
						if (L[i+1]<j)fr[i+1][j][k][sig]+=fr[i][j][k][sig]*min((long double)(j-L[i+1])/(R[i+1]-L[i+1]+1),1.0);
						if (L[i+1]<=j&&j<=R[i+1])fr[i+1][j][k][sig+1]+=fr[i][j][k][sig]/(R[i+1]-L[i+1]+1);
						if (R[i+1]>j)fr[i+1][j][k+1][sig]+=fr[i][j][k][sig]*min((long double)(R[i+1]-j)/(R[i+1]-L[i+1]+1),1.0);	
					}
	for (register int i=n+1;i>=2;i--)
		for (register int j=0;j<M;j++)
			for (register int k=0;k<=K;k++)
				for (register int sig=0;sig<=K;sig++)
					if (ba[i][j][k][sig]>0){
						if (L[i-1]<j)ba[i-1][j][k][sig]+=ba[i][j][k][sig]*min((long double)(j-L[i-1])/(R[i-1]-L[i-1]+1),1.0);
						if (L[i-1]<=j&&j<=R[i-1])ba[i-1][j][k][sig+1]+=ba[i][j][k][sig]/(R[i-1]-L[i-1]+1);
						if (R[i-1]>j)ba[i-1][j][k+1][sig]+=ba[i][j][k][sig]*min((long double)(R[i-1]-j)/(R[i-1]-L[i-1]+1),1.0);
					}
	for (register int i=1;i<=n;i++){
		long double s1=0,s2=0;
		for (register int j=0;j<=R[i];j++)
			for (register int k=0;k<=K-1;k++)
				for (register int sig1=0;sig1<=n-k-1;sig1++)
					if (fr[i-1][j][k][sig1])
						for (register int kk=0;kk<=K-k-1;kk++)
							for (register int sig2=0;sig2<=n-k-1-kk-sig1;sig2++)
								if (ba[i+1][j][kk][sig2]){
									if (sig1+k+sig2+kk+1<K)continue;
									if (kk+k+sig1+1<=K&&L[i]<=j&&j<=R[i]){
										if ((k+sig1+1)%4==1||(k+sig1+1)%4==0)s1+=fr[i-1][j][k][sig1]*ba[i+1][j][kk][sig2]/(R[i]-L[i]+1);
										else
											s2+=fr[i-1][j][k][sig1]*ba[i+1][j][kk][sig2]/(R[i]-L[i]+1);
									}
									int z=min(sig1,K-k-kk-1);
									if (z<0)continue;
									if ((sig1||sig2)&&k+kk+2<=K&&kk+k+1+z<=K&&j<R[i]){
										if ((k+1+z)%4==1||(k+1+z)%4==0)s1+=fr[i-1][j][k][sig1]*ba[i+1][j][kk][sig2]*min((long double)(R[i]-j)/(R[i]-L[i]+1),1.0);
										else
											s2+=fr[i-1][j][k][sig1]*ba[i+1][j][kk][sig2]*min((long double)(R[i]-j)/(R[i]-L[i]+1),1.0);
									}
								}
		printf("%.6f %.6f\n",(double)s1,(double)s2);
	}
	return 0;
}