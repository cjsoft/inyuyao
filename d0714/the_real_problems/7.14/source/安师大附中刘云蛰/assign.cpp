#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
typedef double db;
const int N=22,M=1030;
db f[2][N][M*N],g[N][N][M*N],ff[2][N][M*N],gg[N][N][M*N];
int l[N],r[N];
int main(){
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	int n,i,j,k,m=0,p,a,b,sc;
	db sa,sb,prob,tmp,pp,t1,t2,smg;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",&l[i]),l[i]=l[i]*n+n-i+1;
	for(i=1;i<=n;i++) scanf("%d",&r[i]),r[i]=r[i]*n+n-i+1,m=max(m,r[i]);
	scanf("%d",&p);
	for(k=0;k<=m;k++) g[n+1][0][k]=gg[n+1][0][k]=1;
	for(i=n;i>=1;i--)
	    for(j=0;j<=n-i+1;j++)
	    	for(k=0;k<=m;k++){
	    		if(l[i]==k) prob=1,pp=1-1.0/((r[i]-l[i])/n+1);
	    		else if(l[i]>=k) prob=1,pp=1;
	    		else if(r[i]<k) prob=0,pp=0;
	    		else if(k==r[i]) prob=1.0*((r[i]-k)/n+1)/((r[i]-l[i])/n+1),pp=0;
	    		else prob=1.0*((r[i]-k)/n+1)/((r[i]-l[i])/n+1),pp=1.0*((r[i]-k-1)/n+1)/((r[i]-l[i])/n+1);
	    		if(j) g[i][j][k]=g[i+1][j-1][k]*prob,gg[i][j][k]=gg[i+1][j-1][k]*pp;
	    		smg=(k>=l[i]&&k<=r[i]&&(k-l[i])%n==0?1.0:0.0)/((r[i]-l[i])/n+1);
	    		g[i][j][k]+=g[i+1][j][k]*(1-prob),gg[i][j][k]+=gg[i+1][j][k]*(1-pp-smg);
	    	}
	for(k=0;k<=m;k++) f[0][0][k]=ff[0][0][k]=1;
	for(i=1;i<=n;i++){
		sa=0;sb=0;
	    for(a=0;a<p&&a<i;a++){
	    	b=p-a-1;if(b>n-i) continue;
	    	for(sc=0;sc<=r[i];sc++){
	    		if(l[i]>sc) prob=1,pp=0;
	    		else{
			        prob=1.0*((r[i]-sc)/n+1)/((r[i]-l[i])/n+1);
					pp=((sc-l[i])%n==0?1.0:0.0)/((r[i]-l[i])/n+1);
				}
	    		t1=f[i-1&1][a][sc]-ff[i-1&1][a][sc];
	    		t2=g[i+1][b][sc]-gg[i+1][b][sc];
	    		tmp=t1*prob*g[i+1][b][sc]+f[i-1&1][a][sc]*prob*t2+f[i-1&1][a][sc]*g[i+1][b][sc]*pp;
	    		tmp-=t1*prob*t2+t1*pp*g[i+1][b][sc]+t2*pp*f[i-1&1][a][sc];
	    		tmp+=t1*t2*pp;
	    		if(a%4==0||a%4==3) sa+=tmp;
	    		else sb+=tmp;
	    	}
	    }
	    for(j=0;j<=i;j++)
	    	for(k=0;k<=m;k++){
	    		f[i&1][j][k]=0;ff[i&1][j][k]=0;
	    		if(l[i]==k) prob=1,pp=1-1.0/((r[i]-l[i])/n+1);
	    		else if(l[i]>k) prob=1,pp=1;
	    		else if(r[i]<k) prob=0,pp=0;
	    		else if(k==r[i]) prob=1.0*((r[i]-k)/n+1)/((r[i]-l[i])/n+1),pp=0;
	    		else prob=1.0*((r[i]-k)/n+1)/((r[i]-l[i])/n+1),pp=1.0*((r[i]-k-1)/n+1)/((r[i]-l[i])/n+1);
	    		if(j) f[i&1][j][k]=f[i-1&1][j-1][k]*prob,ff[i&1][j][k]=ff[i-1&1][j-1][k]*pp;
	    		smg=(k>=l[i]&&k<=r[i]&&(k-l[i])%n==0?1.0:0.0)/((r[i]-l[i])/n+1);
	    		f[i&1][j][k]+=f[i-1&1][j][k]*(1-prob),ff[i&1][j][k]+=ff[i-1&1][j][k]*(1-pp-smg);
	    	}
	    printf("%.6lf %.6lf\n",sa,sb);
	}
	return 0;
}

