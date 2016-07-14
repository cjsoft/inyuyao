#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

//#define DEBUG

const int N=100005;
const long long INF=99999999999999999.0;

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
#ifdef DEBUG
int is=0,js=0,ks=0,ls=0;
#endif
for(int i=1;i<=stk;i++){
	for(int j=i+1;j<=stk;j++){
		for(int k=j+1;k<=stk;k++){
			for(int l=k+1;l<=stk;l++){
				ans=max(ans,(poi[St[l]]-poi[St[i]])*(poi[St[k]]-poi[St[i]])+(poi[St[k]]-poi[St[i]])*(poi[St[j]]-poi[St[i]]));
				#ifdef DEBUG
				if(ans==(poi[St[l]]-poi[St[i]])*(poi[St[k]]-poi[St[i]])+(poi[St[k]]-poi[St[i]])*(poi[St[j]]-poi[St[i]]))is=i,js=j,ks=k,ls=l;
				#endif
				//printf("%lld %lld\n",ans,(poi[St[l]]-poi[St[i]])*(poi[St[k]]-poi[St[i]])+(poi[St[k]]-poi[St[i]])*(poi[St[j]]-poi[St[i]]));
			}
		}
	}
}
#ifdef DEBUG
printf("DEBUG:%d %d %d %d\n",is,js,ks,ls);
#endif
printf("%lld",ans/2ll);
if(ans%2)puts(".5");
else puts(".0");
}

bool Checkj(int i,int j,int k,int l){
if(j+1==k || j==stk)return 0;
long long ansl=(poi[St[k]]-poi[St[i]])*(poi[St[j]]-poi[St[i]]);
long long ansr=(poi[St[k]]-poi[St[i]])*(poi[St[j+1]]-poi[St[i]]);
return ansl<ansr;
}

bool Checkk(int i,int j,int k,int l){
if(k+1==l || k==stk)return 0;
long long ansl=(poi[St[l]]-poi[St[i]])*(poi[St[k]]-poi[St[i]])+(poi[St[k]]-poi[St[i]])*(poi[St[j]]-poi[St[i]]);
long long ansr=(poi[St[l]]-poi[St[i]])*(poi[St[k+1]]-poi[St[i]])+(poi[St[k+1]]-poi[St[i]])*(poi[St[j]]-poi[St[i]]);
return ansl<ansr;
}

bool Checkl(int i,int j,int k,int l){
if(l==stk)return 0;
long long ansl=(poi[St[l]]-poi[St[i]])*(poi[St[k]]-poi[St[i]]);
long long ansr=(poi[St[l+1]]-poi[St[i]])*(poi[St[k]]-poi[St[i]]);
return ansl<ansr;
}

void _Kq(){
#ifdef DEBUG
int is=0,js=0,ks=0,ls=0;
#endif
for(int i=1;i<=stk;i++)St[i+stk]=St[i];
stk*=2;
int j=2,k=3,l=4;
long long ans=-INF;
for(int i=1;i<=stk && j<=stk && k<=stk && l<=stk;i++){
	ans=max(ans,(poi[St[l]]-poi[St[i]])*(poi[St[k]]-poi[St[i]])+(poi[St[k]]-poi[St[i]])*(poi[St[j]]-poi[St[i]]));
	#ifdef DEBUG
	if(ans==(poi[St[l]]-poi[St[i]])*(poi[St[k]]-poi[St[i]])+(poi[St[k]]-poi[St[i]])*(poi[St[j]]-poi[St[i]]))is=i,js=j,ks=k,ls=l;
	#endif
	if(j==i)j++;
	if(k==j)k++;
	if(l==k)l++;
	if(i>stk || j>stk || k>stk || l>stk)break;
	int flag=1;
	while(flag){
		flag=0;
		ans=max(ans,(poi[St[l]]-poi[St[i]])*(poi[St[k]]-poi[St[i]])+(poi[St[k]]-poi[St[i]])*(poi[St[j]]-poi[St[i]]));
		if(Checkj(i,j,k,l))j++,flag=1;
		if(Checkk(i,j,k,l))k++,flag=1;
		if(Checkl(i,j,k,l))l++,flag=1;
		ans=max(ans,(poi[St[l]]-poi[St[i]])*(poi[St[k]]-poi[St[i]])+(poi[St[k]]-poi[St[i]])*(poi[St[j]]-poi[St[i]]));
		#ifdef DEBUG
		if(ans==(poi[St[l]]-poi[St[i]])*(poi[St[k]]-poi[St[i]])+(poi[St[k]]-poi[St[i]])*(poi[St[j]]-poi[St[i]]))is=i,js=j,ks=k,ls=l;
		#endif
	}
	ans=max(ans,(poi[St[l]]-poi[St[i]])*(poi[St[k]]-poi[St[i]])+(poi[St[k]]-poi[St[i]])*(poi[St[j]]-poi[St[i]]));
	#ifdef DEBUG
	if(ans==(poi[St[l]]-poi[St[i]])*(poi[St[k]]-poi[St[i]])+(poi[St[k]]-poi[St[i]])*(poi[St[j]]-poi[St[i]]))is=i,js=j,ks=k,ls=l;
	#endif
}
#ifdef DEBUG
printf("DEBUG:%d %d %d %d\n",is,js,ks,ls);
#endif
printf("%lld",ans/2ll);
if(ans%2)puts(".5");
else puts(".0");
}

long long Dist2(const Point &A,const Point &B){
return (A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y);
}

void Bf_Kq(){
for(int i=1;i<=stk;i++)St[i+stk]=St[i];
stk*=2;
int k=3,l=4;
long long ans=-INF;
for(int i=1;i<=stk;i++){
	int k=i+1,l=i+2;
	for(int j=i+1;j<=stk;j++){
		while(k<stk && Dist2(poi[St[i]],poi[St[k]])<Dist2(poi[St[i]],poi[St[k+1]]))k++;
		while(l<stk && Dist2(poi[St[j]],poi[St[l]])<Dist2(poi[St[j]],poi[St[l+1]]))l++;
		ans=max(ans,(poi[St[l]]-poi[St[i]])*(poi[St[k]]-poi[St[i]])+(poi[St[k]]-poi[St[i]])*(poi[St[j]]-poi[St[i]]));
	}
}
printf("%lld",ans/2ll);
if(ans%2)puts(".5");
else puts(".0");
}

int inv[N*2];

long long Test(int i,int j){
int k=inv[i],l=inv[j];
if(St[i]==0 || St[j]==0 || St[k]==0 || St[l]==0 || i>stk || j>stk || k>stk || l>stk)return INF;
return (poi[St[l]]-poi[St[i]])*(poi[St[k]]-poi[St[i]])+(poi[St[k]]-poi[St[i]])*(poi[St[j]]-poi[St[i]]);
}

void Kq(){
//_Kq();
for(int i=1;i<=stk;i++)St[i+stk]=St[i];
stk*=2;
int j=2;
long long ans=-INF;
for(int i=1;i<=stk;i++){while(j<stk && Dist2(poi[St[i]],poi[St[j]])<Dist2(poi[St[i]],poi[St[j+1]]))j++;inv[i]=j;}
for(int i=1;i<=stk;i++){
	int l=i+1,r=stk;
	while(l<r-2){
		int mid1=l+(r-l)/3,mid2=r-(r-l)/3;
		//printf("%d %d %d %d\n",l,r,mid1,mid2);
		long long T1=Test(i,mid1),T2=Test(i,mid2);
		if(T1>T2){r=mid2;ans=max(ans,T1);}
		else {l=mid1;ans=max(ans,T2);}
	}
}
printf("%lld",ans/2ll);
if(ans%2)puts(".5");
else puts(".0");
}

int main(){
freopen("area.in","r",stdin);
freopen("area.out","w",stdout);
scanf("%d",&n);
for(int i=1;i<=n;i++){
	scanf("%lld %lld",&poi[i].x,&poi[i].y);
	if(poi[i].x<_x || poi[i].x==_x && poi[i].y<_y){_x=poi[i].x,_y=poi[i].y;_xy=i;}
}
swap(poi[1],poi[_xy]);
sort(poi+2,poi+n+1,cmp);
Graham();
if(stk<=70)Bf();
else if(stk<=4000)Bf_Kq();
else Kq();
#ifdef DEBUG
printf("%d\n",stk);
Bf();Bf_Kq();Kq();
#endif
return 0;
}

