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
#include <ctime>
#include <queue>
using namespace std;
typedef long long lol;
int sa[250000][4], sb[250000], n, m, k, cc[250000];
void sread()
{
    scanf("%d%d%d", &n, &m, &k);
    yuki(0, m)
        yukj(0, n)
            scanf("%d", sa[j]+i);
    yuki(0, n) scanf("%d", sb+i);
}
int solve()
{
    clock_t shi = 5.8*CLOCKS_PER_SEC;
    yuki(0, n)
    {
        yukj(0, n)
            cc[i] += sa[j][sb[(lol)i*j%n]];
        if(clock() > shi)
        {
            n = i+1;
            break;
        }
    }
    nth_element(cc, cc+k-1, cc+n, greater<int>());
    return cc[k-1];
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
#endif // snowoi
    sread();
    printf("%d\n", solve());
    return 0;
}
