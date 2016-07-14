#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long ll;

struct P{int x,y;}a[310000],s[310000];
int n,minn,top,li,lj;ll ans;
ll _abs(ll x){return x>0?x:-x;}
ll operator * (P a,P b){return (ll)a.x*b.y-(ll)a.y*b.x;}
P operator - (P a,P b){return (P){a.x-b.x,a.y-b.y};}
bool operator != (P a,P b){return a.x!=b.x||a.y!=b.y;}
ll dis(P a){return a.x*a.x+a.y*a.y;}
ll stri(P a,P b,P c){return _abs((c-a)*(c-b));}

int cmp1(P x,P y){
	ll tmp=(x-a[1])*(y-a[1]);
	if(!tmp)return dis(a[1]-x)<dis(a[1]-y);
	else return tmp>0;
}

void convex_hull(){
	s[++top]=a[1],s[++top]=a[2];
	for(int i=3;i<=n;i++){
		while(top>1&&(s[top]-s[top-1])*(a[i]-s[top-1])<=0)top--;
		s[++top]=a[i];
	}
}

int main(){
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	scanf("%d",&n);
	if(n<=2){printf("0.0\n");return 0;}
	minn=1;
	for(int i=1;i<=n;i++){
		scanf("%d %d",&a[i].x,&a[i].y);
		if(a[i].x<a[minn].x||a[i].x==a[minn].x&&a[i].y<a[minn].y)minn=i;
	}swap(a[1],a[minn]);
	sort(a+2,a+n+1,cmp1);
	convex_hull();
	if(top==3){
		ans=stri(s[1],s[2],s[3]);
		printf("%lld",ans/2);
		if(ans&1)printf(".5");
		else printf(".0");
		return 0;
	}for(int i=1;i<=top;i++){
		s[i+top+top]=s[i+top]=s[i];
	}for(int i=1;i<=top;i++){
		li=i,lj=i+1;
		for(int j=i+1;s[j]!=s[i];j++){
			while(s[li+1]!=s[j]&&stri(s[i],s[j],s[li+1])>stri(s[i],s[j],s[li]))li++;
			while(s[lj+1]!=s[i]&&stri(s[i],s[j],s[lj+1])>stri(s[i],s[j],s[lj]))lj++;
			ans=max(ans,stri(s[i],s[j],s[li])+stri(s[i],s[j],s[lj]));
		}
	}printf("%lld",ans/2);
	if(ans&1)printf(".5");
	else printf(".0");
	return 0;
}
