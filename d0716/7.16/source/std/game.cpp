//#include <cmath>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <vector>
#include <set>
#include <algorithm>
#define mp make_pair
#define fi first
#define se second
 
using namespace std;

typedef long long int64;
typedef pair<int,int> PII;
const int MAXN=200005;
 
int n;
PII a[MAXN];
int64 dp[MAXN];

inline bool cmp(const PII &x,const PII &y)
{
	return min(x.fi,y.se)<min(x.se,y.fi);
}
 
int main()
{
	freopen ("game.in","r",stdin);
	freopen ("game.out","w",stdout);
	int testCase;
	for (scanf("%d",&testCase);testCase;testCase--)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d%d",&a[i].fi,&a[i].se);
		sort(a+1,a+n+1,cmp);
		int64 s=0;
		for (int i=1;i<=n;i++)
		{
			s+=a[i].fi;
			dp[i]=max(s,dp[i-1])+a[i].se;
		}
		cout<<dp[n]<<endl;
	}
	return 0;
}
