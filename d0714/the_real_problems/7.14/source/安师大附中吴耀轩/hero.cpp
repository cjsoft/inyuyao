#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <memory.h>
#include <time.h>
using namespace std;
typedef long long LL;
const int maxn = 305;
const LL inf = 1ll<<50;
int n,m,a[maxn][maxn],K;
LL f[2][maxn][maxn];
void upd(LL &x,LL y) {
	if (x>y) x=y;
}
LL f1[maxn],f2[maxn],f3[maxn],f4[maxn];
int main()
{
	#ifndef ONLINE_JUDGE
		freopen("hero.in","r",stdin);
		freopen("hero.out","w",stdout);
	#endif
	scanf("%d %d %d",&n,&m,&K);
	for (register int i=1;i<=n;i++)
	for (register int j=1;j<=m;j++)
		scanf("%d",&a[i][j]);
	for (register int i=1;i<=m;i++)
	for (register int j=i+1;j<=m;j++)
		f[1][i][j]=a[1][i]+a[1][j];
	for (register int t=2;t<=n;t++) {
		for (register int i=0;i<=m+1;i++)
			f1[i]=f2[i]=f3[i]=f4[i]=inf;
		for (register int i=1;i<=m;i++) {
			for (register int j=i+1;j<=m;j++) {
				upd(f1[j],f[t-1&1][i][j]-(LL)K*i-(LL)K*j);upd(f1[j],f1[j-1]);
				f[t&1][i][j]=(LL)K*i+(LL)K*j+f1[j]+a[t][i]+a[t][j];
			}
			for (register int j=m;j>=i+1;j--) {
				upd(f2[j],f[t-1&1][i][j]-(LL)K*i+(LL)K*j);upd(f2[j],f2[j+1]);
				upd(f[t&1][i][j],(LL)K*i-(LL)K*j+f2[j]+a[t][i]+a[t][j]);
			}
		}
		for (register int i=m;i>=1;i--) {
			for (register int j=i+1;j<=m;j++) {
				upd(f3[j],f[t-1&1][i][j]+(LL)K*i-(LL)K*j);upd(f3[j],f3[j-1]);
				upd(f[t&1][i][j],-(LL)K*i+(LL)K*j+f3[j]+a[t][i]+a[t][j]);
			}
			for (register int j=m;j>=i+1;j--) {
				upd(f4[j],f[t-1&1][i][j]+(LL)K*i+(LL)K*j);upd(f4[j],f4[j+1]);
				upd(f[t&1][i][j],-(LL)K*i-(LL)K*j+f4[j]+a[t][i]+a[t][j]);
			}
		}
	}
	LL ans=inf;
	for (register int i=1;i<=m;i++)
	for (register int j=i+1;j<=m;j++)
		upd(ans,f[n&1][i][j]);
	printf("%lld\n",ans);
//	printf("%d\n",clock());
	return 0;
}	
