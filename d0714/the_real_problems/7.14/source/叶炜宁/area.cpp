#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
int n;
ll x[100010],y[100010],Mx1,Mx2,x2,y2,x3,y3,ans;
int main()
{
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld%lld",&x[i],&y[i]);
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++)
		{
			x2=x[j]-x[i];y2=y[j]-y[i];
			Mx1=0;Mx2=0;
			for (int k=1;k<=n;k++)
			{
				x3=x[k]-x[i];y3=y[k]-y[i];
				Mx1=max(Mx1,y3*x2-x3*y2);
				Mx2=max(Mx2,x3*y2-x2*y3);
			}
			ans=max(ans,Mx1+Mx2);
		}
	if (ans&1) printf("%lld.5\n",ans/2);else printf("%lld.0\n",ans/2);
}
