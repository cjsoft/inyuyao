#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> PII;
#define fi first
#define se second

int n;
PII a[10000];
ll cal1(PII a, PII b, PII c)
{
	return a.fi * b.se + b.fi * c.se + c.fi * a.se;
}
ll cal2(PII a, PII b, PII c)
{
	return a.se * b.fi + b.se * c.fi + c.se * a.fi;
}
int main()
{
	freopen("area.in", "r", stdin);
	freopen("area.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld%lld", &a[i].fi, &a[i].se);
	ll ans = 0;
	for (int i = 1; i <= n - 1; i++)
		for (int j = i + 1; j <= n; j++)
		{
			ll ans1 = 0, ans2 = 0;
			for (int k = 1; k <= n; k++)
			{
				ans1 = max(ans1, cal1(a[i], a[k], a[j]) - cal2(a[i], a[k], a[j]));
				ans2 = max(ans2, cal2(a[i], a[k], a[j]) - cal1(a[i], a[k], a[j]));
			}
			ans = max(ans, ans1 + ans2);
		}
	if (ans & 1)
		printf("%lld.5\n", ans / 2);
	else
		printf("%lld.0\n", ans / 2);
}
