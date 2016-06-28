#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cassert>
#include <iostream>
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
ll powmod(ll a,ll b) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
// head

VI v[10];
int p[1010],c[30],d[30],n[5],m;
char s[1010];
double lg[2010][2],pw[2010],qw[2010];
int vis[2010][2],T;
double solve(int S) {
	n[0]=n[1]=0;
	rep(i,0,m) n[d[i]=(S>>i)&1]++;
	double ret=0;
	ret+=log(m);
	int pr=d[p[0]]==0?1001:999;
	++T;
	rep(i,1,1000) {
		int pd=d[p[i-1]];
		if (vis[pr][pd]!=T) {
			vis[pr][pd]=T;
			lg[pr][pd]=log(n[pd^1]+n[pd]*pw[pr]);
		}
		ret+=lg[pr][pd];
		if (d[p[i]]!=pd) pr=1000;
		else ret+=qw[pr];
		pr+=d[p[i]]==0?1:-1;
	}
	return ret;
}
int _;
int main() {
	freopen("rng.in", "r", stdin);
	freopen("rng.out", "w", stdout);
	pw[1000]=1;
	rep(i,1,1001) {
		pw[1000+i]=pw[999+i]*0.5,pw[1000-i]=pw[1001-i]*2/3;
		qw[1000+i]=qw[999+i]+log(2),qw[1000-i]=qw[1001-i]+log(1.5);
	}
	scanf("%d",&m);
	rep(_,0,100) {
		scanf("%s",s);
		rep(i,0,1000) p[i]=s[i]-'a';
		double ret=1e30; int res=-1;
		rep(rd,0,10) {
			int ss=0;
			rep(i,0,m) ss|=(rand()&1)<<i;
			double cur=solve(ss);
			int step=0,v=0;
			while (1) {
				int ns=ss^(1<<(v%m));
				double cv=solve(ns);
				v++;
				if (cv<cur) {
					cur=cv; ss=ns;
					step=0;
				} else step++;
				if (step>=m) break;
			}
			if (cur<ret) ret=cur,res=ss;
		}
		rep(j,0,m) putchar(((res>>j)&1)?'C':'V');
		puts("");
	}
}
