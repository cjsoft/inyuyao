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
}e[N];

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
	LL ans=0;
	n=read();
	for (int i=1;i<=n;i++) e[i].x=read(),e[i].y=read();
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			for (int k=1;k<=n;k++)
			{
				LL rec=crs(e[i],e[j],e[k]);
				for (int l=1;l<=n;l++)
				{
					LL r2=rec+crs(e[i],e[k],e[l]);
					ans=max(ans,r2);
				}
			}
	cout<<ans/2<<"."<<((ans&1)?5:0)<<endl;
	return 0;
}
