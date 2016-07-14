#include<algorithm>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include  <stdio.h>
#include   <time.h>
#include   <math.h>
#include   <bitset>
#include   <vector>
#include    <queue>
#include      <set>
#include      <map>
using namespace std;

typedef long long LL;
const int N=200005;

int n,m;
LL Ans;

struct point
{
	int x,y;
	
	inline void input()
	{
		scanf("%d%d",&x,&y);
	}
	
	inline void output()
	{
		printf("%d %d\n",x,y);
	}
	
	inline LL dis()
	{
		return (LL)x*x+(LL)y*y;
	}
	
	inline point(int x=0,int y=0):x(x),y(y){}
}p[N],q[N];

inline point operator-(const point &a,const point &b)
{
	return point(a.x-b.x,a.y-b.y);
}

inline LL operator*(const point &a,const point &b)
{
	return (LL)a.x*b.y-(LL)a.y*b.x;
}

inline bool cmp(const point &a,const point &b)
{
	LL t=(a-p[1])*(b-p[1]);
	return t==0?(a-p[1]).dis()<(b-p[1]).dis():t>0;
}

void Graham()
{
	int pos=1;
	for(int i=2;i<=n;i++)
		if(p[i].x<p[pos].x||p[i].x==p[pos].x&&p[i].y<p[pos].y)
			pos=i;
	swap(p[1],p[pos]);sort(p+2,p+n+1,cmp);
	q[m=1]=p[1];
	for(int i=2;i<=n;i++)
	{
		while(m>1&&(p[i]-q[m-1])*(q[m]-q[m-1])>=0)
			m--;
		q[++m]=p[i];
	}
}

inline LL Abs(LL a)
{
	return a<0?-a:a;
}

inline LL solve(int l,int r)
{
	point p1=p[l],p2=p[r];LL Max=0;
	while(l<r-5)
	{
		int m1=l+(r-l)/3,m2=l+(r-l)/3*2;
		LL v1=Abs((p2-p1)*(p[m1]-p1)),v2=Abs((p2-p1)*(p[m2]-p1));Max=max(Max,max(v1,v2));
		if(v1<v2)
			l=m1+1;
		else
			r=m2-1;
	}
	while(l<=r)
		Max=max(Max,Abs((p2-p1)*(p[l]-p1))),l++;
	return Max;
}

inline LL area(int l,int r)
{
	return solve(l,r)+solve(r,l+m);
}

inline void out(LL x)
{
	printf("%lld",x/2);
	if(x&1)
		puts(".5");
	else
		puts(".0");
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		p[i].input();
	if(n<3)
		puts("0.0"),exit(0);
	Graham();
	if(m==3)
		out(Abs((q[2]-q[1])*(q[3]-q[1]))),exit(0);
	q[0]=q[m];
	for(int i=1;i<=m+m;i++)
		p[i]=q[i%m];
	int Now=1;
	for(int i=1;i<=m;i++)
	{
		if(Now<i)
			Now=i;
		LL val=area(i,Now);
		while(Now<i+m)
		{
			LL v=area(i,Now+1);
			if(v>val)
				val=v,Now++;
			else
				break;
		}
		Ans=max(Ans,val);
	}
	out(Ans);
	return 0;
}
