#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define MAXN 305
#define INF 10000000000000000LL

int t[MAXN][MAXN];
ll f[MAXN][MAXN][MAXN];

int mx[MAXN],q2[MAXN];
int qq1[MAXN];
ll k;

int main(){
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	int n,m;
	cin>>n>>m>>k;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%d",&t[i][j]);
	for(int i=0;i!=MAXN;++i)
		for(int j=0;j!=MAXN;++j)
			for(int k=0;k!=MAXN;++k)
				if(i||j==k)f[i][j][k]=INF;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j)mx[j]=1;
		for(int col=1;col<=n;++col){
			for(int j=1;j<=n;++j)
				if(k*(col-mx[j])+f[i-1][j][mx[j]]>f[i-1][j][col])mx[j]=col;
			int qmx=1;
			for(int j=1;j<=n;++j){
				if(k*(col-mx[j])+f[i-1][j][mx[j]]<k*(col-mx[qmx]+j-qmx)+f[i-1][qmx][mx[qmx]])qmx=j;
				if(j==col)continue;
				f[i][j][col]=min(f[i][j][col],f[i-1][qmx][mx[qmx]]+t[i][col]+t[i][j]+k*(col-mx[qmx]+j-qmx));
			}
			qmx=n;
			for(int j=n;j>=1;--j){
				if(k*(col-mx[j])+f[i-1][j][mx[j]]<k*(col-mx[qmx]+qmx-j)+f[i-1][qmx][mx[qmx]])qmx=j;
				if(j==col)continue;
				f[i][j][col]=min(f[i][j][col],f[i-1][qmx][mx[qmx]]+t[i][col]+t[i][j]+k*(col-mx[qmx]+qmx-j));
			}
		}
		for(int j=1;j<=n;++j)mx[j]=n;
		for(int col=n;col>=1;--col){
			for(int j=1;j<=n;++j)
				if(k*(mx[j]-col)+f[i-1][j][mx[j]]>f[i-1][j][col])mx[j]=col;
			int qmx=1;
			for(int j=1;j<=n;++j){
				if(k*(mx[j]-col)+f[i-1][j][mx[j]]<k*(mx[qmx]-col+j-qmx)+f[i-1][qmx][mx[qmx]])qmx=j;
				if(j==col)continue;
				f[i][j][col]=min(f[i][j][col],f[i-1][qmx][mx[qmx]]+t[i][j]+t[i][col]+k*(mx[qmx]-col+j-qmx));
			}
			qmx=n;
			for(int j=n;j>=1;--j){
				if(k*(mx[j]-col)+f[i-1][j][mx[j]]<k*(mx[qmx]-col+qmx-j)+f[i-1][qmx][mx[qmx]])qmx=j;
				if(j==col)continue;
				f[i][j][col]=min(f[i][j][col],f[i-1][qmx][mx[qmx]]+t[i][j]+t[i][col]+k*(mx[qmx]-col+qmx-j));
			}
		}
	}
	ll ans=INF;
	for(int i=1;i<=m;++i)
		for(int j=1;j<=m;++j)
			if(i!=j)ans=min(ans,f[n][i][j]);
	cout<<ans<<endl;
	return 0;
	
}
