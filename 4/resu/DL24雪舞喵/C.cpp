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
int sread()
{
    int ans, t;
    char s[2000000];
    scanf("%d%s", &ans, s);
    while(~scanf("%d", &t))
    {
        ans *= 672672;
        ans ^= t;
    }
    return ans;
}
int rando(int x)
{
    return rand()/(double)RAND_MAX * x + 1;
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    srand(sread());
    printf("%d\n", rando(1000000005));
    return 0;
}
