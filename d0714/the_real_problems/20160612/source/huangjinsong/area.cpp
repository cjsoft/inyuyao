#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
typedef long long LL;
inline int read()
{
	int x=0;bool f=0;char c=getchar();
	for (;c<'0'||c>'9';c=getchar()) f=c=='-'?1:0;
	for (;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	return f?-x:x;
}
const int N=100010;
int n,t,tk;
struct na
{
	LL x,y;
}e[N],st[N<<1];

inline na operator - (const na &a,const na &b)
{
	return (na){a.x-b.x,a.y-b.y};
}

inline LL operator * (const na &a,const na &b)
{
	return a.x*b.y-a.y*b.x;
}

inline LL crs(const na &a,const na &b,const na &c)
{
	return (b-a)*(c-a);
}

inline bool operator < (const na &a,const na &b)
{
	if (a.x!=b.x) return a.y<b.y;
	return a.x<b.x;
}

int main()
{
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	n=read();
	if (n<=2) return puts("0.0"),0;
	for (int i=1;i<=n;i++)
		e[i].x=read(),e[i].y=read();
	sort(e+1,e+n+1);
	for (int i=1;i<=n;i++)
	{
		while (t>1&&crs(st[t-1],e[i],st[t])>=0) t--;
		st[++t]=e[i];
	}
	tk=t;
	for (int i=n-1;i;i--)
	{
		while (t>tk&&crs(st[t-1],e[i],st[t])>=0) t--;
		st[++t]=e[i];
	}
	if (t<=4) {cout<<abs(crs(st[1],st[2],st[3]))/2<<endl;return 0;}
	for (int i=t;i<=t<<1;i++) st[i]=st[i-t+1];
	LL ans=0;
	for (int i=1,i1=1,j=2,j1=2;j<t;i++)
	{
		while (j<t&&(st[i+1]-st[i])*(st[j+1]-st[j])>0) 
			j++;
		i1=max(i1,i);j1=max(j1,j);
		while ((st[i1+1]-st[i1])*(st[j]-st[i])>0) 
			i1++;
		while ((st[j1+1]-st[j1])*(st[i]-st[j])>0) 
			j1++;
		LL rec=crs(st[i],st[i1],st[j])+crs(st[j],st[j1],st[i]);
		ans=max(ans,rec);
	}
	cout<<ans/2<<"."<<((ans&1)?5:0)<<endl;
	return 0;
}
