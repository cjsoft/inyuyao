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
int n, m, q, head[263000], nxt[530000], tow[530000], dat[263000], alc, siz[263000], hvy[263000], fa[263000],
    alc2, dcr[263000], val[263000], frt[263000], dpt[263000], rot;
struct snow
{
    int a, b, c;
    snow operator+(const snow &rhs) const
    {
        return (snow){a+rhs.a, b+rhs.b, c+rhs.c};
    }
    snow& operator+=(const snow &rhs){return *this = *this + rhs;}
    int get() const
    {
        return a^b^c;
    }
};
struct node;
node *null;
struct node
{
    node *lht, *rht;
    int sz;
    node():lht(null), rht(null), sz(0) {}
    void upd(){sz = lht->sz+rht->sz;}
}*root[300100];
struct ctree
{
    ctree()
    {
        dpt[0] = -1;
        null = new node;
        null->lht = null;
        null->rht = null;
        fill(root, root+300100, null);
    }
    void insert(node *&cur, node *old, int l, int r, int v)
    {
        if(cur == null) cur = new node;
        if(l == r)
        {
            cur->sz = old->sz+1;
            return;
        }
        int m = l+((r-l) >> 1);
        if(v <= m)
        {
            cur->rht = old->rht;
            insert(cur->lht, old->lht, l, m, v);
        }else
        {
            cur->lht = old->lht;
            insert(cur->rht, old->rht, m+1, r, v);
        }
        cur->upd();
    }
    void make()
    {
        yukii(1, n)
            insert(root[i], root[i-1], 1, m, val[i]);
    }
    snow _find(node *old, node *cur, int l, int r, int k)
    {
        if(l == r) return (snow){0, cur->sz-old->sz, 0};
        if(cur->sz == old->sz) return (snow){0, 0, 0};
        int m = l+((r-l)>>1);
        if(k <= m)
            return (snow){0, 0, cur->rht->sz-old->rht->sz}+_find(old->lht, cur->lht, l, m, k);
        else
            return (snow){cur->lht->sz-old->lht->sz, 0, 0} + _find(old->rht, cur->rht, m+1, r, k);
    }
    snow find(int l, int r, int k)
    {
        if(l > r) swap(l, r);
        return _find(root[l-1], root[r], 1, m, k);
    }
}tree;
void add(int s, int t)
{
    nxt[++alc] = head[s];
    head[s] = alc;
    tow[alc] = t;
    nxt[++alc] = head[t];
    head[t] = alc;
    tow[alc] = s;
}
void sread()
{
    scanf("%d%d%d", &n, &m, &q);
    yukii(1, n) scanf("%d", dat+i);
    int aa, bb;
    yuki(1, n)
    {
        scanf("%d%d", &aa, &bb);
        add(aa, bb);
    }
    rot = 1+((n-1)/3);
}
void dfs1(int cur, int f, int dt)
{
    fa[cur] = f;
    dpt[cur] = dt;
    siz[cur] = 1;
    int hson = 0;
    for(int i = head[cur];i;i = nxt[i])
        if(tow[i] != f)
        {
            dfs1(tow[i], cur, dt+1);
            if(siz[tow[i]] > siz[hson]) hson = tow[i];
            siz[cur] += siz[tow[i]];
        }
    hvy[cur] = hson;
}
void dfs2(int cur, bool flag)
{
    val[++alc2] = dat[cur];
    dcr[cur] = alc2;
    if(flag) frt[cur] = frt[fa[cur]];
    else frt[cur] = cur;
    if(hvy[cur]) dfs2(hvy[cur], true);
    for(int i = head[cur];i;i = nxt[i])
        if(tow[i] != fa[cur] && tow[i] != hvy[cur])
            dfs2(tow[i], false);
}
snow ask(int x, int y, int k)
{
    if(frt[x] == frt[y]) return tree.find(dcr[x], dcr[y], k);
    if(dpt[fa[frt[x]]] > dpt[fa[frt[y]]]) return tree.find(dcr[frt[x]], dcr[x], k)+ask(fa[frt[x]], y, k);
    else return tree.find(dcr[frt[y]], dcr[y], k)+ask(x, fa[frt[y]], k);
}
int println(const snow &s)
{
    printf("%d %d %d\n", s.a, s.b, s.c);
    return s.get();
}
void solve()
{
    dfs1(rot, 0, 0);
    dfs2(rot, false);
    tree.make();
    int la = 0;
    int x, y, k;
    while(q--)
    {
        scanf("%d%d%d", &x, &y, &k);
        //la = println(ask(x^la, y^la, k^la));
        println(ask(x, y, k));
    }
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
#endif // snowoi
    sread();
    solve();
    return 0;
}
