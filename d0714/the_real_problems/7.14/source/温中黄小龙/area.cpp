#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define next(i) ((i)==tot-1?0:(i)+1)
#define MAXN 101001

struct Point{
	ll x,y;
	Point(){}
	Point(ll _x,ll _y){x=_x;y=_y;}
	void scan(){scanf("%I64d%I64d",&x,&y);}
	Point operator-(Point p2){return Point(x-p2.x,y-p2.y);}
}ps[MAXN];
int by_x(Point p1,Point p2){return p1.x<p2.x;}
ll cross(Point p1,Point p2){return p1.x*p2.y-p1.y*p2.x;}
ll S(Point p1,Point p2,Point p3){return abs(cross(p1-p2,p1-p3));}
Point st1[MAXN],st2[MAXN];
int tp1,tp2,tot;
Point hull[MAXN];

int main(){
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;++i)
		ps[i].scan();
	sort(ps+1,ps+1+n,by_x);
	for(int i=1;i<=n;++i){
		while(tp1>1&&cross(st1[tp1]-st1[tp1-1],ps[i]-st1[tp1-1])<=0)--tp1;
		while(tp2>1&&cross(st2[tp2]-st2[tp2-1],ps[i]-st2[tp2-1])>=0)--tp2;
		st1[++tp1]=st2[++tp2]=ps[i];
	}
	for(int i=1;i<tp1;++i)hull[tot++]=st1[i];
	for(int i=tp2;i>1;--i)hull[tot++]=st2[i];
	if(tot<4){
		if(tot<=2)printf("0.0\n");
		else{
			ll ans=S(ps[1],ps[2],ps[3]);
			if(ans&1)printf("%I64d.5",ans/2);
			else printf("%I64d.0",ans/2);
		}
		return 0;
	}
	ll ans=0;
	for(int i=0,p1=1,j=2,p2=3,cnt=0;cnt<=3*tot;++cnt){
		while(p1!=j&&S(hull[i],hull[j],hull[p1])<=S(hull[i],hull[j],hull[next(p1)]))p1=next(p1);
		while(p2!=i&&S(hull[i],hull[j],hull[p2])<=S(hull[i],hull[j],hull[next(p2)]))p2=next(p2);
		ans=max(ans,S(hull[i],hull[p1],hull[j])+S(hull[i],hull[p2],hull[j]));
		if(cross(hull[next(i)]-hull[i],hull[j]-hull[next(j)])<=0)j=next(j);
		else i=next(i);
	}
	if(ans&1)printf("%I64d.5",ans/2);
	else printf("%I64d.0",ans/2);
	return 0;
}
