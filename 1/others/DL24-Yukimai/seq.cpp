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
typedef long long lol;
#ifdef unix
inline void readl(lol &x){scanf("%lld", &x);}
inline void putl(lol x){printf("%lld\n", x);}
#else
inline void readl(lol &x){scanf("%I64d", &x);}
inline void putl(lol x){printf("%I64d\n", x);}
#endif // unix
using namespace std;
/*struct node
{
    int l, r;
    lol maxs, mins, lz;
    bool flip;
    node *lht, *rht;
    node(int il = 0, int ir = 0):l(il), r(ir), maxs(0ll), mins(0ll), lz(0ll), flip(false), lht(0), rht(0) {}
    node(int il, int ir, int iv):l(il), r(ir), maxs(0ll), mins(0ll), lz(0ll), flip(false), lht(0), rht(0)
    {
        if(iv < 0) mins = iv;
        else maxs = iv;
    }
    void upd()
    {
        maxs = lht->maxs+rht->maxs;
        mins = lht->mins+rht->mins;
    }
    void pushd()
    {
        if(lz)
        {

        }
        if(flip)
        {
            int t = lht->mins;
            lht->mins = -rht->maxs;
        }
    }
}*root;*/
int n, m;
lol raw[100010];
/*node *mktree(int l, int r)
{
    if(l == r) return new node(l, r, raw[l]);
    node *ans = new node(l, r);
    int m = l+((r-l)>>1);
    ans->lht = mktree(l, m);
    ans->rht = mktree(m+1, r);
    ans->upd();
    return ans;
}*/
void sread()
{
    scanf("%d%d", &n, &m);
    yuki(0, n)
        readl(raw[i]);
    //root = mktree(0, n-1);
}
lol snow(const lol &x)
{
    return x < 0 ? -x : x;
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("seq.in", "r", stdin);
    freopen("seq.out", "w", stdout);
#endif // snowoi
    sread();
    int a, b, c;
    lol d;
    while(m--)
    {
        scanf("%d%d%d", &a, &b, &c);
        switch(a)
        {
        case 0:
            readl(d);
            yukii(b, c)
                raw[i] += d;
            break;
        case 1:
            yukii(b, c)
                raw[i] = -raw[i];
            break;
        case 2:
            d = 0;
            yukii(b, c)
                d += snow(raw[i]);
            putl(d);
        }
    }
    return 0;
}
