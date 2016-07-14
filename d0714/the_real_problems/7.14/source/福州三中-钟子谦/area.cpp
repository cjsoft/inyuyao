#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <algorithm>
using namespace std;
typedef double ld;
typedef long long ll;
struct pnt {ll x,y; ld at; pnt() {} pnt(ld a,ld b) {x=a; y=b;}};
ll operator * (pnt a,pnt b)
{
	return a.x*b.y-a.y*b.x;
}
pnt operator - (pnt a,pnt b)
{
	return pnt(a.x-b.x,a.y-b.y);
}
ll disp(pnt x)
{
	return x.x*x.x+x.y*x.y;
}
ld ang(pnt x) {return atan2(x.y,x.x);}
ld eps=1e-8;
int dcmp(ld x)
{
	if(x>eps) return 1;
	if(x<-eps) return -1;
	return 0;
}
pnt yd;
bool cmpjj(pnt a,pnt b)
{
	if(dcmp(a.at-b.at)) return a.at<b.at;
	return disp(a-yd)<disp(b-yd);
}
bool cmpyx(pnt a,pnt b)
{
	if(dcmp(a.y-b.y)) return a.y<b.y;
	return a.x<b.x;
}
ll Abs(ll x) {return (x>=0)?x:(-x);}
ll area(pnt a,pnt b,pnt c,pnt d)
{
	return Abs(a*b+b*c+c*d+d*a); //need to /2
}
int n;
int np(int x) {return (x+1)%n;}
pnt ps[233333];
void moved(int a,int b,int c,int& d)
{
	if(np(d)==c) d=c;
	while(area(ps[a],ps[b],ps[c],ps[d])<area(ps[a],ps[b],ps[c],ps[np(d)]))
	d=np(d);
}
void movecd(int a,int b,int& c,int& d)
{
	if(np(c)==b) c=b;
	if(np(d)==b) d=b;
	int td=d;
	while(moved(a,b,np(c),td),
	area(ps[a],ps[b],ps[c],ps[d])<area(ps[a],ps[b],ps[np(c)],ps[td]))
	c=np(c), d=td;
}
void movebcd(int a,int& b,int& c,int& d)
{
	if(np(b)==a) b=a;
	if(np(c)==a) c=a;
	if(np(d)==a) d=a;
	int tc=c,td=d;
	while(movecd(a,np(b),tc,td),
	area(ps[a],ps[b],ps[c],ps[d])<area(ps[a],ps[np(b)],ps[tc],ps[td]))
	b=np(b), c=tc, d=td;
}
pnt ss[233333];
int sn=0;
void graham()
{
	ss[sn++]=ps[0];
	ss[sn++]=ps[1];
	for(int i=2;i<n;i++)
	{
		while(sn>=2&&(ps[i]-ss[sn-1])*(ss[sn-1]-ss[sn-2])>=0) --sn;
		ss[sn++]=ps[i];
	}
}
int gii()
{
	int a=0; char c;
	while(c=getchar(),c<'0'||c>'9');
	a=c-48;
	while(c=getchar(),c>='0'&&c<='9') a=a*10+c-48;
	return a;
}
#define gi gii()
int main()
{
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	n=gi;
	if(n<=2) {puts("0.0"); return 0;}
	for(int i=0;i<n;i++)
	{
		int x=gi,y=gi;
		ps[i]=pnt(x,y);
	}
	sort(ps,ps+n,cmpyx);
	yd=ps[0];
	for(int i=1;i<n;i++) ps[i].at=ang(ps[i]-yd);
	sort(ps+1,ps+n,cmpjj);
	graham();
	n=sn;
	for(int i=0;i<n;i++) ps[i]=ss[i];
	int b=0,c=0,d=0;
	ll ans=0;
	for(int i=0;i<n;i++)
	{
		movebcd(i,b,c,d);
		ans=max(ans,area(ps[i],ps[b],ps[c],ps[d]));
	}
	cout<<ans/2<<"."<<ans%2*5<<"\n";
}
