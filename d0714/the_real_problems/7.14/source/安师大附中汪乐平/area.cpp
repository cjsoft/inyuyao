#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
using namespace std;
#define MAXN 100005
#define ll long long
ll ans,A,B,C;
int xx,yy,n,i,j,t,he1,ta1,he2,ta2;
struct node
{
	int x,y;
	node(int _x=0,int _y=0)
	{
		x=_x;
		y=_y;
	}
	node operator+(node b)
	{
		return node(x+b.x,y+b.y);
	}
	node operator-(node b)
	{
		return node(x-b.x,y-b.y);
	}
	ll operator*(node b)
	{
		return (ll)x*b.y-(ll)y*b.x;
	}
	bool operator<(node b)const
	{
		ll a=(ll)(y-yy)*(b.x-xx)-(ll)(x-xx)*(b.y-yy);
		if(a)return a>0;
		if(x==xx)return y<b.y;
		if(y<yy)return x>b.x;
		return x<b.x;
	}
	bool operator==(node b)
	{
		return x==b.x&&y==b.y;
	}
	ll get()
	{
		return A*x+B*y+C;
	}
}a[MAXN],s[MAXN],a1[MAXN<<1],a2[MAXN<<1],X,Y;
bool check(node a,node b,node c)
{
	return (b-a)*(c-b)>=0;
}
ll dis(node a,node b)
{
	return (ll)(a.x-b.x)*(a.x-b.x)+(ll)(a.y-b.y)*(a.y-b.y);
}
ll ABS(ll x)
{
	if(x<0)return -x;
	return x;
}
void fix(node a,node b)
{
	A=a.y-b.y;
	B=b.x-a.x;
	C=a*b;
	int i,j,l,r,m1,m2;
	l=he1;
	r=ta1-1;
	while(l+2<r)
	{
		m1=(l*2+r)/3;
		m2=(l+r*2)/3;
		if(a1[m1].get()<a1[m2].get())r=m2;
		else l=m1;
	}
	for(i=j=l;i<=r;i++)if(a1[i].get()<a1[j].get())j=i;
	if(a1[j]==a||a1[j]==b)return;
	X=a1[j];
	l=he2;
	r=ta2-1;
	while(l+2<r)
	{
		m1=(l*2+r)/3;
		m2=(l+r*2)/3;
		if(a2[m1].get()>a2[m2].get())r=m2;
		else l=m1;
	}
	for(i=j=l;i<=r;i++)if(a2[i].get()>a2[j].get())j=i;
	if(a2[j]==a||a2[j]==b)return;
	Y=a2[j];
	ans=max(ans,ABS((X-a)*(b-a)+(b-a)*(Y-a)));
}
int main()
{
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d%d",&a[i].x,&a[i].y);
	for(i=j=1;i<=n;i++)if(a[i].x<a[j].x||a[i].x==a[j].x&&a[i].y<a[j].y)j=i;
	swap(a[j],a[1]);
	xx=a[1].x;
	yy=a[1].y;
	sort(a+2,a+n+1);
	a[n+1]=a[1];
	for(i=1;i<=n+1;i++)
	{
		while(t>1&&check(s[t-1],s[t],a[i]))t--;
		s[++t]=a[i];
	}
	t--;
	if(t==3)
	{
		ans=ABS((s[3]-s[1])*(s[2]-s[1]));
		cout<<(ans>>1)<<'.'<<((ans&1)?'5':'0')<<endl;
		return 0;
	}
	for(i=1;i<=t;i++)a1[i]=s[i];
	he1=1;
	ta1=t+1;
	he2=ta2=1;
	for(i=j=1;i<=t;i++)
	{
		for(;dis(s[i],s[j%t+1])>=dis(s[i],s[j]);j=j%t+1)
		{
			a2[ta2++]=s[j];
			he1++;
			fix(s[i],s[j]);
		}
		fix(s[i],s[j]);
		a1[ta1++]=s[i];
		he2++;
	}
	cout<<(ans>>1)<<'.'<<((ans&1)?'5':'0')<<endl;
	return 0;
}

