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
#define maaap make_pair
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stdarg.h>
using namespace std;
int n, m, ans;
int mp[2010][2010], mp2[2010][2010];
inline void g(int &x)
{
    char ch = getchar();
    while(ch < '0' || ch >'9') ch = getchar();
    x = 0;
    while(ch >= '0' && ch <= '9')
    {
        x = (x<<3)+(x<<1);
        x += ch - '0';
        ch = getchar();
    }
}
void getint(int num, ...)
{
    va_list v;
    va_start(v, num);
    while(num--)
    {
        int *cur = va_arg(v, int*);
        g(*cur);
    }
    va_end(v);
}
void sread()
{
    getint(2, &n, &m);
    int a, b, c, d;
    while(m--)
    {
        getint(4, &a, &b, &c, &d);
        if(a > c) swap(a, c);
        if(b > d) swap(b, d);
        if(a == c)
            yukii(b+1, d)
                mp[a][i] = 1;
        else
            yukii(a+1, c)
                mp2[i][b] = 1;
    }
    yukii(0, n)
        yukji(1, n)
            mp[i][j] += mp[i][j-1];
    yukii(0, n)
        yukji(1, n)
            mp2[j][i] += mp2[j-1][i];
}
bool chk1(int x1, int x2, int y)
{
    return mp2[x2][y]-mp2[x1][y] == x2-x1;
}
bool chk2(int x, int _11, int y2)
{
    return mp[x][y2]-mp[x][_11] == y2-_11;
}
int chk(int x, int y, int l)
{
    return chk1(x, x+l, y) && chk1(x, x+l, y+l) && chk2(x, y, y+l) && chk2(x+l, y, y+l);
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("draw.in", "r", stdin);
    freopen("draw.out", "w", stdout);
#endif // snowoi
    sread();
    yuk(k, 1, n+1)
        yukii(0, n-k)
            yukji(0, n-k)
                ans += chk(i, j, k);
    printf("%d\n", ans);
    return 0;
}
