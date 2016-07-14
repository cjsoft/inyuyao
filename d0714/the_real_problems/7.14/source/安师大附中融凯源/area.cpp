#include <stdio.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
typedef long long ll;
const int N=100005;
int n,st[N],top,up[N];
using namespace std;

struct node
{
	ll x,y;
}P[N];
bool cmp(node a,node b){return atan2(a.y-P[1].y,a.x-P[1].x)>atan2(b.y-P[1].y,b.x-P[1].x);}
node operator-(node a,node b){return (node){a.x-b.x,a.y-b.y};}
ll operator*(node a,node b){return a.x*b.y-a.y*b.x;}
void Hall_Convex()
{
	int i;
	for (i=2;i<=n;i++)
	if (P[i].y<P[1].y || (P[i].y==P[1].y && P[i].x<P[1].x)) swap(P[1],P[i]);
	sort(P+2,P+1+n,cmp);
	st[1]=1,st[2]=2,top=2;
	for (i=3;i<=n;i++)
	{
		while (top>1 && (P[st[top]]-P[st[top-1]])*(P[i]-P[st[top-1]])>0) top--;
		st[++top]=i;
	}
	while (top>1 && (P[st[top]]-P[st[top-1]])*(P[1]-P[st[top-1]])>0) top--;
}
void work1()
{
	if (top==3)
	{
		ll ans=(P[st[2]]-P[st[1]])*(P[st[3]]-P[st[1]]);
		printf ("%lld.%d",ans>>1,(ans&1)*5);
		return;
	}
	int i,j,x,y;
	ll ans=0,tmp;n=top;
	for (i=1;i<=n;i++) P[i]=P[st[i]];
	for (i=1;i<=n;i++) P[i+n]=P[i];
	for (i=1;i<=n;i++)
	{
		for (up[i+2]=i+1,j=i+3;j+1<n+i;j++)
		for (up[j]=up[j-1];up[j]+1<j && (P[up[j]+1]-P[j])*(P[i]-P[j])>(P[up[j]]-P[j])*(P[i]-P[j]);up[j]++);
		for (j=n+i-2,x=n+i-1;j-1>i;j--)
		{
			while (x-1>j && (P[i]-P[j])*(P[x-1]-P[j])>(P[i]-P[j])*(P[x]-P[j])) x--;
			ans=max(ans,(P[up[j]]-P[j])*(P[i]-P[j])+(P[i]-P[j])*(P[x]-P[j]));
		}
	}
	printf ("%lld.%d",ans>>1,(ans&1)*5);
}
int main()
{
	freopen ("area.in","r",stdin);
	freopen ("area.out","w",stdout);
	scanf ("%d",&n);
	int i;
	for (i=1;i<=n;i++) scanf ("%lld %lld",&P[i].x,&P[i].y);
	Hall_Convex();
	work1();
	return 0;
}

