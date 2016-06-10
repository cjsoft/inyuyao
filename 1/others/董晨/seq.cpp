#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 100005
#define ll long long
int n,m,k,l,t,r;
ll a[N],b[N],x;
int main(){
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)scanf("%lld",&a[i]);
	while(m--){
		scanf("%d%d%d",&t,&l,&r);
		l++,r++;
		if(t==0){
			scanf("%lld",&x);
			for (int i=l;i<=r;i++)a[i]+=x;
		}
		if(t==1)for (int i=l;i<=r;i++)a[i]=-a[i];
		if(t==2){
			ll ans=0;
			for (int i=l;i<=r;i++)ans+=abs(a[i]);
			printf("%lld\n",ans);
		}
	}
}
