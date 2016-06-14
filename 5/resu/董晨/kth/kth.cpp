#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
#define N 100005
#define INF 5000000
int n,m,k,l,t,s,r,x,y,z,Q,T;
int b[N],id[N],L[N],R[N];
struct node{
	int x,y;
}a[N];
bool cmp(node x,node y){
	return x.x<y.x;
}
void fuck(int k){
	sort(a+L[k],a+R[k]+1,cmp);
}
void add(int l,int r,int v){
	int k=id[l];
	for (int i=L[k];i<=R[k];i++)
		if(a[i].y>=l&&a[i].y<=r)a[i].x+=v;
	fuck(k);
}
int ask(int l,int r,int x){
	int k=id[l];
	int s=0;
	for (int i=L[k];i<=R[k];i++)
		if(a[i].y>=l&&a[i].y<=r)s+=(a[i].x+b[k]<=x);
//	printf("%d %d %d %d\n",l,r,x,s);
	return s;
}
int que(int k,int x){
	int l=L[k],r=R[k];
	while(l<r){
		int mid=l+r+1>>1;
		if(a[mid].x+b[k]<=x)l=mid;else r=mid-1;
	}
	if(a[l].x+b[k]>x)l--;
	return l-L[k]+1;
}
int check(int l,int r,int x){
	int s=0;
	if(id[l]==id[r])return ask(l,r,x);
	s=ask(l,R[id[l]],x)+ask(L[id[r]],r,x);
	for (int i=id[l]+1;i<id[r];i++)s+=que(i,x);
	return s;
}
int main(){
	freopen("kth.in","r",stdin);
	freopen("kth.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)scanf("%d",&a[i].x),a[i].y=i;
	m=min(n,(int)(sqrt(n)*3));
	k=n/m;
	if(k*m<n)k++;
	for (int i=n+1;i<=k*m;i++)a[i].x=INF+1;
	for (int i=1;i<=n;i++)id[i]=(i-1)/m+1;
	for (int i=1;i<=k;i++){
		L[i]=(i-1)*m+1;
		R[i]=i*m;
		fuck(i);
	}
	scanf("%d",&Q);
	while(Q--){
		scanf("%d%d%d%d",&T,&x,&y,&z);
		if(T==1){
			if(id[x]==id[y])add(x,y,z);
			else{
				add(x,R[id[x]],z);add(L[id[y]],y,z);
				for (int i=id[x]+1;i<id[y];i++)b[i]+=z;
			}
		}else{
			int l=-INF,r=INF;
			while(l<r){
				int mid=l+r>>1;
				if(check(x,y,mid)>=z)r=mid;else l=mid+1;
			}
			printf("%d\n",l);
		}
	}
}
