#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int N,M,K,T[305][305],F[305][305],G[305][305],D[305][305],C[305][305],Ans;
int main(){
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	scanf("%d%d%d",&N,&M,&K);int i,j,k;
	for(i=1;i<=N;i++)
	    for(j=1;j<=M;j++)scanf("%d",&T[i][j]);
	for(i=1;i<=M;i++)
	    for(j=i+1;j<=M;j++)F[i][j]=T[1][i]+T[1][j];
	for(i=2;i<=N;i++){
		G[1][M]=F[1][M];
		for(j=M-1;j>1;j--)G[1][j]=min(F[1][j],G[1][j+1]+K);
		for(j=2;j<M;j++)G[j][M]=min(F[j][M],G[j-1][M]+K);
		for(j=2;j<M;j++)
		    for(k=M-1;k>j;k--)G[j][k]=min(F[j][k],min(G[j][k+1],G[j-1][k])+K);
		C[1][2]=F[1][2];
		for(j=3;j<=M;j++)C[1][j]=min(F[1][j],C[1][j-1]+K);
		for(j=2;j<M;j++){
			C[j][j+1]=min(C[j-1][j+1]+K,F[j][j+1]);
		    for(k=j+2;k<=M;k++)C[j][k]=min(min(C[j][k-1],C[j-1][k])+K,F[j][k]);
		    }
		D[M-1][M]=F[M-1][M];
		for(j=M-2;j>=1;j--)D[j][M]=min(F[j][M],D[j+1][M]+K);
		for(j=M-1;j>1;j--){
			D[j-1][j]=min(D[j-1][j+1]+K,F[j-1][j]);
			for(k=j-2;k>=1;k--)D[k][j]=min(min(D[k+1][j],D[k][j+1])+K,F[k][j]);
		    }
		for(j=1;j<=M;j++)
		    for(k=j+1;k<=M;k++)F[j][k]=min(min(G[j][k],C[j][k]),D[j][k])+T[i][j]+T[i][k];
	    }
	Ans=F[1][2];
	for(i=1;i<=M;i++)
	    for(j=i+1;j<=M;j++)Ans=min(Ans,F[i][j]);
	printf("%d\n",Ans);
	return 0;
}

