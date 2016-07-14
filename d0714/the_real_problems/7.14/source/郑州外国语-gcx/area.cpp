#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define eps 1e-8

using namespace std;

const int N=100005;
struct P{
	double x,y,ang;
};
struct L{
	P a,b;
};
bool operator <(P a,P b)
{
	if(a.ang==b.ang) return a.x<b.x;
	return a.ang<b.ang; 
}
P operator -(P a,P b)
{
	a.x-=b.x;a.y-=b.y;
	return a;
}
P operator +(P a,P b)
{
	a.x+=b.x;a.y+=b.y;
	return a;
}
double operator *(P a,P b)
{
	return a.x*b.y-a.y*b.x;
}

int n,topt;
P di[N],tb[N];

double ans=0;

void solve()
{
	for(int i=1;i<=topt;++i)
	{
		if(i==2)
			int aaa=1;
		int t1=i+1,t2=(i+2)%topt+1;
		for(int j=i+2;j<=topt;++j)
		{
			while((tb[t1]-tb[i])*(tb[j]-tb[i])-(tb[t1+1]-tb[i])*(tb[j]-tb[i])<eps&&t1<=j) t1++;
			while((tb[j]-tb[i])*(tb[t2]-tb[i])-(tb[j]-tb[i])*(tb[t2%topt+1]-tb[i])<eps&&(t2%topt+1)!=i) t2=t2%topt+1;
			ans=max(ans,(tb[t1]-tb[i])*(tb[j]-tb[i])/2+(tb[j]-tb[i])*(tb[t2]-tb[i])/2);
			
		}
	}
	return ;
}


int main()
{
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	scanf("%d",&n);
	if(n<=2)
	{
		printf("0.0");
		return 0;
	}
	for(int i=1;i<=n;++i)
		scanf("%lf%lf",&di[i].x,&di[i].y);
	for(int i=2;i<=n;++i)
		if(di[i].x<di[1].x||(di[i].x==di[1].x&&di[i].y<di[1].y))
			swap(di[i],di[1]);
	for(int i=2;i<=n;++i)
		di[i].ang=atan2(di[i].y-di[1].y,di[i].x-di[1].x);
	sort(di+2,di+n+1);
	tb[1]=di[1];topt=1;
	for(int i=2;i<=n;++i)
	{
	//	while(topt>1&&tb[i].ang==di[i].ang) topt--;
		if(di[i].x==tb[topt].x&&di[i].y==tb[topt].y) continue;
		while(topt>1&&(tb[topt]-tb[topt-1])*(di[i]-tb[topt-1])<-eps) topt--;
		tb[++topt]=di[i];
	}
	while(topt>1&&(tb[topt]-tb[topt-1])*(tb[1]-tb[topt-1])<-eps) topt--;
	if(topt==3)
	{
		printf("%.1lf",(tb[2]-tb[1])*(tb[3]-tb[1])/2);
		return 0;
	}	
	solve();
	printf("%.1lf",ans);
	return 0;
}

