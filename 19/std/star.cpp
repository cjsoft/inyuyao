#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cassert>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll mod=1000000007;
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
// head

const int N=520;
VI f[N],g[N],h[N],spwd[N][N],l[N],r[N];
int val[N],n,d;
ll sl[N],sr[N],pw[N],fnv[N];
VI init(ll p) {
	ll r=1;
	p%=mod;
	if (p<0) p+=mod;
	VI ret;
	ret.pb(r);
	rep(i,1,n) {
		r=r*(p+1-i)%mod;
		if (r<0) r+=mod;
		ret.pb(r*fnv[i]%mod);
	}
	return ret;
}
VI add(const VI &a,const VI &b) {
	VI ret;
	rep(i,0,n) ret.pb((a[i]+b[i])%mod);
	return ret;
}
VI sub(const VI &a,const VI &b) {
	VI ret;
	rep(i,0,n) ret.pb((a[i]-b[i]+mod)%mod);
	return ret;
}
VI mul(const VI &a,const VI &b) {
	VI ret;
	rep(i,0,n) {
		ll c=0;
		rep(j,0,i+1) c=(c+(ll)a[j]*b[i-j])%mod;
		ret.pb(c);
	}
	return ret;
}
void init() {
	rep(j,0,d) spwd[0][j]=VI(n,0); pw[0]=1;
	f[0]=VI(n,0); g[0]=init(0); if (val[0]) h[0]=g[0]; else h[0]=f[0];
	rep(i,1,511) {
		pw[i]=pw[i-1]*d%mod;
		spwd[i][0]=VI(n,0);
		rep(j,1,d) if (val[j]) spwd[i][j]=add(spwd[i][j-1],init(j*pw[i-1]));
			else spwd[i][j]=spwd[i][j-1];
		f[i]=spwd[i][d-1];
		g[i]=f[i];
		if (val[0]) g[i]=add(g[i],init(0));
		f[i]=mul(f[i],g[i-1]); g[i]=mul(g[i],g[i-1]);
		h[i]=add(h[i-1],f[i]);
	}
}
char s[10100];
int num[10100];
void read(VI &x,ll &y) {
	scanf("%s",s);
	int l=strlen(s);
	rep(i,0,l) num[i]=s[i]-'0',y=(y*10+num[i])%mod;
	reverse(num,num+l);
	x.clear();
	while (l) {
		int t=0;
		per(i,0,l) {
			t=t*10+num[i];
			num[i]=t/d;
			t%=d;
		}
		x.pb(t);
		while (l&&num[l-1]==0) --l;
	}
}
// O(Ldn+Ln^2)
VI solve(VI d) {
	VI r=h[SZ(d)-1],v=init(0);
	per(i,0,SZ(d)) {
		if (d[i]!=0) {
			r=add(r,mul(mul(v,spwd[i+1][d[i]-1]),g[i]));
			if (val[0]&&i!=SZ(d)-1) r=add(r,mul(v,g[i]));
		}
		if (!val[d[i]]) break;
		v=mul(v,init(pw[i]*d[i]));
	}
	return r;
}
//O(2^nLn^2)
void addto(VI &a,VI b) {
	while (SZ(a)<SZ(b)) a.pb(0);
	rep(i,0,SZ(b)) a[i]+=b[i];
	int m=SZ(a);
	rep(i,0,m-1) {
		a[i+1]+=a[i]/d;
		a[i]%=d;
	}
	if (a[m-1]>=d) a.pb(a[m-1]/d),a[m-1]%=d;
}
int main() {
	freopen("star.in","r",stdin);
	freopen("star.out", "w", stdout); 
	scanf("%d%d",&n,&d);
	rep(i,0,d) scanf("%d",val+i);
	fnv[0]=1;
	rep(i,1,n) fnv[i]=fnv[i-1]*powmod(i,mod-2)%mod;
	init();
	rep(i,0,n) {
		read(l[i],sl[i]); read(r[i],sr[i]);
		addto(r[i],VI(1,1)); sr[i]++;
	}
	ll ret=0;
	rep(S,0,(1<<n)) {
		VI v(1,0); ll sv=0;
		rep(i,0,n) if (((S>>i)&1)==0) addto(v,l[i]),sv+=sl[i]; else addto(v,r[i]),sv+=sr[i];
		VI c=mul(sub(h[510],solve(v)),init(-sv+n-1));
		if (__builtin_popcount(S)%2==0) ret+=c[n-1]; else ret-=c[n-1];
	}
	ret%=mod;
	if (ret<0) ret+=mod;
	printf("%lld\n",ret);
}
