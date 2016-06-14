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
#include <cstdlib>
#include <cmath>
using namespace std;
typedef long long lol;
int n, q, raw[80000], tmp[80000];
void sread()
{
    scanf("%d", &n);
    yuki(0, n)
        scanf("%d", raw+i);
    scanf("%d", &q);
}
void add(int l, int r, int v)
{
    yukii(l, r) raw[i] += v;
}
int ask(int l, int r, int k)
{
    int m = r-l+1;
    memcpy(tmp, raw+l, m<<2);
    nth_element(tmp, tmp+k-1, tmp+m);
    return tmp[k-1];
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("kth.in", "r", stdin);
    freopen("kth.out", "w", stdout);
#endif // snowoi
    sread();
    int id, l, r, v;
    while(q--)
    {
        scanf("%d%d%d%d", &id, &l, &r, &v);
        if(id == 1) add(l-1, r-1, v);
        else printf("%d\n", ask(l-1, r-1, v));
    }
    return 0;
}
