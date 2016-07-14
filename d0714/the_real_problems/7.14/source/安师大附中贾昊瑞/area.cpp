#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<memory.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<queue>
#include<map>
#include<set>
#include<list>
#include<deque>
#include<vector>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define F(i,j,n) for(register int i=j;i<=n;i++)
#define D(i,j,n) for(register int i=j;i>=n;i--)
#define ll long long
using namespace std;
void in(int&a);void in(ll&a);
struct point{
	int x,y;
}a[100010];
int n;double ans,p,q,d,l,s,A,C;
int main()
{
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	in(n);F(i,1,n)in(a[i].x),in(a[i].y);
	F(i,1,n)F(j,i+1,n)if(i^j)
	if(a[i].x==a[j].x){
		p=q=0;
	d=sqrt((double)(a[i].x-a[j].x)*(a[i].x-a[j].x)+(double)(a[i].y-a[j].y)*(a[i].y-a[j].y));
	F(k,1,n)if(k^i&&k^j)
	if(a[k].x<a[i].x)p=max(p,(a[i].x-a[k].x)*d);
	else q=max(q,(a[k].x-a[i].x)*d);
	ans=max(ans,p+q);
//	printf("\n1:%d %d %.1lf %.1lf %.1lf\n",i,j,p,q,ans/2);
	}
	else
	if(a[i].y==a[j].y){
		p=q=0;
	d=sqrt((double)(a[i].x-a[j].x)*(a[i].x-a[j].x)+(double)(a[i].y-a[j].y)*(a[i].y-a[j].y));
	F(k,1,n)if(k^i&&k^j)
	if(a[k].y<a[i].y)p=max(p,(a[i].y-a[k].y)*d);
	else q=max(q,(a[k].y-a[i].y)*d);
	ans=max(ans,p+q);
//	printf("\n2:%d %d %.1lf %.1lf %.1lf\n",i,j,p,q,ans/2);
	}
	else{
	p=q=0;
	d=sqrt((double)(a[i].x-a[j].x)*(a[i].x-a[j].x)+(double)(a[i].y-a[j].y)*(a[i].y-a[j].y));
	A=(double)(a[j].y-a[i].y)/(a[i].x-a[j].x);C=-A*a[i].x-a[i].y;s=sqrt(A*A+1);
	F(k,1,n)if(k^i&&k^j){
	l=(A*a[k].x+a[k].y+C)/s;
	p=max(p,l*d);
	q=max(q,-l*d);
//	printf("%d %d %d:%.4lf %.4lf %.1lf\n",i,j,k,l,d,l*d);
	}
	ans=max(ans,p+q);
//	printf("\n3:%d %d %.1lf %.1lf %.1lf\n",i,j,p,q,ans/2);
	}
	printf("%.1lf\n",ans/2);
	return 0;
}
void in(ll&a){register char c;register bool y=false;c=getchar();a=0;
while(c<'0'||c>'9'){if(c=='-'){c=getchar();y=true;break;}c=getchar();}
while(c>='0'&&c<='9'){a=(a<<3)+(a<<1)+c-'0';c=getchar();}if(y)a=-a;}
void in(int&a){register char c;register bool y=false;c=getchar();a=0;
while(c<'0'||c>'9'){if(c=='-'){c=getchar();y=true;break;}c=getchar();}
while(c>='0'&&c<='9'){a=(a<<3)+(a<<1)+c-'0';c=getchar();}if(y)a=-a;}
