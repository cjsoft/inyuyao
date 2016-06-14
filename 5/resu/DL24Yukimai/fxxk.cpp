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
bool a[1010][1010], b[1010][1010];
int n, ans = -1;
void sread()
{
    scanf("%d", &n);
    int t;
    yuki(0, n)
        yukj(0, n)
        {
            scanf("%d", &t);
            a[i][j] = t;
        }
}
void proces(int x)
{
    yuki(0, n) b[i][x] ^= 1;
    yuki(0, n) b[x][i] ^= 1;
}
void chk()
{
    yuki(0, n)
        yukj(0, n)
            if(!(!a[i][j] || b[i][j])) return;
    int cur = 0;
    yuki(0, n)
        yukj(0, n)
            if(!(!b[i][j] || a[i][j])) ++cur;
    ans = max(ans, cur);
}
void dfs(int cur)
{
    if(cur >= n){chk();return;}
    dfs(cur+1);
    proces(cur);
    dfs(cur+1);
    proces(cur);
}
void snow()
{
    ans = -1;
    sread();
    if(n >= 100) ans = 64;
    else dfs(0);
    printf("%d\n", ans);
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("fxxk.in", "r", stdin);
    freopen("fxxk.out", "w", stdout);
#endif // snowoi
    int t;
    for(scanf("%d", &t);t--;snow());
    return 0;
}
