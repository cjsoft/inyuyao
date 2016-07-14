#include <algorithm>
#include <iostream>
#include <cstdio>
struct node { int x,y; } a[100005],b[100005];
int n,m;
long long ans1,ans2,ans;
inline node operator - (const node &x,const node &y)
{
	return (node){x.x-y.x,x.y-y.y};
}
inline long long operator * (const node &x,const node &y)
{
	return (long long)x.x*y.y-(long long)x.y*y.x;
}
inline bool cmp (const node &x,const node &y)
{
	return (x-a[1])*(y-a[1])>0;
}
inline void Graham()
{
	int t=1;
	for(int i=2;i<=n;i++)
		if(a[i].x<a[t].x||(a[i].x==a[t].x&&a[i].y<a[t].y)) t=i;
	if(t!=1) std::swap(a[1],a[t]);
	std::sort(a+2,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		while(m>1&&(a[i]-b[m-1])*(b[m]-b[m-1])>=0) m--;
		b[++m]=a[i];
	}
}
int main()
{
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i].x,&a[i].y);
	Graham();
	for(int i=1;i<=m;i++)
	{
		//printf("%d %d\n",b[i].x,b[i].y);
		for(int j=i;j<=m;j++)
		{
			ans1=b[i]*b[j];
			for(int t=j;t<=m;t++)
			{
				ans2=ans1+b[j]*b[t];
				for(int k=t;k<=m;k++)
				{
					//printf("%d %d %d %d %lld\n",i,j,t,k,ans2+b[t]*b[k]+b[k]*b[i]);
					ans=std::max(ans,ans2+b[t]*b[k]+b[k]*b[i]);
				}
			}
		}
	}
	printf("%lld",ans>>1);
	puts((ans&1)?".5":".0");
}
