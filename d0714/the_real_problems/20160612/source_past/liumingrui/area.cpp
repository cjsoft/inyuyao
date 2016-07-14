#include <algorithm>
#include <cstdio>
#include <cmath>
#define rep(i,n) for(int i=1;i<=n;++i)
#define N 100005
using namespace std;
typedef long long ll;
struct poi{int x,y;}a[N],p[N];
int n,top=3;ll ans=0;
poi operator -(poi x,poi y){return (poi){x.x-y.x,x.y-y.y};}
ll operator *(poi x,poi y){return 1ll*x.y*y.x-1ll*x.x*y.y;}
ll cro(poi x,poi y,poi z){return (y-x)*(z-x);}
bool cmp(poi x,poi y){if(x.x==y.x)return x.y<y.y;return x.x<y.x;}
bool cp2(poi x,poi y){if(x*y==0)return x.x<y.x;return x*y<0;}
int ne(int x){++x;if(x>n)return 1;return x;}
bool che(int x,int y,int z){if(y==n)return 0;return cro(p[x],p[z],p[y])<=cro(p[x],p[z],p[ne(y)]);}
int main(){
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	scanf("%d",&n);
	rep(i,n)scanf("%d%d",&a[i].x,&a[i].y);
	sort(a+1,a+n+1,cmp);poi tp=a[1];
	rep(i,n-1)a[i]=a[i+1]-tp;--n;
	sort(a+1,a+n+1,cp2);
	p[1]=(poi){0,0};p[2]=a[1];p[3]=a[2];
	for(int i=3;i<=n;++i){
		while(top>2&&cro(a[i],p[top],p[top-1])<0)--top;
		p[++top]=a[i];
	}
	n=top;
	int x=1,y=1,z=1,w=1;
	for(;x<=n;++x){
		while(1){
			while(1){
				while(che(z,w,x))w=ne(w);
				//printf("%d %d %d %d\n",x,y,z,w);
				ans=max(ans,cro(p[x],p[z],p[y])+cro(p[z],p[x],p[w]));
				if(che(y,z,w))z=ne(z);else break;
			}
			if(che(x,y,z))y=ne(y);else break;
		}
		/*while(che(x,y,z)||che(y,z,w)||che(z,w,x)){
			if(che(x,y,z))y=ne(y);
			if(che(y,z,w))z=ne(z);
			if(che(z,w,x))w=ne(w);
		}*/
	}
	if((ans&1)==1)printf("%lld.5\n",ans>>1);else printf("%lld.0\n",ans>>1);
	return 0;
}