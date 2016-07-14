#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <memory.h>
#include <time.h>
using namespace std;
typedef long long LL;
const int maxn = 100005;
struct Point {
	LL x,y;
	void read() {
		scanf("%lld %lld",&x,&y);
	}
	Point operator-(const Point &v) {
		return (Point){x-v.x,y-v.y};
	}
	LL operator*(const Point &v) {
		return x*v.y-y*v.x;
	}
};
int n;LL ans;
Point p[maxn];
void upd(LL &x,LL y) {if (x<y) x=y;}
LL ABS(LL x) {return x>0?x:-x;}

namespace part1 {
	void main() {
		for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++) {
			LL ans1=0,ans2=0;
			for (int k=1;k<=n;k++) {
				LL tmp=(p[k]-p[i])*(p[j]-p[i]);
				if (tmp>0) upd(ans1,tmp);
				else upd(ans2,-tmp);
			}
			upd(ans,ans1+ans2);
		}
		if (ans&1) printf("%lld.5",ans/2);
		else printf("%lld.0",ans/2);
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
		freopen("area.in","r",stdin);
		freopen("area.out","w",stdout);
	#endif
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		p[i].read();
//	if (n<=500) 
	part1::main();
//	printf("\n%d\n",clock());
	return 0;
}
