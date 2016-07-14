#include <cstdio>
#include <ctime>
#include <cmath>
#include <algorithm>
using namespace std;
#define N 100000
#define inf 1e9

bool vis[N];
int T,n,m,x,y,S[N];
double ans;

struct node{
	int x,y;
}a[N];

struct gene{
	int no[4];
	double s;
}g[505];

long long calc(int x){return 1ll*x*x;}

double dist(node a,node b){
	return sqrt(1.0*calc(a.x-b.x)+calc(a.y-b.y));
}

long long multi(node s,node a,node b){
	return 1ll*(a.x-s.x)*(b.y-s.y)-1ll*(b.x-s.x)*(a.y-s.y);
}

bool cmp(node p,node q){
	long long tmp=multi(a[0],p,q);
	if(tmp>0) return 1;
	else if(tmp==0) return dist(a[0],p)<dist(a[0],q);
	else return 0;
}

int rnd(){
	int x=rand()%m+1;
	while(vis[x]) x=rand()%m+1;
	return x;
}

bool cmp1(gene a,gene b){return a.s>b.s;}

double getS(int no){
	long long t1=multi(a[S[g[no].no[0]]],a[S[g[no].no[1]]],a[S[g[no].no[2]]]);
	long long t2=multi(a[S[g[no].no[0]]],a[S[g[no].no[2]]],a[S[g[no].no[3]]]);
	return 1.0*(t1+t2)/2;
}	

void solve(){
	for(int i=1;i<=500;i++){
		for(int j=0;j<4;j++){
			g[i].no[j]=rnd();
			vis[g[i].no[j]]=1;
		}
		for(int j=0;j<4;j++) vis[g[i].no[j]]=0;
		for(int j=0;j<4;j++)
			for(int k=0;k<4-j-1;k++)
				if(g[i].no[k]>g[i].no[k+1]) swap(g[i].no[k],g[i].no[k+1]);
		g[i].s=getS(i);
	}
	T=2000;
	while(T--){
		sort(g+1,g+500+1,cmp1);
		ans=max(ans,g[1].s);
		for(int i=251;i<=500;i++){
			int x=rand()%250+1;
			int y=rand()%250+1;
			while(x==y) y=rand()%250+1;
			g[i].no[0]=g[x].no[0];
			g[i].no[1]=g[x].no[1];
			g[i].no[2]=g[y].no[2];
			g[i].no[3]=g[y].no[3];
			g[i].s=getS(i);
		}
		for(int i=1;i<=500;i++){
			double tmp=(rand()%100+1)/100.0;
			if(tmp<=0.3){
				for(int j=0;j<4;j++){
					g[i].no[j]=rnd();
					vis[g[i].no[j]]=1;
				}
				for(int j=0;j<4;j++) vis[g[i].no[j]]=0;
				for(int j=0;j<4;j++)
					for(int k=0;k<4-j-1;k++)
						if(g[i].no[k]>g[i].no[k+1]) swap(g[i].no[k],g[i].no[k+1]);
				g[i].s=getS(i);
			}
		}
	}
	printf("%.1lf\n",ans);
}		
		
int main(){
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	srand(time(0));
	scanf("%d",&n);
	if(n<=2){
		printf("0.0\n");
		return 0;
	}
	a[0].x=a[0].y=inf;
	for(int i=1;i<=n;i++){
		scanf("%d %d",&a[i].x,&a[i].y);
		if(a[i].y<a[0].y) a[0].x=a[i].x,a[0].y=a[i].y;
		else if(a[i].y==a[0].y&&a[i].x<a[0].x) a[0].x=a[i].x;
	}
	sort(a+1,a+n+1,cmp);
	S[m=1]=1;
	S[++m]=2;
	for(int i=3;i<=n;i++){
		while(m>1&&multi(a[S[m-1]],a[S[m]],a[i])<=0) m--;
		S[++m]=i;
	}
	if(multi(a[S[m-1]],a[S[m]],a[1])<=0) m--;
	//for(int i=1;i<=m;i++) printf("%d %d\n",a[S[i]].x,a[S[i]].y);
	solve();
	return 0;
}
