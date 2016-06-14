#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define N 100005
#define M 21
#define ll long long
int n,m,k,l,t,s;
int a[N],p[M],mi[M];
ll ans,x,y;
int main(){
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	scanf("%d",&n);
	mi[1]=1;
	for (int i=2;i<M;i++)mi[i]=mi[i-1]*2;
	for (int j=1;j<=n;j++){
		scanf("%d",&m);
		for (int i=1;i<M;i++)if(m&mi[i])p[i]++;
	}
	for (int i=1;i<=n;i++){
		x=0;
		for (int j=1;j<M;j++)if(p[j]){
			p[j]--;
			x+=mi[j];
		}
		ans+=x*x;
	}
	printf("%lld\n",ans);
}
