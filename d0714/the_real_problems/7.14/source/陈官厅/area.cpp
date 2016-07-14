#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 505
using namespace std;
typedef long long ll;
ll n,i,j,sum1,sum2,ans,k,x;
struct data{
	ll x,y;
}a[N];
data operator - (data x,data y)
{
	return (data){y.x-x.x,y.y-x.y};
}
ll operator * (data x,data y)
{
	return x.x*y.y-x.y*y.x;
}
int main()
{
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	scanf("%lld",&n);
	for (i=1;i<=n;i++)
		scanf("%lld%lld",&a[i].x,&a[i].y);
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
		{
			sum1=0;sum2=0;
			for (k=1;k<=n;k++)
			{
				x=(a[i]-a[j])*(a[k]-a[j]);
				sum1=max(sum1,x);
				sum2=max(sum2,-x);
			}
			//printf("%lld %lld\n",sum1,sum2);
			ans=max(ans,sum1+sum2);
		}
	printf("%lld",ans/2);
	if (ans&1)puts(".5");else puts(".0");
}