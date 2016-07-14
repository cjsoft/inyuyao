#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
using namespace std;
int l[30],r[30],n,m,i,N,s[30][2],a[30],b[30];
inline bool cmp(int x,int y)
{
	if(a[x]==a[y])return x<y;
	return a[x]>a[y];
}
void dfs(int x)
{
	int i;
	if(x>n)
	{
		N++;
		for(i=1;i<=n;i++)b[i]=i;
		sort(b+1,b+n+1,cmp);
		sort(b+1,b+m+1);
		for(i=1;i<=m;i++)s[b[i]][i>>1&1]++;
		return;
	}
	for(i=l[x];i<=r[x];i++)
	{
		a[x]=i;
		dfs(x+1);
	}
}
int main()
{
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d",l+i);
	for(i=1;i<=n;i++)scanf("%d",r+i);
	scanf("%d",&m);
	dfs(1);
	for(i=1;i<=n;i++)printf("%.6lf %.6lf\n",(double)s[i][0]/N,(double)s[i][1]/N);
	return 0;
}

