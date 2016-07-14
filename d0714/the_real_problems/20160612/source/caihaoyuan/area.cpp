#include<bits/stdc++.h>
#define rep(i,j,k) for((i)=(j);(i)<=(k);++i)
#define per(i,j,k) for((i)=(j);(i)>=(k);--i)
#define cmax(x,y) (y)>(x)?(x)=(y):0
using namespace std;
typedef long long ll;
const int N = 500000;
struct point{ll x,y;}a[N],stk[N];
point operator -(point a,point b){return (point){a.x-b.x,a.y-b.y};}
ll operator *(point a,point b){return a.x*b.y-a.y*b.x;}
int n,i,j,k,l,top,len,jj,kk,l2; ll ans,tmp,t2;
int inline read(){
	char ch=getchar();int z=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){z=z*10+ch-'0';ch=getchar();}
	return z*f;
}
bool inline cmp(point a,point b){return a.x<b.x||a.x==b.x&&a.y<b.y;}
ll inline cross(point a,point b,point c){return (a-b)*(a-c);}
int main(){
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	n=read();
	rep(i,1,n) a[i].x=read(),a[i].y=read();
	sort(a+1,a+n+1,cmp);
	top=1; stk[1]=a[1];
	rep(i,2,n){
		while(top>1 && (stk[top]-stk[top-1])*(a[i]-stk[top])<=0) --top;
		stk[++top]=a[i];
	}
	len=top;
	per(i,n-1,1){
		while(top>len && (stk[top]-stk[top-1])*(a[i]-stk[top])<=0) --top;
		stk[++top]=a[i];
	}
	--top; rep(i,1,top) stk[i+top*3]=stk[i+top*2]=stk[i+top]=stk[i];
	ans=0; i=1; j=2; l=4;
	rep(k,3,top){
		while(cross(stk[l],stk[i],stk[k])<cross(stk[l+1],stk[i],stk[k]) && l+1<i+top) ++l;
		while(cross(stk[j],stk[k],stk[i])<cross(stk[j+1],stk[k],stk[i]) && j+1<k) ++j;
		if(cross(stk[j],stk[k],stk[i])+cross(stk[l],stk[i],stk[k])>ans){
			ans=cross(stk[j],stk[k],stk[i])+cross(stk[l],stk[i],stk[k]);
			jj=j; kk=k; l2=l;
		}
	}
	j=jj; k=kk; l=l2;
	rep(i,1,top){
	do{
		tmp=cross(stk[j],stk[k],stk[i])+cross(stk[l],stk[i],stk[k]);
		cmax(ans,tmp);
		jj=j; l2=l; ++k;
		while(cross(stk[l],stk[i],stk[k])<cross(stk[l+1],stk[i],stk[k]) && l+1<i+top) ++l;
		while(cross(stk[j],stk[k],stk[i])<cross(stk[j+1],stk[k],stk[i]) && j+1<k) ++j;
		t2=cross(stk[j],stk[k],stk[i])+cross(stk[l],stk[i],stk[k]);
		if(t2<tmp) break;
	}while(k+2<i+top);
	}
	if(ans % 2 == 0) printf("%lld.0\n",ans/2);
	else printf("%lld.5\n",ans/2);
	return 0;
}
