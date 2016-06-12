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
int n, head[400], nxt[800], tow[800], dat[800], fa[400], fdat[400], alc, dpt[400], snow[400];
lol ans;
void add(int s, int t, int w)
{
    nxt[++alc] = head[s];
    head[s] = alc;
    tow[alc] = t;
    dat[alc] = w;
    nxt[++alc] = head[t];
    head[t] = alc;
    tow[alc] = s;
    dat[alc] = w;
}
void sread()
{
    scanf("%d", &n);
    int s, t, w;
    yuki(1, n)
    {
        scanf("%d%d%d", &s, &t, &w);
        add(s, t, w);
    }
}
void dfs(int cur, int f, int fd, int dt)
{
    fa[cur] = f;
    fdat[cur] = fd;
    dpt[cur] = dt;
    for(int i = head[cur];i;i = nxt[i])
        if(tow[i] != f)
            dfs(tow[i], cur, dat[i], dt+1);
}
int get(int s, int t)
{
    int cal = 0;
    while(s != t)
    {
        if(dpt[s] > dpt[t])
        {
            snow[cal++] = fdat[s];
            s = fa[s];
        }else
        {
            snow[cal++] = fdat[t];
            t = fa[t];
        }
    }
    if(!(cal & 1)) return 0;
    sort(snow, snow+cal);
    return snow[cal>>1];
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("draw.in", "r", stdin);
    freopen("draw.out", "w", stdout);
#endif // snowoi
    sread();
    dfs(1, 0, 0, 0);
    yukii(1, n)
        yukji(i+1, n)
            ans += get(i, j);
    printf("%lld\n", ans);
    return 0;
}
