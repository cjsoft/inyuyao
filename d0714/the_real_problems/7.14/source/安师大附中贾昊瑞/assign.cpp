#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<memory.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<queue>
#include<map>
#include<set>
#include<list>
#include<deque>
#include<vector>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define F(i,j,n) for(register int i=j;i<=n;i++)
#define D(i,j,n) for(register int i=j;i>=n;i--)
#define ll long long
#define lc (k<<1)
#define rc ((k<<1)|1)
using namespace std;
void in(int&a);void in(ll&a);
int n,k;int a[30][2],ans[30][2],tot=1;int b[30],d[30];
struct no{
	int x,nm;
	bool operator <(const no&b)const{
	if(x==b.x)return nm<b.nm;
	return x>b.x;}
}c[30];
void dfs(int x){
	if(x==n){
		F(i,0,n-1)c[i].x=b[i],c[i].nm=i,d[i]=0;
		sort(c,c+n);
//		F(i,0,n-1)printf("%d ",b[i]);printf("\n");
//		F(i,0,n-1)printf("%d %d ",c[i].x,c[i].nm);printf("\n");
		F(i,0,k-1)d[c[i].nm]=1;
		register int i=0,j=0;
		for(;j<k;i++)
			if(d[i]){
			if((j&3)==3||(j&3)==0)ans[i][0]++;
			else ans[i][1]++;
			j++;
		}
		return;
	}
	F(i,a[x][0],a[x][1])
	b[x]=i,dfs(x+1);
}
int main()
{
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	in(n);F(i,0,n-1)in(a[i][0]);F(i,0,n-1)in(a[i][1]),tot*=(a[i][1]-a[i][0]+1);in(k);
	dfs(0);
//	printf("%d\n",tot);
	F(i,0,n-1){
//	printf("%d %d\n",ans[i][0],ans[i][1]);
	printf("%.6lf %.6lf\n",ans[i][0]*1.0/tot,ans[i][1]*1.0/tot);
	}
	return 0;
}
void in(ll&a){register char c;register bool y=false;c=getchar();a=0;
while(c<'0'||c>'9'){if(c=='-'){c=getchar();y=true;break;}c=getchar();}
while(c>='0'&&c<='9'){a=(a<<3)+(a<<1)+c-'0';c=getchar();}if(y)a=-a;}
void in(int&a){register char c;register bool y=false;c=getchar();a=0;
while(c<'0'||c>'9'){if(c=='-'){c=getchar();y=true;break;}c=getchar();}
while(c>='0'&&c<='9'){a=(a<<3)+(a<<1)+c-'0';c=getchar();}if(y)a=-a;}
