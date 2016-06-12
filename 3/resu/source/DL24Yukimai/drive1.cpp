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
#include <queue>
using namespace std;
typedef long long lol;
typedef pair<int, int> pii;
int head[52000], nxt[104000], tow[104000], n, q, f[52000], g[52000], alc;
bool vis[52000];
priority_queue<pii, vector<pii>, greater<pii> > pq;
int sminus(const int &a, const int &b)
{
    int ans = (a-b)%n;
    if(ans < 0) ans += n;
    return ans;
}
int h(int a, int b)
{
    return min(sminus(a, b), sminus(b, a));
}
void add(int s, int t)
{
    nxt[++alc] = head[s];
    head[s] = alc;
    tow[alc] = t;
    nxt[++alc] = head[t];
    head[t] = alc;
    tow[alc] = s;
}
int astar(int s, int t)
{
    if(s == t) return 0;
    while(!pq.empty()) pq.pop();
    scl(f, 0x7f);
    scl(g, 0x7f);
    sclr(vis);
    f[s] = h(s, t);
    g[s] = 0;
    pq.push(mp(f[s], s));
    while(!pq.empty())
    {
        int cur = pq.top().sc;
        pq.pop();
        if(cur == t) return g[t];
        if(vis[cur])continue;
        vis[cur] = true;
        int to = cur-1;
        if(!cur) cur = n;
        if(!vis[to] && g[to] > g[cur]+1)
        {
            g[to] = g[cur]+1;
            f[to] = g[to]+h(to, t);
            pq.push(mp(f[to], to));
        }
        to = cur+1;
        if(to > n) to = 1;
        if(!vis[to] && g[to] > g[cur]+1)
        {
            g[to] = g[cur]+1;
            f[to] = g[to]+h(to, t);
            pq.push(mp(f[to], to));
        }
        for(int i = head[cur];i;i = nxt[i])
            if(!vis[tow[i]] && g[tow[i]] > g[cur]+1)
            {
                g[tow[i]] = g[cur]+1;
                f[tow[i]] = g[tow[i]]+h(tow[i], t);
                pq.push(mp(f[tow[i]], tow[i]));
            }
    }
    return -1;
}
void sread()
{
    scanf("%d", &n);
    int a, b;
    yuki(3, n)
    {
        scanf("%d%d", &a, &b);
        add(a, b);
    }
    scanf("%d", &q);
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("drive.in", "r", stdin);
    freopen("drive.out", "w", stdout);
#endif // snowoi
    sread();
    int a, b;
    while(q--)
    {
        scanf("%d%d", &a, &b);
        printf("%d\n", astar(a, b));
    }
    return 0;
}
