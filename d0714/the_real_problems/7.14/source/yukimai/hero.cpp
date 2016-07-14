#define yuki(x, y) for(int i = x; i < (y); ++i)
#define yukj(x, y) for(int j = x; j < (y); ++j)
#define yukii(x, y) for(int i = x; i <= (y); ++i)
#define yukji(x, y) for(int j = x; j <= (y); ++j)
#define yuk(x, y, z) for(int x = y; x < (z); ++x)
#define yui(x, y, z) for(int x = y; x >= (z); --x)
#define ft first
#define sc second
#define mp make_pair
#define sclr(x) memset(x, 0, sizeof(x))
#define sclr1(x) memset(x, -1, sizeof(x))
#define scl(x, y) memset(x, y, sizeof(x))
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long lol;
#ifdef unix
inline void putll(const lol &x){printf("%lld\n", x);}
#else
inline void putll(const lol &x){printf("%I64d\n", x);}
#endif
int n, m, k, head[360200], nxt[1270000], tow[1270000], dat[1270000], cost[1270000], alc = 1, lst[360200];
const int source = 360199, sourc = 360198, sink = 360197;
const lol inf = 0x1f1f1f1f1f1f1f1fll;
bool inq[360200];
lol dis[360200];
queue<int> q;
int enc(int i, int j, int k)
{
  return k*n*m+i*m+j;
}
void add(int s, int t, int w, int c)
{
  nxt[++alc] = head[s];
  head[s] = alc;
  tow[alc] = t;
  dat[alc] = w;
  cost[alc] = c;
  nxt[++alc] = head[t];
  head[t] = alc;
  tow[alc] = s;
  dat[alc] = 0;
  cost[alc] = -c;
}
void sread()
{
  scanf("%d%d%d", &n, &m, &k);
  int t;
  yuki(0, n)
    yukj(0, m)
    {
      scanf("%d", &t);
      add(enc(i, j, 0), enc(i, j, 1), 1, t);
    }
}
void pre()
{
  add(source, sourc, 2, 0);
  yuki(0, m) add(sourc, enc(0, i, 0), 2, 0);
  yuki(0, n-1)
  {
    yukj(0, m)
    {
      add(enc(i, j, 1), enc(i, j, 2), 2, -j*k);
      add(enc(i, j, 1), enc(i, j, 3), 2, j*k);
      add(enc(i, j, 2), enc(i+1, j, 0), 2, j*k);
      if(j < m-1) add(enc(i, j, 2), enc(i, j+1, 2), 2, 0);
      add(enc(i, j, 3), enc(i+1, j, 0), 2, -j*k);
      if(j) add(enc(i, j, 3), enc(i, j-1, 3), 2, 0);
    }
  }
  yuki(0, m) add(enc(n-1, i, 1), sink, 2, 0);
}
bool spfa()
{
  scl(dis, 0x1f);
  dis[source] = 0;
  q.push(source);
  inq[source] = true;
  while(!q.empty())
  {
    int cur = q.front();
    q.pop();
    inq[cur] = false;
    for(int i = head[cur];i;i = nxt[i])
      if(dat[i] && dis[tow[i]] > dis[cur]+cost[i])
      {
	dis[tow[i]] = dis[cur]+cost[i];
	lst[tow[i]] = i;
	if(!inq[tow[i]]) q.push(tow[i]), inq[tow[i]] = true;
      }
  }
  return dis[sink] < inf;
}
lol mcmf()
{
  int flow = 0;
  lol sumcost = 0;
  while(spfa())
  {
    flow = 1000;
    for(int i = lst[sink];i;i = lst[tow[i^1]])
      flow = min(flow, dat[i]);
    for(int i = lst[sink];i;i = lst[tow[i^1]])
    {
      dat[i] -= flow;
      dat[i^1] += flow;
    }
    sumcost += dis[sink];
  }
  return sumcost;
}
int main(int argc, char **argv)
{
#ifndef snowoi
  freopen("hero.in", "r", stdin);
  freopen("hero.out", "w", stdout);
#endif
  sread();
  pre();
  putll(mcmf());
  return 0;
}
