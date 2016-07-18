#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=5000000,mod=1e9+7,p=137;
int n,ans,bin[maxn+5],x,a,b,c;
ll m,A[maxn+5],B[maxn+5],C[maxn+5];
inline int myrand(){
	x=(1ll*a*x+b)%c;
	return x;
}
inline void Init(){
	cin>>n>>x>>a>>b>>c;
	for(int i=1;i<=(n+1)/2;i++)B[i]=B[i-1]+myrand()+5;
	m=B[(n+1)/2]<<1|1;
	for(int i=1;i<=n-(n+1)/2;i++)C[i]=m-(myrand()%(B[i]-B[i-1]-1)+B[i-1]+1);
	reverse(C+1,C+(n-(n+1)/2)+1);
	for(int i=1;i<=(n+1)/2;i++)A[i]=B[i];
	for(int i=1;i<=n-(n+1)/2;i++)A[i+(n+1)/2]=C[i];
}
inline int Add(int a,int b){
	return a+b>=mod?a+b-mod:a+b;
}
inline void Update(int i,int j){
	if(i-j>=0)ans=Add(ans,max(A[i],m-A[j])%mod*bin[i-j]%mod);
	if(j==i+1)ans=Add(ans,max(A[i],m-A[j])%mod);
}
inline void Solve(){
	bin[0]=1;for(int i=1;i<=n;i++)bin[i]=Add(bin[i-1],bin[i-1]);
	int i=1,j=n;Update(i,j);
	while(i<n||j>1){
		if(i<n){
			if(j==1||A[i+1]<m-A[j-1])i++;
			else j--;
		}else j--;
		Update(i,j);
	}
	printf("%d\n",ans);
}
int main(){
	freopen("ants.in","r",stdin);
	freopen("ants.out","w",stdout);
	Init();
	Solve();
	return 0;
}
