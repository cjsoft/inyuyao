#define yuki(x, y) for(int i = x; i < (y); ++i)
#define yukj(x, y) for(int j = x; j < (y); ++j)
#define yukii(x, y) for(int i = x; i <= (y); ++i)
#define yukji(x, y) for(int j = x; j <= (y); ++j)
#define yuk(x, y, z) for(int x = y; x < (z); ++x)
#define yui(x, y, z) for(int x = y; x >= (z); --x)
#define sclr(x) memset(x, 0, sizeof(x))
#define sclr1(x) memset(x, -1, sizeof(x))
#define scl(x, y) memset(x, y, sizeof(x))
#define ft first
#define sc second
#define mp make_pair
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long lol;
int n, cnt[22];
lol ans;
lol pf(int x)
{
    return (lol)x*x;
}
void proces(int x)
{
    yuki(0, 22)
        if(x & (1<<i)) ++cnt[i];
}
void sread()
{
    scanf("%d", &n);
    int t;
    yuki(0, n)
    {
        scanf("%d", &t);
        proces(t);
    }
}
void solve()
{
    int cur = -1;
    while(cur)
    {
        cur = 0;
        yui(i, 21, 0)
        {
            cur <<= 1;
            if(cnt[i]) ++cur, --cnt[i];
        }
        ans += pf(cur);
    }
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif // snowoi
    sread();
    solve();
    printf("%lld\n", ans);
    return 0;
}
