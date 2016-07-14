#include <algorithm>
#include <cstring>
#include <cstdio>
#define rep(i,n) for(int i=1;i<=n;++i)
#define N 305
#define inf 0x3f3f3f3f
using namespace std;
int p[2][N][N],t[N][N],s[N],a[N][N],n,m,ks,r=1,ans=inf;
int main(){
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	scanf("%d%d%d",&n,&m,&ks);
	rep(i,n)rep(j,m)scanf("%d",&a[i][j]);
	rep(i,n){
		for(int j=2;j<=m;++j){
			s[m+1]=inf;int tp=inf;
			for(int k=j-1;k;--k)s[k]=min(s[k+1]+ks,t[k][j]);
			for(int k=1;k<=j;++k)tp=min(tp+ks,t[k][j]),p[r][k][j]=min(tp,s[k])+a[i][k]+a[i][j];
		}
		//rep(j,m)for(int k=j+1;k<=m;++k)printf("%d%c",p[r][j][k],k==m?'\n':' ');
		rep(j,m){
			s[m+1]=inf;int tp=inf;
			for(int k=m;k>j;--k)s[k]=min(s[k+1]+ks,p[r][j][k]);
			for(int k=j+1;k<=m;++k)tp=min(tp+ks,p[r][j][k]),t[j][k]=min(tp,s[k]);
		}
		r^=1;
	}
	r^=1;
	rep(i,m)for(int j=i+1;j<=m;++j)ans=min(ans,p[r][i][j]);
	printf("%d\n",ans);
	return 0;
}