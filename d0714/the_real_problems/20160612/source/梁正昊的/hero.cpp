#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

#define fo(i,a,b) for (int i=a;i<=b;i++)
#define fd(i,a,b) for (int i=a;i>=b;i--)
#define min(a,b) ((a<b)?a:b)	

typedef long long ll;

const int maxn=310;

int n,m,K,ans,ii,val[maxn][maxn],f[2][maxn][maxn],g[maxn][maxn];

int main()
{
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	scanf("%d%d%d",&n,&m,&K);
	fo(i,1,n)
		fo(j,1,m) scanf("%d",&val[i][j]);
	fo(i,1,m)
		fo(j,i+1,m) f[0][i][j]=val[1][i]+val[1][j];
	fo(i,2,n)
	{
		fo(j,1,m)
			fo(k,1,m) f[1-ii][j][k]=1<<30;
		fo(j,1,m)
		{
			g[0][j]=1<<30;
			fo(k,0,j) g[j][k]=1<<30;
			fo(k,j+1,m) g[j][k]=min(g[j][k-1],f[ii][j][k]+K*(m-j+m-k));
		}
		fo(j,1,m)	
			fo(k,j+1,m)
			{
				g[j][k]=min(g[j][k],g[j-1][k]);
				f[1-ii][j][k]=min(f[1-ii][j][k],g[j][k]-K*(m-j+m-k)+val[i][j]+val[i][k]);
			}
		fo(j,1,m)
		{
			g[0][j]=g[j][m+1]=1<<30;
			fd(k,m,j+1) g[j][k]=min(g[j][k+1],f[ii][j][k]+K*(m-j+k));
			fd(k,j,1) g[j][k]=g[j][k+1];
		}
		fo(j,1,m)	
			fo(k,1,m)
			{
				g[j][k]=min(g[j][k],g[j-1][k]);
				if (j<k) f[1-ii][j][k]=min(f[1-ii][j][k],g[j][k]-K*(m-j+k)+val[i][j]+val[i][k]);
			}
		fo(j,1,m)
		{
			g[m+1][j]=1<<30;
			fo(k,0,j) g[j][k]=1<<30;
			fo(k,j+1,m) g[j][k]=min(g[j][k-1],f[ii][j][k]+K*(j+m-k));
		}
		fd(j,m,1)	
			fo(k,j+1,m)
			{
				g[j][k]=min(g[j][k],g[j+1][k]);
				f[1-ii][j][k]=min(f[1-ii][j][k],g[j][k]-K*(j+m-k)+val[i][j]+val[i][k]);
			}
		fo(j,1,m)
		{
			g[m+1][j]=g[j][m+1]=1<<30;
			fd(k,m,j+1) g[j][k]=min(g[j][k+1],f[ii][j][k]+K*(j+k));
			fd(k,j,1) g[j][k]=g[j][k+1];
		}
		fd(j,m,1)	
			fo(k,1,m)
			{
				g[j][k]=min(g[j][k],g[j+1][k]);
				if (j<k) f[1-ii][j][k]=min(f[1-ii][j][k],g[j][k]-K*(j+k)+val[i][j]+val[i][k]);
			}
		ii=1-ii;
	}
	ans=1<<30;
	fo(i,1,m)
		fo(j,i+1,m) ans=min(ans,f[ii][i][j]);
	printf("%d\n",ans);
}