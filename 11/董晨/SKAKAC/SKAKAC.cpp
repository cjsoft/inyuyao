#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define N 35
#define M 100000
int T,n,m,k,l,t,s,u,v,x,y,ll;
int a[N][N],flag[N][N],q[2][M][2];
int fx[8]={1,1,2,2,-1,-1,-2,-2};
int fy[8]={2,-2,1,-1,2,-2,1,-1};
int main(){
	freopen("SKAKAC.in","r",stdin);
	freopen("SKAKAC.out","w",stdout);
	scanf("%d%d",&n,&T);
	scanf("%d%d",&x,&y);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)scanf("%d",&a[i][j]),flag[i][j]=-1;
	flag[x][y]=0;
	q[0][1][0]=x,q[0][1][1]=y;
	ll=1;
	u=1,v=0;
	while(t<T){
		t++;
		l=ll;u^=1,v^=1;
		ll=0;
		for (int i=1;i<=l;i++){
			x=q[u][i][0],y=q[u][i][1];
			for (int j=0;j<8;j++){
				int xx=x+fx[j],yy=y+fy[j];
				if(xx<1||xx>n||yy<1||yy>n)continue;
				if(t%a[xx][yy])continue;
				if(flag[xx][yy]!=t){
					flag[xx][yy]=t;
					q[v][++ll][0]=xx;
					q[v][ll][1]=yy;
				}
			}
		}
	}
	printf("%d\n",ll);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)if(flag[i][j]==T)printf("%d %d\n",i,j);
}
