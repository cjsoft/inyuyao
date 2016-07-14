#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<memory.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<queue>
#include<map>
#include<set>
#include<list>
#include<deque>
#include<vector>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define F(i,j,n) for(register int i=j;i<=n;i++)
#define D(i,j,n) for(register int i=j;i>=n;i--)
#define ll long long
#define lc (k<<1)
#define rc ((k<<1)|1)
using namespace std;
void in(int&a);void in(ll&a);
int a[310][310],inf=1e9,n,m,k;
int f[2][310][310],xy[310][310],ij[310][310],xj[310][310],iy[310][310],b,c,d;
int main()
{
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	in(n);in(m);in(k);
	F(i,1,n)F(j,1,m)in(a[i][j]);
	F(i,0,m+1)F(j,0,m+1)if(i&j&i^(m+1)&j^(m+1)&i<j)f[1][i][j]=a[1][i]+a[1][j];else f[1][i][j]=inf;
	F(l,2,n){
	F(i,0,m+1)F(j,0,m+1)xy[i][j]=ij[i][j]=xj[i][j]=iy[i][j]=f[l&1][i][j]=inf;
	D(i,m,1)D(j,m,i+1)if(i==j)xy[i][j]=inf;
	else{b=min(xy[i+1][j],xy[i][j+1]);c=f[(l-1)&1][i][j]+(i+j)*k;xy[i][j]=min(b,c);}
	D(i,m,1)F(j,i+1,m)if(i==j)xj[i][j]=inf;
	else{b=min(xj[i+1][j],xj[i][j-1]);c=f[(l-1)&1][i][j]+(i-j)*k;xj[i][j]=min(b,c);}
	F(i,1,m)D(j,m,i+1)if(i==j)iy[i][j]=inf;
	else{b=min(iy[i-1][j],iy[i][j+1]);c=f[(l-1)&1][i][j]-(i-j)*k;iy[i][j]=min(b,c);}
	F(i,1,m)F(j,i+1,m)if(i==j)ij[i][j]=inf;
	else{b=min(ij[i-1][j],ij[i][j-1]);c=f[(l-1)&1][i][j]-(i+j)*k;ij[i][j]=min(b,c);}
	F(i,1,m)F(j,i+1,m){
	d=xy[i][j]-(i+j)*k;b=ij[i][j]+(i+j)*k;b=min(d,b);
	d=xj[i][j]-(i-j)*k;c=iy[i][j]+(i-j)*k;c=min(d,c);
	f[l&1][i][j]=min(b,c)+a[l][i]+a[l][j];}
	}
	F(i,1,m)F(j,i+1,m)inf=min(inf,f[n&1][i][j]);
	printf("%d\n",inf);
//	printf("%.3lf\n",(double)clock()/CLOCKS_PER_SEC);
	return 0;
}
void in(ll&a){register char c;register bool y=false;c=getchar();a=0;
while(c<'0'||c>'9'){if(c=='-'){c=getchar();y=true;break;}c=getchar();}
while(c>='0'&&c<='9'){a=(a<<3)+(a<<1)+c-'0';c=getchar();}if(y)a=-a;}
void in(int&a){register char c;register bool y=false;c=getchar();a=0;
while(c<'0'||c>'9'){if(c=='-'){c=getchar();y=true;break;}c=getchar();}
while(c>='0'&&c<='9'){a=(a<<3)+(a<<1)+c-'0';c=getchar();}if(y)a=-a;}
