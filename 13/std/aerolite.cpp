#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
typedef long double LD;
typedef pair<LD,LD> pdd;
const LD eps=1e-9,PI=acos(-(LD)1);
const int MAXN=200,MAXM=200;
inline int dcmp(const LD &o)
{
	if(o>eps)return 1;
	else if(o<-eps)return -1;
	else return 0;
}
inline void restric(LD &a,LD &b)
{
	while(a<0)a+=2*PI,b+=2*PI;
	while(a>=2*PI)a-=2*PI,b-=2*PI;
	while(b<a)b+=2*PI;
}
struct Point
{
	LD x,y;
	Point(LD _x=0,LD _y=0):x(_x),y(_y){}
	Point operator+(const Point &o)const{return Point(x+o.x,y+o.y);}
	Point operator-(const Point &o)const{return Point(x-o.x,y-o.y);}
	Point operator*(const LD &o)const{return Point(x*o,y*o);}
	Point operator/(const LD &o)const{return Point(x/o,y/o);}
	LD mold(){return sqrt(x*x+y*y);}
	LD polar(){return atan2(y,x);}
}poly[MAXN];
inline LD dot(const Point &a,const Point &b){return a.x*b.x+a.y*b.y;}
inline LD cross(const Point &a,const Point &b){return a.x*b.y-a.y*b.x;}
bool cmp(const Point &a,const Point &b){return dcmp(cross(a-poly[0],b-poly[0]))>0;}
vector<pdd> temp;
inline void maintain(vector<pdd> &edit)
{
	if(edit.empty())return;
	temp=edit,edit.clear();
	sort(temp.begin(),temp.end());
	vector<pdd>::iterator i=temp.begin();
	LD st=i->first,ed=i->second;
	for(i++;i!=temp.end();i++)
	{
		if(i->first>ed)
		{
			edit.push_back(pdd(st,ed));
			st=i->first,ed=i->second;
		}
		else ed=max(ed,i->second);
	}
	edit.push_back(pdd(st,ed));
}
inline void change(vector<pdd> &exist,vector<pdd> &rem)
{
	if(exist.empty())
	{
		rem.push_back(pdd(0,2*PI));
		return;
	}
	sort(exist.begin(),exist.end());
	vector<pdd>::iterator i=exist.begin();
	LD st=i->first,ed=i->second;
	rem.push_back(pdd(0,st));
	for(i++;i!=exist.end();i++)
	{
		if(i->first>ed)
		{
			rem.push_back(pdd(ed,i->first));
			st=i->first,ed=i->second;
		}
		else ed=max(ed,i->second);
	}
	rem.push_back(pdd(ed,2*PI));
}
struct Segment
{
	Point head,vec;
	vector<pdd> rem;
	Segment(Point _head=Point(),Point _vec=Point()):head(_head),vec(_vec),rem(vector<pdd>()){}
	LD area()
	{
		LD ret=cross(head,vec);
		maintain(rem);
		for(vector<pdd>::iterator i=rem.begin();i!=rem.end();i++)
			ret-=cross(head+vec*(i->first),head+vec*(i->second));
		return ret*0.5;
	}
}seg[MAXN];
struct Circle
{
	Point cent;
	LD rad;
	vector<pdd> exist,rem;
	Circle(Point _cent=Point(),LD _rad=0):cent(_cent),rad(_rad),exist(vector<pdd>()),rem(vector<pdd>()){}
	LD area()
	{
		LD ret=2*PI*rad*rad;
		maintain(rem);
		for(vector<pdd>::iterator i=rem.begin();i!=rem.end();i++)
			ret-=rad*cent.x*(sin(i->second)-sin(i->first))-rad*cent.y*(cos(i->second)-cos(i->first))+rad*rad*(i->second-i->first);
		return ret*0.5;
	}
}cir[MAXM];
vector<pdd> exist[MAXM];
int n,m;
inline void init()
{
	int x,y,r;
	scanf("%d",&m);
	for(int i=0;i<m;i++)
	{
		scanf("%d%d%d",&x,&y,&r);
		cir[i]=Circle(Point(x,y),r);
	}
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		poly[i]=Point(x,y);
	}
}
inline void prepare()
{
	for(int i=1;i<n;i++)
	{
		int d=dcmp(poly[i].x-poly[0].x);
		if(d<0||(d==0&&poly[i].y<poly[0].y))swap(poly[i],poly[0]);
	}
	sort(poly+1,poly+n,cmp);
	for(int i=0;i<n-1;i++)seg[i]=Segment(poly[i],poly[i+1]-poly[i]);
	seg[n-1]=Segment(poly[n-1],poly[0]-poly[n-1]);
}
inline void cover(Circle &a,Circle &b)
{
	LD dist=(b.cent-a.cent).mold();
	if(dcmp(b.rad+a.rad-dist<=0))return;
	else if(dcmp(b.rad-a.rad-dist)>=0)a.rem.push_back(pdd(0,2*PI));
	else if(dcmp(a.rad-b.rad-dist)>=0)b.rem.push_back(pdd(0,2*PI));
	else
	{
		LD alpha,theta,st,ed;
		//b covers a
		alpha=(b.cent-a.cent).polar(),theta=acos((a.rad*a.rad+dist*dist-b.rad*b.rad)/(2*a.rad*dist));
		st=alpha-theta,ed=alpha+theta;
		restric(st,ed);
		if(ed<=2*PI)a.rem.push_back(pdd(st,ed));
		else
		{
			a.rem.push_back(pdd(st,2*PI));
			a.rem.push_back(pdd(0,ed-2*PI));
		}
		// a covers b
		alpha+=PI,theta=acos((b.rad*b.rad+dist*dist-a.rad*a.rad)/(2*b.rad*dist));
		st=alpha-theta,ed=alpha+theta;
		restric(st,ed);
		if(ed<=2*PI)b.rem.push_back(pdd(st,ed));
		else
		{
			b.rem.push_back(pdd(st,2*PI));
			b.rem.push_back(pdd(0,ed-2*PI));
		}
	}
}
inline void cover(Segment &a,Circle &b)
{
	LD len=a.vec.mold();
	LD dist=cross(a.vec,b.cent-a.head)/len;
	if(dcmp(dist-b.rad)>=0)return;
	else if(dcmp(dist+b.rad)<=0)b.exist.push_back(pdd(0,2*PI));
	else
	{
		LD alpha=sqrt(b.rad*b.rad-dist*dist)/len,st,ed;
		LD mid=dot(b.cent-a.head,a.vec)/(len*len);
		Point pedal=a.head+a.vec*mid;
		Point p1=pedal-a.vec*alpha,p2=pedal+a.vec*alpha;
		st=(p1-b.cent).polar(),ed=(p2-b.cent).polar();
		restric(st,ed);
		if(ed<=2*PI)b.exist.push_back(pdd(st,ed));
		else
		{
			b.exist.push_back(pdd(st,2*PI));
			b.exist.push_back(pdd(0,ed-2*PI));
		}
		st=max(mid-alpha,(LD)0),ed=min(mid+alpha,(LD)1);
		if(st<ed)a.rem.push_back(pdd(st,ed));
	}
}
inline double solve()
{
	LD ret=0;
	for(int i=0;i<m;i++)
		for(int j=i+1;j<m;j++)
			cover(cir[i],cir[j]);
	for(int i=0;i<n;i++)ret+=seg[i].area();
	for(int i=0;i<m;i++)ret+=cir[i].area();
/*	for(int i=0;i<m;i++)
	{
		cout<<"###Removed parts of circle "<<i<<":"<<endl;
		for(int j=0;j<cir[i].rem.size();j++)cout<<cir[i].rem[j].first<<' '<<cir[i].rem[j].second<<endl;
	}*/
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cover(seg[i],cir[j]);
	for(int i=0;i<n;i++)ret-=seg[i].area();
	for(int i=0;i<m;i++)
	{
		change(cir[i].exist,cir[i].rem);
		ret-=cir[i].area();
	}
/*	for(int i=0;i<n;i++)
	{
		cout<<"###Removed parts of segment "<<i<<":"<<endl;
		for(int j=0;j<seg[i].rem.size();j++)cout<<seg[i].rem[j].first<<' '<<seg[i].rem[j].second<<endl;
	}
	for(int i=0;i<m;i++)
	{
		cout<<"###Removed parts of circle "<<i<<":"<<endl;
		for(int j=0;j<cir[i].rem.size();j++)cout<<cir[i].rem[j].first<<' '<<cir[i].rem[j].second<<endl;
	}*/
	return fabs(ret);
}
int main(void)
{
	freopen("aerolite.in","r",stdin);
	freopen("aerolite.out","w",stdout);
	init();
	prepare();
	printf("%.9lf\n",solve());
	return 0;
}
