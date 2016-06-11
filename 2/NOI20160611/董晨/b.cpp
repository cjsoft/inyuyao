#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 300005
int n,m,k,l,t,s,ans,x,y;
int a[N][4],b[N],c[N];
int main(){
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for (int j=0;j<m;j++)
		for (int i=0;i<n;i++)scanf("%d",&a[i][j]);
	for (int i=0;i<n;i++)scanf("%d",&b[i]);
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)c[i]+=a[j][b[(long long)i*j%n]];
	sort(c,c+n);
	printf("%d\n",c[n-k]);
}
