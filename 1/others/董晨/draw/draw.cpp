#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define N 2005
#define ll long long
int n,m,k,l,t,s,x1,y1,x2,y2,id,x,y;
ll ans;
int a[N][N][4],root[N];
struct node{
	int l,r,s;
}T[N*20];
void ins(int &i,int l,int r,int x,int y){
	T[++id]=T[i];i=id;
	if(l==x&&r==y){
		T[i].s++;
		return;
	}
	int mid=l+r>>1;
	if(y<=mid)ins(T[i].l,l,mid,x,y);
	else if(x>mid)ins(T[i].r,mid+1,r,x,y);
	else{
		ins(T[i].l,l,mid,x,mid);
		ins(T[i].r,mid+1,r,mid+1,y);
	}
}
int que(int i,int l,int r,int x){
	if(!i)return 0;
	if(l==r)return T[i].s;
	int mid=l+r>>1;
	if(x<=mid)return que(T[i].l,l,mid,x)+T[i].s;
	else return que(T[i].r,mid+1,r,x)+T[i].s;
}
int main(){
	freopen("draw.in","r",stdin);
	freopen("draw.out","w",stdout);
	scanf("%d%d",&n,&m);
	n++;
	for (int i=1;i<=m;i++){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		x1++,y1++,x2++,y2++;
		if(x1==x2){
			if(y1>y2)swap(y1,y2);
			for (int j=y1;j<=y2;j++){
				a[x1][j][0]=y1;
				a[x1][j][2]=y2;
			}
		}else{
			if(x1>x2)swap(x2,x1);
			for (int j=x1;j<=x2;j++){
				a[j][y1][1]=x1;
				a[j][y1][3]=x2;
			}
		}
	}
	for (int k=2-n;k<=n-2;k++){
		for (int i=1;i<=id;i++)T[i].l=T[i].r=T[i].s=0;
		id=0;
		if(k<0)x=1-k,m=k+n;else x=1,m=n-k;
		y=k+x;
		l=0;
		while(max(x,y)<=n){
			l++;
			root[l]=root[l-1];
			if(a[x][y][0]&&a[x][y][1]){
				t=min(y-a[x][y][0],x-a[x][y][1]);
				ans+=que(root[l-1],1,m,l)-que(root[l-t-1],1,m,l);
			}
			if(a[x][y][2]&&a[x][y][3]){
				t=min(a[x][y][2]-y,a[x][y][3]-x);
				if(t)ins(root[l],1,m,l,l+t);
			}
			x++,y++;
		}
	}
	printf("%lld\n",ans);
}
