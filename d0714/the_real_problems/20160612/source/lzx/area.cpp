#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long LL;
const int N = 1e5 + 10;
struct Dot
{
	LL x, y;
	Dot (LL _x = 0, LL _y = 0) {x = _x, y = _y;}
	void read()
	{
		scanf("%lld%lld", &x, &y);
	}
} P[N], Stk[N], stk[N];
int top, Top, n;

Dot operator- (Dot a, Dot b) {return Dot(a.x - b.x, a.y - b.y);}
LL operator^ (Dot a, Dot b) {return a.x * b.y - a.y * b.x;}

void init()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i)
		P[i].read();
}

LL cross(Dot c, Dot a, Dot b)
{
	return (a - c) ^ (b - c);
}

void solve()
{
	LL ans = 0;
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= n; ++j)
			for (int k = 1; k <= n; ++ k) if (i == j || cross(P[i], P[j], P[k]) > 0)
				for (int z = 1; z <= n; ++ z) if (j == k || cross(P[j], P[k], P[z]) > 0)
					ans = max(ans, (P[i] ^ P[j]) + (P[j] ^ P[k]) + (P[k] ^ P[z]) + (P[z] ^ P[i]));
	if (ans & 1)
		printf("%lld.5", ans >> 1);
	else 
		printf("%lld.0", ans >> 1);
}

int main()
{
	freopen("area.in", "r", stdin);
	freopen("area.out", "w", stdout);
	init();
	solve();
}