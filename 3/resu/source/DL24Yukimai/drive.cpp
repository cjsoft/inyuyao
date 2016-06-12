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
int head[52000], nxt[104000], tow[104000], n, q, dis[7000][7000], alc;
bool vis[52000];
queue<int> pq;
void add(int s, int t)
{
    nxt[++alc] = head[s];
    head[s] = alc;
    tow[alc] = t;
    nxt[++alc] = head[t];
    head[t] = alc;
    tow[alc] = s;
}
int bfs(int s)
{
    while(!pq.empty()) pq.pop();
    sclr(vis);
    dis[s][s] = 0;
    pq.push(s);
    vis[s] = true;
    while(!pq.empty())
    {
        int cur = pq.front();
        pq.pop();
        int to = cur-1;
        if(!to) to = n;
        if(!vis[to])
        {
            dis[s][to] = dis[s][cur]+1;
            pq.push(to);
            vis[to] = true;
        }
        to = cur+1;
        if(to > n) to = 1;
        if(!vis[to])
        {
            dis[s][to] = dis[s][cur]+1;
            pq.push(to);
            vis[to] = true;
        }
        for(int i = head[cur];i;i = nxt[i])
            if(!vis[tow[i]])
            {
                dis[s][tow[i]] = dis[s][cur]+1;
                pq.push(tow[i]);
                vis[tow[i]] = true;
            }
    }
    return 0;
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
    yukii(1, n)
        bfs(i);
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
        printf("%d\n", dis[a][b]);
    }
    return 0;
}
