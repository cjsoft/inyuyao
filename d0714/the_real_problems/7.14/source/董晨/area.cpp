#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define N 200005
int n,m,l,t;
int x[N],y[N];
double s1,s2,ans;
int main(){
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)scanf("%d%d",&x[i],&y[i]);
	for (int i=1;i<n;i++)
		for (int j=i+1;j<=n;j++){
			double k=(double)(y[j]-y[i])/(x[j]-x[i]);
			double x1=x[j]-x[i],y1=y[j]-y[i];
			s1=s2=0;
			for (int l=1;l<=n;l++){
				double t=(x[l]-x[i])*k+y[i];
				double x2=x[l]-x[i],y2=y[l]-y[i];
				if(t>=y[l])s1=max(s1,x1*x2-y1*y2);
					else s2=max(s2,x1*x2-y1*y2);
			}
			ans=max(ans,s1+s2);
		}
	printf("%.1f\n",ans);
}