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
typedef pair<long double, int> pdi;
long double u;
pdi a[500][500];
int n, m;
void sread()
{
    scanf("%d%d%Lf", &n, &m, &u);
    yuki(0, m)
    {
        yukji(1, n)
        {
            scanf("%Lf", &a[i][j].ft);
            a[i][j].sc = j;
        }
        scanf("%Lf", &a[i][0].ft);
    }
}
void solve1()
{
    yuki(0, n)
    {
        puts("0");
    }
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
#endif // snowoi
    sread();
    solve1();
    return 0;
}
