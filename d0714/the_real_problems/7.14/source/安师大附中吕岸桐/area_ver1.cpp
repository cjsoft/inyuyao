#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int N=100005;
const long long INF=999999999999999.0;

int n,_xy,St[N*2],stk;
long long _x=INF,_y=INF;

struct Point{
long long x,y;
Point(){}
Point(long long sx,long long sy){x=sx;y=sy;}
friend Point operator-(const Point &A,const Point &B){return Point(A.x-B.x,A.y-B.y);}
friend long long operator*(const Point &A,const Point &B){return A.x*B.y-A.y*B.x;}
}poi[N];

long long Abs(long long x){return x>0?x:-x;}

bool cmp(const Point &A,const Point &B){
return (A-poi[1])*(B-poi[1])<0;
}

void Graham(){
//for(int i=1;i<=n;i++)printf("%lf %lf\n",poi[i].x,poi[i].y);
//puts("---------------");
St[++stk]=1;
St[++stk]=2;
for(int i=3;i<=n;i++){
	while(stk>2 && (poi[St[stk]]-poi[St[stk-1]])*(poi[i]-poi[St[stk-1]])>0)stk--;
	St[++stk]=i;
}
//for(int i=1;i<=stk;i++)printf("%lf %lf\n",poi[St[i]].x,poi[St[i]].y);
}

void Bf(){
if(stk==3){long long ans=(poi[St[3]]-poi[St[1]])*(poi[St[2]]-poi[St[1]]);printf("%lld",ans/2ll);if(ans%2)puts(".5");else puts(".0\n");return;}
long long ans=-INF;
for(int i=1;i<=stk;i++){
	for(int j=i+1;j<=stk;j++){
		for(int k=j+1;k<=stk;k++){
			for(int l=k+1;l<=stk;l++){
				ans=max(ans,(poi[St[l]]-poi[St[i]])*(poi[St[k]]-poi[St[i]])+(poi[St[k]]-poi[St[i]])*(poi[St[j]]-poi[St[i]]));
				//printf("%lld %lld\n",ans,(poi[St[l]]-poi[St[i]])*(poi[St[k]]-poi[St[i]])+(poi[St[k]]-poi[St[i]])*(poi[St[j]]-poi[St[i]]));
			}
		}
	}
}
printf("%lld",ans/2ll);
if(ans%2)puts(".5");
else puts(".0");
}

void Kq(){
for(int i=1;i<=stk;i++)St[i+stk]=St[i];
stk*=2;

}

int main(){
freopen("area.in","r",stdin);
freopen("area.out","w",stdout);
scanf("%d",&n);
for(int i=1;i<=n;i++){
	scanf("%lld %lld",&poi[i].x,&poi[i].y);
	if(poi[i].x<_x || poi[i].x==_x && poi[i].y<_y){_x=poi[i].x,_y=poi[i].y;_xy=i;}
}
if(n==3){}
swap(poi[1],poi[_xy]);
sort(poi+2,poi+n+1,cmp);
Graham();
if(stk<=50)Bf();
else Kq();
return 0;
}

