#include <stdio.h>
#include <iostream>
#include <cstring>
#include <algorithm>
const double eps=1e-10;
const int N=30;
int n,k,l[N],r[N],sc[N],id[N];
double ans[2][N];
using namespace std;

bool cmp(int a,int b)
{
	if (sc[a]==sc[b]) return a<b;
	return sc[a]>sc[b];
}
void test()
{
	int i;
	for (i=1;i<=n;i++) id[i]=i;
	sort(id+1,id+1+n,cmp);
	sort(id+1,id+1+k);
	for (i=1;i<=k;i++) ans[(i%4)>>1][id[i]]+=1.0;
}
void dfs(int i)
{
	if (i>n){test();return;}
	int j;
	for (j=l[i];j<=r[i];j++)
	sc[i]=j,dfs(i+1),sc[i]=0;
}
int main()
{
	freopen ("assign.in","r",stdin);
	freopen ("assign.out","w",stdout);
	scanf ("%d",&n);
	int i,ard,j,sum=0,x,y;
	for (i=1;i<=n;i++) scanf ("%d",&l[i]);
	for (i=1;i<=n;i++) scanf ("%d",&r[i]);
	scanf ("%d",&k);
	dfs(1);
	double mul=1.0;
	for (i=1;i<=n;i++) mul*=(r[i]-l[i]+1);
	for (i=1;i<=n;i++) printf ("%.6lf %.6lf\n",ans[0][i]/mul,ans[1][i]/mul);
	return 0;
}

