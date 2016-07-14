#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
using namespace std;

struct Node{int x,y;};

int S=0,T=100000,TT=100001;
long long f[51][51][51],K,ans=1ll<<60;
int a[310][310],n,m;

int pos(int i,int j){return (i-1)*m+j;}
int abs(int a){return a>0?a:-a;}
int dis(int x,int y,int a,int b){return min(abs(x-a)+abs(y-b),abs(x-b)+abs(y-a));}

int main(){
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	scanf("%d %d %lld",&n,&m,&K);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	if(n<=50&&m<=50){
		memset(f,127,sizeof(f));
		for(int i=1;i<=m;i++)
			for(int j=i+1;j<=m;j++)
				f[1][i][j]=a[1][i]+a[1][j];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				for(int k=j+1;k<=m;k++)
					for(int x=1;x<=m;x++)
						for(int y=x+1;y<=m;y++)
							f[i][j][k]=min(f[i][j][k],f[i-1][x][y]+a[i][j]+a[i][k]+K*dis(j,k,x,y));
		for(int i=1;i<=m;i++)
			for(int j=i+1;j<=m;j++)
				ans=min(ans,f[n][i][j]);
		printf("%lld\n",ans);
	}return 0;	
}
