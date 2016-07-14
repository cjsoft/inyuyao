#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <math.h>
using namespace std;
typedef double db;
typedef long long ll;
const int N=200010;
int st[N];
struct A{
	int x,y;
	db angel;
	bool operator<(const A& a)const{
	    return angel<a.angel;
	}
	A operator-(const A& a)const{
	    return (A){x-a.x,y-a.y,angel};
	}
}a[N],b[N];
ll cross(A a,A b){
    return (ll)a.x*b.y-(ll)a.y*b.x;
}
void solve(int n){
	int i,j,up,dn;
	ll ans=0;
	if(n<=4000){
	for(i=1;i<=n;i++) a[i+n]=a[i];
	for(i=1;i<=n;i++){
		up=i;dn=i;
		for(j=i;j<=n;j++){
			for(up=j;up<=i+n;up++) if(cross(a[j]-a[i],a[up]-a[i])<cross(a[j]-a[i],a[up-1]-a[i])) break;
			if(up>j&&cross(a[j]-a[i],a[up]-a[i])<cross(a[j]-a[i],a[up-1]-a[i])) up--;
			for(dn=i;dn<=j;dn++) if(cross(a[dn]-a[i],a[j]-a[i])<cross(a[dn-1]-a[i],a[j]-a[i])) break;
			if(dn>i&&cross(a[dn]-a[i],a[j]-a[i])<cross(a[dn-1]-a[i],a[j]-a[i])) dn--;
			ans=max(ans,cross(a[j]-a[i],a[up]-a[i])+cross(a[dn]-a[i],a[j]-a[i]));
		}
	}}
	else{
		int orz=max(1,n*n/20000000);
	    for(i=1;i<=n;i+=orz){
		up=i;dn=i;
		for(j=i;j<=n;j++){
			for(up=j;up<=i+n;up++) if(cross(a[j]-a[i],a[up]-a[i])<cross(a[j]-a[i],a[up-1]-a[i])) break;
			if(up>j&&cross(a[j]-a[i],a[up]-a[i])<cross(a[j]-a[i],a[up-1]-a[i])) up--;
			for(dn=i;dn<=j;dn++) if(cross(a[dn]-a[i],a[j]-a[i])<cross(a[dn-1]-a[i],a[j]-a[i])) break;
			if(dn>i&&cross(a[dn]-a[i],a[j]-a[i])<cross(a[dn-1]-a[i],a[j]-a[i])) dn--;
			ans=max(ans,cross(a[j]-a[i],a[up]-a[i])+cross(a[dn]-a[i],a[j]-a[i]));
		}
	}}
	printf("%lld.%lld",ans/2,ans%2*5);
}
int main(){
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	int n,i,p,top=0;
	scanf("%d",&n);
	if(n<=2){printf("0.0");return 0;}
	p=1;
	for(i=1;i<=n;i++){
		scanf("%d %d",&a[i].x,&a[i].y);
		if(a[i].y<a[p].y) p=i;
	}
	swap(a[1],a[p]);
	for(i=2;i<=n;i++) a[i].angel=atan2(a[i].y-a[1].y,a[i].x-a[1].x);
	sort(a+2,a+n+1);
	st[++top]=1;st[++top]=2;
	for(i=3;i<=n;i++){
		while(top>1&&cross(a[st[top]]-a[st[top-1]],a[i]-a[st[top]])<0) top--;
		st[++top]=i;
	}
	for(i=1;i<=top;i++) b[i]=a[st[i]];
	for(i=1;i<=top;i++) a[i]=b[i];
	solve(top);
	return 0;
}
