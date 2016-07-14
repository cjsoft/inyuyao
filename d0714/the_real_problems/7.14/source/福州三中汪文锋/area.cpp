#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<queue>
#include<time.h>
#include<algorithm>
#include<math.h>
#include<iomanip>
using namespace std;
typedef long long ll;
typedef long double ld;
struct dd
{
	int id;
	ll x,y;
}p[100051],q[100051];
int pp=1;
dd C;
int n;
ll len(dd a,dd b)
{return (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y);}
ll cross(dd a,dd b,dd c)
{return (b.y-a.y)*(c.x-a.x)-(b.x-a.x)*(c.y-a.y);}
ll abs(ld a)
{if(a<0)return -a;else return a;}
bool cmp(dd a,dd b){if(cross(C,a,b)==0)return len(a,C)<len(b,C);else return cross(C,a,b)>0;}
void init_30()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		ll x,y;
		cin>>x>>y;
		p[i].x=x;p[i].y=y;
		p[i].id=i;
		if(p[i].x<p[pp].x||(p[i].x==p[pp].x&&p[i].y<p[pp].y))pp=i;
    }
    C=p[pp];
    sort(p+1,p+n+1,cmp);
    q[1]=p[1];q[2]=p[2];
    int r=2;
    for(int i=3;i<=n;i++)
    {
    	while(cross(q[r-1],q[r],p[i])<0&&r>1)r--;
    	q[++r]=p[i];
    }
    ll ans=0;
    if(r==3)
      printf("%.1lf\n",abs(cross(q[1],q[2],q[3]))/2.0);
    else
    {
      for(int i=1;i<=r;i++)
      {
    	  int L=i%r+1,R;
    	  ld maxx=0.0;
    	  for(int j=(i+2)%r+1;j!=i;j=j%r+1)
    	    if(abs(cross(q[i],q[(i+1)%r+1],q[j]))>maxx)
    	    {maxx=abs(cross(q[i],q[(i+1)%r+1],q[j]));R=j;}
    	  for(int j=1,k=(i+1)%r+1;j<=r-3;j++,k=k%r+1)
    	  {
    		  while(abs(cross(q[i],q[k],q[L]))<=abs(cross(q[i],q[k],q[L%r+1])))L=L%r+1;
    		  while(abs(cross(q[i],q[k],q[R]))<=abs(cross(q[i],q[k],q[R%r+1])))R=R%r+1;
    		  if(ans<abs(cross(q[i],q[k],q[L]))+abs(cross(q[i],q[k],q[R])))
			  ans=abs(cross(q[i],q[k],q[L]))+abs(cross(q[i],q[k],q[R]));		
    	  }  	
      }
      if(ans%2==1)
        cout<<ans/2<<".5"<<endl;
      else
        cout<<ans/2<<".0"<<endl;
    }
}
void init_50()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		ll x,y;
		cin>>x>>y;
		p[i].x=x;p[i].y=y;
		p[i].id=i;
		if(p[i].x<p[pp].x||(p[i].x==p[pp].x&&p[i].y<p[pp].y))pp=i;
    }
    C=p[pp];
    sort(p+1,p+n+1,cmp);
    q[1]=p[1];q[2]=p[2];
    int r=2;
    for(int i=3;i<=n;i++)
    {
    	while(cross(q[r-1],q[r],p[i])<0&&r>1)r--;
    	q[++r]=p[i];
    }
    ll ans=0;
    if(r==3)
      printf("%.1lf\n",abs(cross(q[1],q[2],q[3]))/2.0);
    else
    {
      int LL=2%r+1;
      for(int i=1;i<=r;i++)
      {
    	  int L=i%r+1,R;
    	  ll maxx=0.0,minn=0.0;
    	  for(int j=(i+2)%r+1;j!=i;j=j%r+1)
    	    if(abs(cross(q[i],q[(i+1)%r+1],q[j]))>maxx)
    	    {maxx=abs(cross(q[i],q[(i+1)%r+1],q[j]));R=j;}
    	  int lastLL=LL;   
    	  for(int k=LL;k!=(i+r-3)%r+1;k=k%r+1)
    	  {
    		  while(abs(cross(q[i],q[k],q[L]))<=abs(cross(q[i],q[k],q[L%r+1])))L=L%r+1;
    		  while(abs(cross(q[i],q[k],q[R]))<=abs(cross(q[i],q[k],q[R%r+1])))R=R%r+1;
    		  if(len(q[i],q[k])>minn){minn=len(q[i],q[k]);LL=k;}
    		  if(ans<abs(cross(q[i],q[k],q[L]))+abs(cross(q[i],q[k],q[R])))
			  ans=abs(cross(q[i],q[k],q[L]))+abs(cross(q[i],q[k],q[R]));		
    	  }  	
    	  if(LL==lastLL)LL=LL%r+1;
      }
      if(ans%2==1)
        cout<<ans/2<<".5"<<endl;
      else
        cout<<ans/2<<".0"<<endl;
    }
}
void init()
{
	if(n<=500)
	  init_30();
	else
	  init_50();
}
int main()
{
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	init();
	return 0;
}
