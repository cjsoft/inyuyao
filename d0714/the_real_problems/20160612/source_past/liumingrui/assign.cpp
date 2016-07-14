#include <algorithm>
#include <cstdio>
#define rep(i,n) for(int i=1;i<=n;++i)
#define N 26
using namespace std;
typedef long long ll;
int now[N],tp[N],l[N],r[N],n,k;ll ans[2][N];bool in[N];
bool cmp(int x,int y){if(now[x]==now[y])return x<y;return now[x]>now[y];}
void dfs(int x){
	if(x==n+1){
		rep(i,n)tp[i]=i;
		sort(tp+1,tp+n+1,cmp);
		int ts=now[tp[k]],tr=0;
		rep(i,n)if(now[i]>ts||(now[i]==ts&&i<=tp[k])){
			++tr;if(tr%4==1||tr%4==0)++ans[0][i];else ++ans[1][i];
		}
		return;
	}
	for(int i=l[x];i<=r[x];++i){
		now[x]=i;dfs(x+1);
	}
}
int main(){
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	scanf("%d",&n);ll ttp=1;
	rep(i,n)scanf("%d",l+i);
	rep(i,n)scanf("%d",r+i);
	rep(i,n)ttp*=0ll+r[i]-l[i]+1;
	scanf("%d",&k);
	dfs(1);
	rep(i,n)printf("%lf %lf\n",1.0*ans[0][i]/ttp,1.0*ans[1][i]/ttp);
	return 0;
}
