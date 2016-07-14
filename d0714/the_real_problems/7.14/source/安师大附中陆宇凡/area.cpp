#include<cmath>
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;

int N,i,j,tt,o,p;
long long ss,ans,mx[4005][4005];

struct Dian
{
	long long x,y;
//	double alpha;
//	Dian(const double &_x,const double &_y){x=_x,y=_y,alpha=atan2(y,x);}
	long long operator * (const Dian &o)const{return o.y*x-o.x*y;}
	bool operator < (const Dian &o)const
	{
		if(y==o.y)return x<o.x?1:0;
		return y<o.y?1:0;
	}
}L[100005],list[200005],X,Y;

int cmp(const void *a,const void *b)
{
	Dian X=*(Dian *)a;
	Dian Y=*(Dian *)b;
	long long xx1=X.x-L[1].x,yy1=X.y-L[1].y;
	long long xx2=Y.x-L[1].x,yy2=Y.y-L[1].y;
	long long t=yy2*xx1-yy1*xx2;
	if(t==0)return X.x<Y.x?-1:1;
	return t>0?-1:1;
}

int main()
{
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	scanf("%d",&N);
	for(i=1;i<=N;i++)
		scanf("%lld %lld",&L[i].x,&L[i].y);
	sort(L+1,L+N+1);tt=0;
//	for(i=1;i<=N;i++)
//		printf("%d %d\n",L[i].x,L[i].y);
	qsort(L+2,N-1,sizeof(L[0]),cmp);
//	for(i=1;i<=N;i++)
//		printf("%lld %lld\n",L[i].x,L[i].y);
	list[++tt]=L[1],list[++tt]=L[2];
	for(i=3;i<=N;i++)
	{
		do
		{
			X.x=L[i].x-list[tt-1].x;X.y=L[i].y-list[tt-1].y;
			Y.x=list[tt].x-list[tt-1].x;Y.y=list[tt].y-list[tt-1].y;
			if(Y*X<=0)tt--;
			else break;
		}
		while(tt>1);
		list[++tt]=L[i];
	}
//	list[++tt]
	if(tt<=4)
	{
		ss=0.0;
		for(i=3;i<=tt;i++)
		{
			X.x=list[i].x-list[1].x;X.y=list[i].y-list[1].y;
			Y.x=list[i-1].x-list[1].x;Y.y=list[i-1].y-list[1].y;
			ss+=Y*X;
		}
		if(ss%2ll)printf("%lld.5\n",ss/2ll);
		else printf("%lld.0\n",ss/2ll);
		return 0;
	}
	for(i=1;i<=tt-3;i++)
	{
		for(j=i+2;j<=tt-1;j++)
		{
			for(o=j+1;o<=tt;o++)
			{
				X.x=list[o].x-list[i].x;X.y=list[o].y-list[i].y;
				Y.x=list[j].x-list[i].x;Y.y=list[j].y-list[i].y;
				mx[i][j]=max(mx[i][j],Y*X);
			}
		}
	}
	for(i=1;i<=tt-3;i++)
	{
		for(j=i+1;j<=tt-2;j++)
		{
			for(o=j+1;o<=tt-1;o++)
			{
				X.x=list[o].x-list[i].x;X.y=list[o].y-list[i].y;
				Y.x=list[j].x-list[i].x;Y.y=list[j].y-list[i].y;
				ans=max(ans,Y*X+mx[i][o]);
			}
		}
	}
	if(ans%2ll)printf("%lld.5\n",ans/2ll);
	else printf("%lld.0\n",ans/2ll);
	return 0;
}
