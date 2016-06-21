#include<bits/stdc++.h> 
using namespace std;
typedef long long ll;
const int maxn=5000000,mod=1e9+7,p=137;
int n,x,a0,b0,c0,ans;
ll m,A[maxn+5],B[maxn+5],C[maxn+5],step[maxn+5];
inline int myrand(){
	x=(1ll*a0*x+b0)%c0;
	return x;
}
inline void Init(){
	cin>>n>>x>>a0>>b0>>c0;
	for(int i=1;i<=(n+1)/2;i++)B[i]=B[i-1]+myrand()+5;
	m=B[(n+1)/2]<<1|1;
	for(int i=1;i<=n-(n+1)/2;i++)C[i]=m-(myrand()%(B[i]-B[i-1]-1)+B[i-1]+1);
	reverse(C+1,C+(n-(n+1)/2)+1);
	for(int i=1;i<=(n+1)/2;i++)A[i]=B[i];
	for(int i=1;i<=n-(n+1)/2;i++)A[i+(n+1)/2]=C[i];
}
inline void dfs(int x){
	if(x>n){
		ll mx=0;
		for(int i=1;i<=n;i++)mx=max(mx,step[i]);
		ans=(ans+mx)%mod;
		return;
	}
	step[x]=A[x];dfs(x+1);
	step[x]=m-A[x];dfs(x+1);
}
int main(){
	Init();
	dfs(1);
	cout<<ans<<endl;
	return 0;
}
