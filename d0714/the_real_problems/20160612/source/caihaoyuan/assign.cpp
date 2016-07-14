#include<bits/stdc++.h>
#define rep(i,j,k) for((i)=(j);(i)<=(k);++i)
using namespace std;
const int N = 100000;
int a[N],b[N],l[N],r[N],pro,k,i,n;
struct point{int x,y;}c[N],d[N];
bool inline cmp(point a,point b){return a.x>b.x||a.x==b.x&&a.y<b.y;}
bool inline cmp2(point a,point b){return a.y<b.y;}
int inline read(){
	char ch=getchar();int z=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){z=z*10+ch-'0';ch=getchar();}
	return z*f;
}
void dfs(int x){
	int i;
	if(x>n){
		rep(i,1,n) d[i]=c[i];
		sort(d+1,d+n+1,cmp);
		sort(d+1,d+k+1,cmp2);
		rep(i,1,k)
			if((i&3)<2) ++a[d[i].y];
			else ++b[d[i].y];
		}
	else{
		c[x].y=x;
		rep(i,l[x],r[x]){
			c[x].x=i; dfs(x+1);
		}
	}
}
int main(){
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	n=read(); pro=1;
	rep(i,1,n) l[i]=read();
	rep(i,1,n) r[i]=read();
	rep(i,1,n) pro*=(r[i]-l[i]+1);
	k=read();
	dfs(1);
	rep(i,1,n) printf("%.6f %.6f\n",(double)a[i]/(double)pro,(double)b[i]/(double)pro);
	return 0;
}
