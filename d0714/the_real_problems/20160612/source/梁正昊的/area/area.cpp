#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

#define fo(i,a,b) for (int i=a;i<=b;i++)
#define fd(i,a,b) for (int i=a;i>=b;i--)
	
typedef long long ll;

const int maxn=110000;

struct node{int x,y;} p[maxn];

int n;
double tmp,ans;

bool cmp(node a,node b) {return 1LL*a.y*b.x-1LL*b.y*a.x<0;}

double calc(node a,node b,node c)
{
	double A=sqrt(1LL*(a.x-b.x)*(a.x-b.x)+1LL*(a.y-b.y)*(a.y-b.y));
	double B=sqrt(1LL*(a.x-c.x)*(a.x-c.x)+1LL*(a.y-c.y)*(a.y-c.y));
	double C=sqrt(1LL*(c.x-b.x)*(c.x-b.x)+1LL*(c.y-b.y)*(c.y-b.y));
	double P=(A+B+C)/2;
	return sqrt(P*(P-A)*(P-B)*(P-C));
}

int main()
{
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	scanf("%d",&n);
	fo(i,1,n)
	{
		scanf("%d%d",&p[i].x,&p[i].y);
		p[i].x++;
		p[i].y++;
	}
	sort(p+1,p+1+n,cmp);
	if (n==3)
	{
		printf(".1lf\n",calc(p[1],p[2],p[3]));
		return 0;
	}
	fo(a,1,n)
		fo(b,a+1,n)	
			fo(c,b+1,n)	
				if (tmp=calc(p[a],p[b],p[c])<ans) 
					fo(d,c+1,n)
						ans=max(ans,tmp+min(calc(p[a],p[b],p[d]),min(calc(p[a],p[c],p[d]),calc(p[b],p[c],p[d]))));
	printf("%lf\n",ans);			
}