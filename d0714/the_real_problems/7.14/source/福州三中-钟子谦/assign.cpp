#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;
int n,l[233],r[233],K,cs[233],tot=0,A[233],B[233];
pii gs[233];
bool cmpb(pii a,pii b) {return a.second<b.second;}
void chk()
{
	for(int i=1;i<=n;i++) gs[i]=pii(-cs[i],i);
	sort(gs+1,gs+1+n);
	sort(gs+1,gs+1+K,cmpb);
	int p=0;
	for(int i=1;i<=K;i++)
	{
		int g=gs[i].second; p=(p+1)&3;
		if(p<=1) A[g]++; else B[g]++;
	}
	tot++;
}
void dfs(int d)
{
	if(d>n) {chk(); return;}
	for(int i=l[d];i<=r[d];i++)
	{
		cs[d]=i; dfs(d+1);
	}
}
void force()
{
	dfs(1);
	for(int i=1;i<=n;i++)
	printf("%.6lf %.6lf\n",double(A[i])/tot,(double)B[i]/tot);
}
int main()
{
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	scanf("%d",&n);
	double aa=1;
	for(int i=1;i<=n;i++) scanf("%d",l+i);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",r+i);
		aa*=r[i]-l[i]+1;
	}
	scanf("%d",&K);
	if(aa<2333333)
	{
		force();
		return 0;
	}
}
