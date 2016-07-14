#include <bits/stdc++.h>
using namespace std;

const int N=100005;
int n;
long long x[N],y[N],ans;

long long cha(long long a,long long b,long long c,long long d)
{
	return a*d-b*c;
}

long long sq(int i,int j,int k)
{
	return cha(x[j]-x[i],y[j]-y[i],x[k]-x[i],y[k]-y[i]);
}

int main()
{
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	cin>>n;
	int i,j,k,l;
	for(i=1;i<=n;i++)scanf("%lld%lld",&x[i],&y[i]);
	for(i=1;i<=n;i++)
	    for(j=1;j<=n;j++)
	        for(k=1;k<=n;k++)
	            for(l=1;l<=n;l++)
	            {
	               if(i==j||j==k||k==l||j==l)continue;
	                ans=max(ans,sq(i,j,k)+sq(i,j,l));
	            }
	for(i=1;i<=n;i++)
	    for(j=1;j<=n;j++)
	        for(k=1;k<=n;k++)
	                ans=max(ans,sq(i,j,k));
	printf("%.1lf",ans/2.0);
}
