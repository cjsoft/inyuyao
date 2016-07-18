#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<iostream>
using namespace std;
typedef long double ld;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int> pa;
#define rep(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
#define rep2(i,a,b) for(int (i)=(a);(i)<(b);(i)++)
#define per(i,a,b) for(int (i)=(a);(i)>=(b);(i)--)
#define Rep(p,x) for(int (p)=head[(x)];(p);(p)=nxt[(p)])
#define Rep2(p,x) for(int (p)=cur[(x)];(p);(p)=nxt[(p)])
#define mp make_pair
#define w1 first
#define w2 second
#define ins insert
#define pb push_back
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
#define ms(x,y) memset(x,y,sizeof x)
#define lb(x) ((x)&(-x))
template<class T>inline void rread(T&num){
	num=0;T f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')num=num*10+ch-'0',ch=getchar();
	num*=f;
}
//*************************************************head*********************************************
const int maxn=5000000,mod=1e9+7,p=137;
int n,x,a,b,c,ans;
ll m,A[maxn+5],B[maxn+5],C[maxn+5],step[maxn+5];
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
inline void dfs(int x){
	if(x>n){
		ll mx=0;
		rep(i,1,n)mx=max(mx,step[i]);
		ans=(ans+mx)%mod;
		return;
	}
	step[x]=A[x];dfs(x+1);
	step[x]=m-A[x];dfs(x+1);
}
int main(){
	freopen("ants.in","r",stdin); 
	freopen("ants.out","w",stdout);
	Init();
	dfs(1);
	cout<<ans<<endl;
	return 0;
}
