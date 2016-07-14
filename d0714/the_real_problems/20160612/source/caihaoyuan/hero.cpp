#include<bits/stdc++.h>
#define rep(i,j,k) for((i)=(j);(i)<=(k);++i)
#define per(i,j,k) for((i)=(j);(i)>=(k);--i)
#define cmin(x,y) (y)<(x)?(x)=(y):0
using namespace std;
typedef long long ll;
const ll inf = 1LL<<60;
const int N = 305;
ll f[N][N][N],g[N][N],ans; int n,m,i,j,k,kk,w[N][N];
int inline read(){
	char ch=getchar();int z=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){z=z*10+ch-'0';ch=getchar();}
	return z*f;
}
int main(){
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	n=read();m=read();kk=read();ans=inf;
	rep(i,1,n) rep(j,1,m) w[i][j]=read();
	rep(i,1,n) rep(j,0,m+1) rep(k,j,m+1) f[i][j][k]=inf;
	rep(i,1,n){
		rep(j,1,m) rep(k,j+1,m) g[j][k]=f[i-1][j][k]-kk*(j+k);
		rep(j,1,m) rep(k,j+1,m){cmin(g[j+1][k],g[j][k]);cmin(g[j][k+1],g[j][k]);}
		rep(j,1,m) rep(k,j+1,m) cmin(f[i][j][k],g[j][k]+kk*(j+k)+w[i][j]+w[i][k]);
		rep(j,1,m) rep(k,j+1,m) g[j][k]=f[i-1][j][k]-kk*(j-k);
		rep(j,1,m) per(k,m,j+1){cmin(g[j+1][k],g[j][k]);cmin(g[j][k-1],g[j][k]);}
		rep(j,1,m) rep(k,j+1,m) cmin(f[i][j][k],g[j][k]+kk*(j-k)+w[i][j]+w[i][k]);
		rep(j,1,m) rep(k,j+1,m) g[j][k]=f[i-1][j][k]-kk*(-j-k);
		per(j,m,1) per(k,m,j+1){cmin(g[j-1][k],g[j][k]);cmin(g[j][k-1],g[j][k]);}
		rep(j,1,m) rep(k,j+1,m) cmin(f[i][j][k],g[j][k]+kk*(-j-k)+w[i][j]+w[i][k]);
		rep(j,1,m) rep(k,j+1,m) if(j!=k) g[j][k]=f[i-1][j][k]-kk*(-j+k);
		per(j,m,1) rep(k,j+1,m){cmin(g[j-1][k],g[j][k]);cmin(g[j][k+1],g[j][k]);}
		rep(j,1,m) rep(k,j+1,m) cmin(f[i][j][k],g[j][k]+kk*(-j+k)+w[i][j]+w[i][k]);
	}
	rep(j,1,m) rep(k,j+1,m) cmin(ans,f[n][j][k]);
	printf("%lld\n",ans);
	return 0;
}
