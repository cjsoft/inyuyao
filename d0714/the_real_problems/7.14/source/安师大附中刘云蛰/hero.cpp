#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
const int N=305,inf=1000000000;
int a[N][N];
int f[N][N][N],g1[N][N],g2[N][N],g3[N][N],g4[N][N];
int mn(int x,int y){return x<y?x:y;}
int main(){
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	int n,m,p,i,j,k,ans=inf;
	scanf("%d %d %d",&n,&m,&p);
	for(i=1;i<=n;i++)
	    for(j=1;j<=m;j++)
	        scanf("%d",&a[i][j]);
	for(j=0;j<=m+1;j++){
        g1[0][j]=g1[j][0]=g2[0][j]=g2[j][0]=inf;
        g3[0][j]=g3[j][0]=g4[0][j]=g4[j][0]=inf;
        g1[m+1][j]=g1[j][m+1]=g2[m+1][j]=g2[j][m+1]=inf;
        g3[m+1][j]=g3[j][m+1]=g4[m+1][j]=g4[j][m+1]=inf;
    }
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++)
		    for(k=1;k<=m;k++)
		        g1[j][k]=mn(mn(g1[j][k-1],g1[j-1][k])+p,f[i-1][j][k]);
		for(j=m;j>=1;j--)
		    for(k=1;k<=m;k++)
		        g2[j][k]=mn(mn(g2[j+1][k],g2[j][k-1])+p,f[i-1][j][k]);
		for(j=1;j<=m;j++)
		    for(k=m;k>=1;k--)
		        g3[j][k]=mn(mn(g3[j-1][k],g3[j][k+1])+p,f[i-1][j][k]);
		for(j=m;j>=1;j--)
		    for(k=m;k>=1;k--)
		        g4[j][k]=mn(mn(g4[j+1][k],g4[j][k+1])+p,f[i-1][j][k]);
		for(j=1;j<=m;j++)
		    for(k=1;k<=m;k++){
		        if(j!=k) f[i][j][k]=mn(mn(g1[j][k],g2[j][k]),mn(g3[j][k],g4[j][k]))+a[i][j]+a[i][k];
		        else f[i][j][k]=inf;
		    }
	}
	for(j=1;j<=m;j++)
	    for(k=1;k<=m;k++)
	        ans=mn(ans,f[n][j][k]);
	printf("%d",ans);
	return 0;
}
