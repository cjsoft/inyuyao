
#include <bits/stdc++.h>
using namespace std;

const int N=30;
int n,k;
int l[N],r[N],s[N],q[N];
pair<int,int> t[N];
double pa[N],pb[N],line[N];

void dfs(int i,double p)
{
	if(p<1e-10)return ;
	if(i>n)
	{
		int j=1;
		for(i=1;i<=n;i++)t[i].first=-s[i],t[i].second=i;
		sort(t+1,t+1+n);
		line[-t[k].first]+=p;
		q[0]=0;
		for(i=1;i<=k;i++)q[++q[0]]=t[i].second;
		sort(q+1,q+1+k);
		for(i=1;i<=k;i++)
		    if(i%4<=1)pa[q[i]]+=p;
		    else pb[q[i]]+=p;
		return ;
	}
	for(int j=l[i];j<=r[i];j++)
	{
		s[i]=j;
		dfs(i+1,p/(1.0*(r[i]-l[i]+1)));
	}
}

int main()
{
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	scanf("%d",&n);
	int i;
	for(i=1;i<=n;i++)
	    scanf("%d",&l[i]);
	for(i=1;i<=n;i++)
	    scanf("%d",&r[i]);
	scanf("%d",&k);
	dfs(1,1.0);
	for(i=1;i<=n;i++)
	    printf("%.6lf %.6lf\n",pa[i],pb[i]);
	return 0;
}

