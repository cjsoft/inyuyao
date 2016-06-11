#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
int n,m,k,l,t,s,U;
double a[405][405];
void gauss(){
	int x=1,y=0;
	double t;
	for (int i=1;i<=n;i++){
		for (y=x;y<=n;y++)if(a[y][i]!=0)break;
    	if(y>n)continue;
        if(y!=x)
			for (int j=1;j<=n+1;j++)swap(a[y][j],a[x][j]);
		t=a[x][i];
		for (int j=1;j<=n+1;j++)a[x][j]/=t;
		for (int j=1;j<=n;j++){
			if(j!=x){
				t=a[j][i];
				for (int k=1;k<=n+1;k++)a[j][k]-=t*a[x][k];
			}
		}
		x++;
	}
}
int main(){
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	scanf("%d%d%lf",&m,&n,&U);
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n+1;j++)scanf("%lf",&a[i][j]);
	gauss();
	for (int i=1;i<=n;i++)printf("%.6f\n",a[i][n+1]);
}
