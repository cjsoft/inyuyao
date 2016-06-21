#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double db;
const int P=1000000007;
const int N=110000;
inline int Pow(int a,int b){
	int c=1;
	for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
	return c;
}
int fac[N];
int inv[N];
int n;
int a[N];
int main(){
	freopen("huffman.in","r",stdin);
	freopen("huffman.out","w",stdout);
	scanf("%d",&n);
	fac[0]=1;
	rep(i,1,n)fac[i]=fac[i-1]*1ll*i%P;
	inv[n]=Pow(fac[n],P-2);
	per(i,n-1,0)inv[i]=inv[i+1]*1ll*(i+1)%P;
	rep(i,1,n)inv[i]=inv[i]*1ll*fac[i-1]%P;
	rep(i,3,n)inv[i]=(inv[i-1]+inv[i])%P;
	int ans=0;
	rep(i,1,n){
		int x;scanf("%d",&x);
		ans=(ans+inv[n]*2ll*x)%P;
	}
	rep(i,2,n){
		ans=ans*1ll*((i*1ll*(i-1)/2)%P)%P;
	}
	printf("%d\n",ans);
	return 0;
}



