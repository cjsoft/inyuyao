#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#define ll long long
#define N 505

using namespace std;
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while ('0'<=ch&&ch<='9'){
		ret=ret*10-48+ch;
		ch=getchar();
	}
	return ret;
}

int n;
ll x[N],y[N];

int main(){
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	n=read();
	for (int i=1;i<=n;y[i++]=read()) x[i]=read();
	ll ans=0;
	for (int i=1;i<=n;++i)
		for (int j=i+1;j<=n;++j){
			ll mx=0,mn=0;
			for (int k=i+1;k<=n;++k){
				ll now=(x[k]-x[i])*(y[k]-y[j])-(x[k]-x[j])*(y[k]-y[i]);
				mx=max(mx,now);
				mn=min(mn,now);
			}
			ans=max(ans,mx-mn);
		}
	if (ans%2==0) printf("%lld.0\n",ans/2);
	else printf("%lld.5\n",ans/2);
	return 0;
}
