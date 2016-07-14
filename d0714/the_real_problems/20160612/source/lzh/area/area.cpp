#include<iostream>
#include<cstdio>
#include<algorithm>
#define N 100001
#include<cmath>
#include <iomanip>
using namespace std;
const long double pi=acos(-1);
struct point{
	long double x,y;
	long double w;
	point(long double X=0,long double Y=0){x=X,y=Y;}
	void read(){
		double X,Y;
		scanf("%lf %lf",&X,&Y);
		x=X,y=Y;
	}
}a[N],d[N],o;
int n,l,r;
long double ans;
point operator+(point a,point b){return point(a.x+b.x,a.y+b.y);}
point operator-(point a,point b){return point(a.x-b.x,a.y-b.y);}
point operator/(point a,long double b){return point(a.x/b,a.y/b);}
long double operator*(point a,point b){return a.x*b.y-a.y*b.x;}
long double cross(point a,point b,point c){
	return (b-a)*(c-a);
}
long double did(long double x){
	return x<0?x+pi+pi:x;
}
long double getw(point a){
	return did(atan2(a.y,a.x));
}
bool cmp(const point&a,const point&b){return a.w<b.w;}
int did1(int x){
	return x>r?l:x;
}
long double Abs(long double x){
	return x<0?-x:x;
}
long double er(int l,int r,int x,int y){
	static int mid,L,R;
	static long double s,s1,s2;
	s=0;
	L=l,R=r;
	while (l<=r){
		mid=(l+r)/2;
		s1=Abs(cross(d[x],d[y],d[mid]));
		s2=Abs(cross(d[x],d[y],d[mid+1]));
		if (L<=mid+1&&mid+1<=R&&s1<s2)s=max(s,s2),l=mid+1;
		else
			r=mid-1,s=max(s,s1);
	}
	return s;
}
int main(){
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		a[i].read(),o=o+a[i];
	o=o/n;
	for (int i=1;i<=n;i++)
		a[i].w=getw(a[i]-o);
	sort(a+1,a+n+1,cmp);
	l=1,r=0;
	for (int i=1;i<=n;i++){
		while (r-l+1>=3&&cross(d[r-1],d[r],a[i])<=0)r--;
		while (r-l+1>=3&&cross(a[i],d[l],d[l+1])<=0)l++;
		d[++r]=a[i];
	}
	bool bz=1;
	while (bz){
		bz=0;
		while (r-l+1>=4&&cross(d[r-1],d[r],d[l])<=0)r--,bz=1;
		while (r-l+1>=4&&cross(d[r],d[l],d[l+1])<=0)l++,bz=1;
	}
	if (r-l+1<=2)printf("0.0");
	else
	if (r-l+1==3)printf("%.1Lf",Abs(cross(d[l],d[l+1],d[l+2]))/2);
	else{
		for (int i=l;i<=r;i++)
			for (int j=i+1;j<=r;j++){
				long double s1=0,s2=0;
				s1=er(i+1,j-1,i,j);
				s2=max(er(l,i-1,i,j),er(j+1,r,i,j));
				ans=max(ans,s1+s2);
				if (ans==s1+s2){
					int yy;
					yy=0;
				}
			}
		printf("%.1Lf",ans/2);
	}
	return 0;
}