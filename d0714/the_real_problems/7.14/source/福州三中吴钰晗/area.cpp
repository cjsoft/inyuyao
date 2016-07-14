#include<bits/stdc++.h>
using namespace std;
int read()
{
	int s=0,f=1;char ch=getchar();
	while(!('0'<=ch&&ch<='9')){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){s=(s<<3)+(s<<1)+ch-'0';ch=getchar();}
	return s*f;
}
#define LL long long
struct point
{
	LL x,y;
}p[100005],sta[200005];int m;
LL operator*(point a,point b)
{
	return a.x*b.y-b.x*a.y;
}
point operator-(point a,point b)
{
	return (point){a.x-b.x,a.y-b.y};
}
LL sqr(LL s)
{
	return s*s;
}
LL dis(point a,point b)
{
	return sqr(a.x-b.x)+sqr(a.y-b.y);
}
bool cmp(point a,point b)
{
	if(a.x==b.x)return a.y<b.y;
	return a.x<b.x;
}
int n;
int p1,p2,p3,p4;
int ne[200005],la[200005];
LL ans=0;
bool line(point a,point b,point c)
{
	if((c-a)*(b-a)!=0)return 0;
	return b.x>=min(a.x,c.x)&&b.x<=max(a.x,c.x)&&b.y>=min(a.y,c.y)&&b.y<=max(a.y,c.y);
}
int main()
{
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)
	    p[i]=(point){read(),read()};
	sort(&p[1],&p[n+1],cmp);
	for(int i=1;i<=n;i++)
	   {sta[++m]=p[i];
	    while(m-2>0?((sta[m]-sta[m-2])*(sta[m-1]-sta[m-2])>0||line(sta[m-2],sta[m-1],sta[m])):0)sta[m-1]=sta[m--];
	   }
	for(int i=n-1;i>=1;i--)
	   {sta[++m]=p[i];
	    while(m-2>0?((sta[m]-sta[m-2])*(sta[m-1]-sta[m-2])>0||line(sta[m-2],sta[m-1],sta[m])):0)sta[m-1]=sta[m--];
	   }
	m--;
	n=m;
	for(int i=1;i<=n;i++)ne[i]=i+1,la[i]=i-1;ne[n]=1;la[1]=n;
	LL n2=0,n3=0,n4=0;
	for(p1=p2=p3=p4=1;p1<=n;p1++)
	   {LL ss=0;//cout<<sta[p1].x<<" "<<sta[p1].y<<endl;
	    n3=dis(sta[p1],sta[p3]);
	    
		    point v=sta[p3]-sta[p1];
			n2=(sta[p2]-sta[p1])*v;
			while((ss=(sta[ne[p2]]-sta[p1])*v)>n2)p2=ne[p2],n2=ss;
			while((ss=(sta[la[p2]]-sta[p1])*v)>n2)p2=la[p2],n2=ss;
			n4=v*(sta[p4]-sta[p1]);
			while((ss=(v*(sta[ne[p4]]-sta[p1])))>n4)p4=ne[p4],n4=ss;
			while((ss=(v*(sta[la[p4]]-sta[p1])))>n4)p4=la[p4],n4=ss;
	    while((ss=dis(sta[p1],sta[ne[p3]]))>n3)
		   {p3=ne[p3],n3=ss;
		   
		 	point v=sta[p3]-sta[p1];
			n2=(sta[p2]-sta[p1])*v;
			while((ss=(sta[ne[p2]]-sta[p1])*v)>n2)p2=ne[p2],n2=ss;
			while((ss=(sta[la[p2]]-sta[p1])*v)>n2)p2=la[p2],n2=ss;
			n4=v*(sta[p4]-sta[p1]);
			while((ss=(v*(sta[ne[p4]]-sta[p1])))>n4)p4=ne[p4],n4=ss;
			while((ss=(v*(sta[la[p4]]-sta[p1])))>n4)p4=la[p4],n4=ss;
			ans=max(ans,n2+n4);//cout<<p1<<" "<<p2<<" "<<p3<<" "<<p4<<endl;
		   }
			ans=max(ans,n2+n4);//cout<<p1<<" "<<p2<<" "<<p3<<" "<<p4<<endl;
	   }
	printf("%lld.%d\n",ans/2,((ans&1)?5:0));
	return 0;
}

