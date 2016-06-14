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
#include <queue>
#include <algorithm>
using namespace std;
typedef long long lol;
typedef pair<int, int> pii;
const int M = 1000000007, inf = 0x7f7f7f7f, nya = 500000004;
int n, m, tat, head[6760000], nxt[31200000], tow[31200000], dat[31200000], dis[6760000], alc, ans, curt, maxd;
bool vis[6760000];
priority_queue<pii, vector<pii>, greater<pii> > pq;
vector<pii> q;
int enc(int x, int y){return x*n+y;}
int splus(int a, int b)
{
    return ((lol)a+b)%M;
}
int& eplus(int &a, int b)
{
    return a = splus(a, b);
}
int stimes(int a, int b)
{
    return (lol)a*b%M;
}
void add(int s, int t, int w)
{
    nxt[++alc] = head[s];
    head[s] = alc;
    tow[alc] = t;
    dat[alc] = w;
}
#ifdef snowoi
void debug()
{
    yukii(2, n)
    {
        yukji(0, n) printf("%d ", dis[enc(j, i)]);
        puts("");
    }
}
void debug2(vector<pii> &v)
{
    yuki(0, v.size())
    {
        printf("[%d %d] ", v[i].ft, v[i].sc);
    }
    puts("");
}
#endif // snowoi
void sread()
{
    scanf("%d%d%d", &n, &m, &tat);
    int s, t, w;
    yuki(0, m)
    {
        scanf("%d%d%d", &s, &t, &w);
        yukj(0, n)
        {
            add(enc(j, s), enc(j+1, t), w);
            add(enc(j, t), enc(j+1, s), w);
        }
    }
}
void dij()
{
    scl(dis, 0x7f);
    dis[enc(0, 1)] = 0;
    pq.push(mp(0, 1));
    while(!pq.empty())
    {
        int cur = pq.top().sc;
        pq.pop();
        if(vis[cur]) continue;
        vis[cur] = true;
        for(int i= head[cur];i;i = nxt[i])
            if(!vis[tow[i]] && dis[tow[i]] > dis[cur]+dat[i])
            {
                dis[tow[i]] = dis[cur]+dat[i];
                pq.push(mp(dis[tow[i]], tow[i]));
            }
    }
}
bool cmp(const pii &a, const pii &b, const pii &c)
{
    return b.sc >= a.sc || ((double)a.sc-b.sc)/(a.ft-b.ft) >= ((double)b.sc-c.sc)/(b.ft-c.ft);
}
int sget(const pii &a, const pii &b)
{
    return (a.sc-b.sc)/(b.ft-a.ft);
}
void addans(const pii &d, int tm)
{
    eplus(ans, stimes(nya, stimes(tm-curt+1, splus(splus(d.sc, stimes(curt, d.ft)), splus(d.sc, stimes(tm, d.ft))))));
}
void solve()
{
    dij();
    yukii(2, n)
    {
        q.push_back(mp(0, inf));
        yukji(1, n)
        {
            pii cur = mp(j, dis[enc(j, i)]);
            while(q.size() > 1 && cmp(q[q.size()-2], q.back(), cur)) q.pop_back();
            q.push_back(cur);
        }
        while(q.back().sc > q[q.size()-2].sc) q.pop_back();
        curt = 0;
        while(q.size() > 1 && curt <= tat)
        {
            int targ = sget(q[q.size()-2], q.back());
            addans(q.back(), min(targ, tat));
            q.pop_back();
            curt = targ+1;
        }
        q.clear();
    }
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif // snowoi
    sread();
    solve();
    printf("%d\n", ans);
    return 0;
}
