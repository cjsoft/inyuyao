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
int n, q, snow[300][300], pos[300][300], miao[300][300], lz[300], tmp[600], tmp2[600], bsiz, asiz, fsiz, tsiz, tsiz2;
int rando()
{
    double t = rand()/(double)RAND_MAX, p = sqrt(n)/100;
    return t*p*2-p;
}
void sread()
{
    scanf("%d", &n);
    srand(n^672672);
    bsiz = sqrt(n)+rando();
    yuki(0, n)
    {
        if(fsiz >= bsiz) ++asiz, fsiz = 0;
        scanf("%d", snow[asiz]+fsiz++);
    }
    scanf("%d", &q);
}
void pre()
{
    memcpy(miao, snow, sizeof(snow));
    yuki(0, asiz)
        sort(miao[i], miao[i]+bsiz);
    sort(miao[asiz], miao[asiz]+fsiz);
}
void add(int l, int r, int v)
{
    int bb = l/bsiz, eb = r/bsiz, bv = l%bsiz, ev = r%bsiz;
    while(bb < eb)
    {
        if(bv)
        {
            if(lz[bb])
            {
                yuki(0, bsiz) snow[bb][i] += lz[bb];
                lz[bb] = 0;
            }
            yuki(bv, bsiz)
                snow[bb][i] += v;
            memcpy(miao[bb], snow[bb], sizeof(snow[bb]));
            sort(miao[bb], miao[bb]+bsiz);
        }else
        {
            lz[bb] += v;
        }
        ++bb;
        bv = 0;
    }
    if(lz[bb])
    {
        if(bb == asiz) yuki(0, fsiz) snow[bb][i] += lz[bb];
        else yuki(0, bsiz) snow[bb][i] += lz[bb];
        lz[bb] = 0;
    }
    yukii(bv, ev) snow[bb][i] += v;
    memcpy(miao[bb], snow[bb], sizeof(snow[bb]));
    sort(miao[bb], miao[bb]+bsiz);
}
void gettmp(int bb, int eb, int bv, int ev)
{
    tsiz = 0, tsiz2 = 0;
    while(bb < eb)
    {
        if(bv)
        {
            yuki(bv, bsiz) tmp[tsiz++] = snow[bb][i]+lz[bb];
        }else
            tmp2[tsiz2++] = bb;
        ++bb;
        bv = 0;
    }
    yukii(bv, ev) tmp[tsiz++] = snow[bb][i]+lz[bb];
    sort(tmp, tmp+tsiz);
}
int chk(int v)
{
    int ans = lower_bound(tmp, tmp+tsiz, v)-tmp;
    yuki(0, tsiz2) ans += lower_bound(miao[tmp2[i]], miao[tmp2[i]]+bsiz, v-lz[tmp2[i]])-miao[tmp2[i]];
    return ans;
}
int ask(int l, int r, int k)
{
    gettmp(l/bsiz, r/bsiz, l%bsiz, r%bsiz);
    int ansl = -5000000, ansr = 5000000;
    while(ansl+1 < ansr)
    {
        int m = ansl+((ansr-ansl)>>1);
        int t = chk(m)+1;
        if(t <= k) ansl = m;
        else ansr = m;
    }
    return ansl;
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("kth.in", "r", stdin);
    freopen("kth.out", "w", stdout);
#endif // snowoi
    sread();
    pre();
    int id, l, r, v;
    while(q--)
    {
        scanf("%d%d%d%d", &id, &l, &r, &v);
        if(id == 1) add(l-1, r-1, v);
        else printf("%d\n", ask(l-1, r-1, v));
    }
    return 0;
}
