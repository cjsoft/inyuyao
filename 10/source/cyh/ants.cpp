#include<bits/stdc++.h> 
#define MOD 1000000007LL
using namespace std;
typedef long long ll;
const int maxn=5000000,mod=1e9+7,p=137;
int n,x,a0,b0,c0,ans;
ll m,A[maxn+5],B[maxn+5],C[maxn+5],step[maxn+5];
ll tpow[maxn + 5];
inline void Init();
int main() {
    freopen("ants.in", "r", stdin);
    freopen("ants.out", "w", stdout);
    Init();
    // printf("  %lld\n", m);
    // for (int i = 1; i <= n; ++i) {
        // A[i] %= MOD;
    // }
    tpow[0] = 1;
    for (int i = 1; i <= maxn; ++i) tpow[i] = tpow[i - 1] << 1, tpow[i] %= MOD;
    int l = 1, r = n;
    ll lpos, rpos, ldelta, rdelta;
    ll ans = 0;
    while (l < r) {
        lpos = A[l]; rpos = A[r];
        ldelta = lpos; rdelta = m - rpos;
        // if (lpos % 76012403 < 1 || (m - lpos) % 76012403 < 1 || rdelta % 76012403 < 1 || rpos % mod < 1) puts("WARn");
        // if (ldelta < rdelta) {
        if (m - lpos > rpos) {
            ans = (ans + (m - lpos) % MOD * tpow[r - l] % MOD) % MOD;
        } else if (1 || ldelta >= rdelta) {
            ans = (ans + rpos % MOD * tpow[r - l] % MOD) % MOD;
        } else {
            ans = (ans + rpos * tpow[r - l - 1] % MOD) % MOD;
        }
        if (m - lpos > rpos)
            ++l;
        else
            --r;
    }
    lpos = A[l];
    if (lpos != m - lpos) ans = (ans + m % MOD) % MOD;
    else ans = (ans + (m >> 1)) % MOD;
    
    // lpos = A[l];
    // if (lpos < m - lpos) {
        // ans = (ans + m - lpos) % mod;
    // } else if (lpos > m - lpos) {

        // ans = (ans + lpos) % mod;
    // } else {
        // ans = (ans + lpos) % mod;
        // ans = (ans + lpos) % mod;
        
    // }
    printf("%lld\n", ans);
    return 0;
}
inline int myrand(){
	x=(1ll*a0*x+b0)%c0;
	return x;
}
void Init(){
	cin>>n>>x>>a0>>b0>>c0;
	for(int i=1;i<=(n+1)/2;i++)B[i]=B[i-1]+myrand()+5;
	m=B[(n+1)/2]<<1|1;
	for(int i=1;i<=n-(n+1)/2;i++)C[i]=m-(myrand()%(B[i]-B[i-1]-1)+B[i-1]+1);
	reverse(C+1,C+(n-(n+1)/2)+1);
	for(int i=1;i<=(n+1)/2;i++)A[i]=B[i];
	for(int i=1;i<=n-(n+1)/2;i++)A[i+(n+1)/2]=C[i];
}
