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

int ch[5];
void cal()
{
	for(int i=1;i<=3;++i)
		if(((tb[i]-tb[4])*(tb[i%3+1]-tb[4]))*((tb[i]-tb[4])*(tb[(i+1)%3+1]-tb[4]))<0)
		{
			ans=max(ans,abs((tb[i%3+1]-tb[4])*(tb[i]-tb[4])/2+(tb[i]-tb[4])*(tb[(i+1)%3+1]-tb[4])/2));
		}
	if(ans>5417)
		int aaa=1;
}
void cal2()
{
	ans=max(ans,abs((tb[2]-tb[1])*(tb[3]-tb[1])/2));
	return;
}
void dfs(int wz)
{
	if(wz==4) cal2();
	if(wz>4) 
	{
		cal();
		return ;
	}
	for(int i=ch[wz-1]+1;i<=n;++i)
	{
		ch[wz]=i;tb[wz]=di[i];
		dfs(wz+1);
	}
}


int main()
{
	freopen("area.in","r",stdin);
	freopen("area1.out","w",stdout);
	scanf("%d",&n);
	if(n<=2)
	{
		printf("0.0");
		return 0;
	}
	for(int i=1;i<=n;++i)
		scanf("%lf%lf",&di[i].x,&di[i].y);
	dfs(1);
	printf("%.1lf",ans);
	return 0;
}

