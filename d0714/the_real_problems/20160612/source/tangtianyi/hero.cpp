#include<bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define For(i,j,k) for (int i=j;i<=k;++i)
#define foR(i,j,k) for (int i=j;i>=k;--i)
#define mem(a,x) memset(a,x,sizeof(a))
#define sqr(x) (x)*(x)
const int N=310,inf=0x3fffffff;
int a[N][N],an[N][N],g[N][N],f[N][N],ans=inf,n,m,k;
template <typename T>void cmin(T &a,T b){a=min(a,b);}
template <typename T>void cmax(T &a,T b){a=max(a,b);}
template <typename T>
void read(T &x){
	char c;T f=1;
	while (!isdigit(c=getchar())) if (c=='-') f=-1;
	x=c-'0';
	while (isdigit(c=getchar())) x=x*10+c-'0';
	x*=f;
}
int main(){
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	read(n),read(m),read(k);
	For (i,1,n) For (j,1,m) read(a[i][j]);
	mem(f,60);
	For (l,1,n){
		mem(g,60);
		For (i,1,m)
			For (j,1,m)
				f[i][j]=min(an[i][j]-(i+j)*k,min(f[i-1][j],f[i][j-1])),cmin(g[i][j],f[i][j]+(i+j)*k);
		For (i,1,m)
			foR (j,m,1)
				f[i][j]=min(an[i][j]-(i-j)*k,min(f[i-1][j],f[i][j+1])),cmin(g[i][j],f[i][j]+(i-j)*k);
		foR (i,m,1)
			For (j,1,m)
				f[i][j]=min(an[i][j]-(j-i)*k,min(f[i+1][j],f[i][j-1])),cmin(g[i][j],f[i][j]+(j-i)*k);
		foR (i,m,1)
			foR (j,m,1)
				f[i][j]=min(an[i][j]+(j+i)*k,min(f[i+1][j],f[i][j+1])),cmin(g[i][j],f[i][j]-(j+i)*k);
		For (i,1,m)
			For (j,1,m)
				i==j ? an[i][j]=inf :an[i][j]=g[i][j]+a[l][i]+a[l][j];
	}
	For (i,1,m)
		For (j,1,m)
			cmin(ans,an[i][j]);
	printf("%d\n",ans);
	return 0;
}
