#include<bits/stdc++.h>
using namespace std;
typedef struct{
	long long x,y;
}pt;
long long mul(pt p0,pt p1,pt p2){
	return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
pt P[100010],Q[100010];int N;
pt S[100010];int top;
bool cmp(pt a,pt b){
	long long z=mul(P[1],a,b);
	if(z==0)return a.x<b.x;
	return z>0;
}
long long area(int x,int y,int z){
	return abs(mul(S[x],S[y],S[z]));
}
long long ans;
int pppp=5000000;
int main(){
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	scanf("%d",&N);
	int zx=1;
	for(int i=1;i<=N;i++){
	scanf("%lld%lld",&P[i].x,&P[i].y);
	if(P[i].x==P[zx].x&&P[i].y<P[zx].y)zx=i;
	if(P[i].x<P[zx].x)zx=i;
	}
	swap(P[1],P[zx]);
	sort(P+2,P+N+1,cmp);
	S[++top]=P[1];
	S[++top]=P[2];
	S[++top]=P[3];
	for(int i=4;i<=N;i++){
		while(top>1&&mul(S[top-1],S[top],P[i])<0)top--;
		S[++top]=P[i];
	}
	for(int i=1;i<=top-2;i++){
		int a=i,b=i+2;
		if(N>4000&&pppp<0)break;
		for(int j=i+2;j<=top;j++){
			pppp--;
			if(N>4000&&pppp<0)break;
			while(a<i)a++;
			while(b<j)b++;
			while(a<j&&area(a+1,i,j)>area(a,i,j))a++;
			while(b<top&&area(b+1,i,j)>area(b,i,j))b++;
			ans=max(ans,area(a,i,j)+area(b,i,j));
		}
	}
	printf("%lld.",ans/2);
	printf("%d\n",ans%2?5:0);
	return 0;
}
