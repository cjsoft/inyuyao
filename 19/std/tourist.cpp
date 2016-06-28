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

typedef long double ld;
const int N=101000;
ld ret,K,B,S,l,r,s;
ll x[N],y[N];
int n;
vector<pair<int,pair<ld,ld> > > vec;

ld gg(ld v) {
	ld x=(v*(r-l)+(l+r))*0.5;
	return (S+(K*l+B+K*x+B)*(x-l))*(s-S-(K*l+B+K*x+B)*(x-l));
}

void solve() {
	vec.clear();
	rep(i,0,n) {
		if (x[i]==x[i+1]) continue;
		ld k=((ld)y[i+1]-y[i])/(x[i+1]-x[i]),b=y[i]-k*x[i];
		vec.pb(mp(x[i],mp(k,b)));
		vec.pb(mp(x[i+1],mp(-k,-b)));
	}
	sort(all(vec));
	K=0,B=0,S=0;
	rep(i,0,SZ(vec)-1) {
		K+=vec[i].se.fi;
		B+=vec[i].se.se;
		l=vec[i].fi,r=vec[i+1].fi;
		ret+=(gg(-sqrt(0.6))*5+gg(sqrt(0.6))*5+gg(0)*8)/9*(r-l);
		S+=(K*l+B+K*r+B)*(r-l);
	}
}

int main() {
	freopen("tourist.in", "r", stdin);
	freopen("tourist.out", "w", stdout);
	scanf("%d",&n);
	rep(i,0,n) scanf("%lld%lld",x+i,y+i); x[n]=x[0],y[n]=y[0];
	rep(i,0,n) s+=x[i+1]*y[i]-x[i]*y[i+1];
	if (s<0) {
		s*=-1;
		reverse(x+1,x+n); reverse(y+1,y+n);
	}
	solve();
	rep(i,0,n+1) swap(x[i],y[i]);
	reverse(x+1,x+n); reverse(y+1,y+n);
	solve();
	printf("%.10lf\n",(double)(ret/s/s));
}
