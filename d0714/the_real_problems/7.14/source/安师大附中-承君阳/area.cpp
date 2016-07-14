#include<bits/stdc++.h>
#define C(a,b,c) 1ll*(b.x-a.x)*(c.y-a.y)-1ll*(c.x-a.x)*(b.y-a.y)
#define D(a,b) 1ll*(b.x-a.x)*(b.x-a.x)+1ll*(b.y-a.y)*(b.y-a.y)
#define G(o,j) C(q[i],q[o.x],q[j])+C(q[j],q[o.y],q[i])
#define N 233333
using namespace std;
int n,i,j,t;
struct P{int x,y;}p[N],q[N],o,e;
long long S;
long long M(P x,P y){return C(p[0],x,y)>0||C(p[0],x,y)==0&&D(p[0],x)<D(p[0],y);}
int R(P&o,int j)
{
	while(o.x<i||C(q[i],q[o.x],q[j])<C(q[i],q[o.x+1],q[j]))o.x++;
	while(o.y<j||C(q[j],q[o.y],q[i])<C(q[j],q[o.y+1],q[i]))o.y++;
}
main()
{
	for(freopen("area.in","r",stdin),freopen("area.out","w",stdout),cin>>n,i=0;i<n;i++)
		if(cin>>p[i].x>>p[i].y,p[i].x<p[0].x||p[i].x==p[0].x&&p[i].y<p[0].y)swap(p[i],p[0]);
	for(sort(p+1,p+n,M),p[n]=q[i=t=1]=p[0];i<=n;q[++t]=p[i++])while(t>1&&C(q[t-1],q[t],p[i])<=0)t--;
	for(i=--t;i;i--)q[i+t]=q[i];
	for(i=j=1;i<=t;S=max(S,G(o,j)),i++)for(R(o,j),R(e,j+1);G(o,j)<G(e,j+1);j++)o=e,R(e,j+1);
	cout<<S/2<<"."<<S%2*5;
}
//23333
