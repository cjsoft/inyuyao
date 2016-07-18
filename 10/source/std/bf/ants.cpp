#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=5000000,mod=1e9+7,p=137;
int n,x,a,b,c,ans,bin[maxn+5];
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
struct node{
	ll x;
	int flag;
	inline node(){x=flag=0;}
	inline node(ll _x,int _flag){x=_x;flag=_flag;}
	inline friend bool operator<(node a,node b){return a.x<b.x;}
}q[maxn<<1];
inline void Solve(){
	bin[0]=1;
	for(int i=1;i<=n;i++)bin[i]=Add(bin[i-1],bin[i-1]);
	int tot=0;
	for(int i=1;i<=n;i++)q[++tot]=node(min(A[i],m-A[i]),1),q[++tot]=node(max(A[i],m-A[i]),-1);
	sort(q+1,q+tot+1);
	int cnt1=0,cnt2=0;
	for(int i=1;i<=tot;i++){
		if(q[i].flag==1)cnt1+=q[i].flag;
		cnt2=(i-(q[i].flag==-1)-cnt1)>>1;
		if(cnt1+cnt2==n)ans=Add(ans,q[i].x%mod*bin[cnt2]%mod);
		if(q[i].flag==-1)cnt1+=q[i].flag;
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
