#include<bits/stdc++.h>
using namespace std;

#define LL long long
#define For(i,j,k) for (int i=j;i<=k;i++)
#define foR(i,j,k) for (int i=j;i>=k;i--)
#define mem(a,x) memset(a,x,sizeof(a))
#define sqr(x) (x)*(x)
const int inf=0x7fffffff,N=101000;
struct node{LL x,y;}a[N],mi;
int n,t,b[N];
LL ans;

template <typename T>void cmax(T &a,T b){a=max(a,b);}
template <typename T>void cmin(T &a,T b){a=min(a,b);}
bool operator <(node a,node b){return a.x<b.x||a.x==b.x&&a.y<b.y;}
LL operator *(node a,node b){return a.x*b.y-a.y*b.x;}
node operator -(node a,node b){return node{b.x-a.x,b.y-a.y};}
LL dis(node a,node b){return sqr(a.x-b.x)+sqr(a.y-b.y);}
LL S(int x,int y,int z){return abs((a[b[x]]-a[b[y]])*(a[b[x]]-a[b[z]]));}
LL s(node a,node b,node c){return abs((a-b)*(a-c));}
bool cmp(node a,node b){return (mi-a)*(mi-b)>0||(mi-a)*(mi-b)==0&&dis(mi,a)<dis(mi,b);}

template <typename T>
void read(T &x){
	char c;T f=1;
	while (!isdigit(c=getchar())) if (c=='-') f=-1;
	x=c-'0';
	while (isdigit(c=getchar())) x=x*10+c-'0';
	x*=f;
}

void tubao(){
	mi=node{inf,inf};
	For (i,1,n) cmin(mi,a[i]);
	sort(a+1,a+n+1,cmp);
	For (i,1,n){
		b[++t]=i;
		while (t>=4&&(a[b[t-2]]-a[b[t]])*(a[b[t-2]]-a[b[t-1]])>=0)
			b[t-1]=b[t],--t;
	}
}

int main(){
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	scanf("%d\n",&n);
	For (i,1,n) read(a[i].x),read(a[i].y);
	tubao();
	For (i,1,t) b[i+t]=b[i];
	if (t>=4){
	    int i=1,j=3,k=2,l=4;
	    while (i<=t){
	        LL sk=0,sl=0,sn=0;
	        while (j<i+t-1){
	            int lk=k,ll=l;sk=S(i,j,k),sl=S(i,j,l);
	            while (k+1<j&&S(i,j,k+1)>sk) sk=S(i,j,++k);
	            while (l+1<i+t&&S(i,j,l+1)>sl) sl=S(i,j,++l);
	            if (sk+sl<=sn) 
	                {k=lk,l=ll;break;}
	                else sn=sk+sl;
	            ++j;
	        }
	        --j,cmax(ans,sn),++i;
	    }
	}
	else ans=S(1,2,3);
	printf("%lld.%lld\n",ans/2,ans%2);
	return 0;
}
