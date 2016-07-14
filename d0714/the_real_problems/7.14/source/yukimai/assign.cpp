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
using namespace std;
typedef long long lol;
int n, il[30], ir[30], sco[30], perm[30], acnt[30], bcnt[30], cnt, k;
void sread()
{
  scanf("%d", &n);
  yuki(0, n) scanf("%d", il+i);
  yuki(0, n) scanf("%d", ir+i);
  scanf("%d", &k);
}
bool cmp(int l, int r)
{
  if(sco[l] != sco[r]) return sco[l] > sco[r];
  return l < r;
}
void chk()
{
  ++cnt;
  yuki(0, n) perm[i] = i;
  sort(perm, perm+n, cmp);
  sort(perm, perm+k);
  yuki(0, k)
  {
    if(!(i&3) || (i&3) == 3) ++acnt[perm[i]];
    else ++bcnt[perm[i]];
  }
}
void dfs(int cur)
{
  if(cur == n)
  {
    chk();
    return;
  }
  yukii(il[cur], ir[cur])
  {
    sco[cur] = i;
    dfs(cur+1);
  }
}
int main(int argc, char **argv)
{
#ifndef snowoi
  freopen("assign.in", "r", stdin);
  freopen("assign.out", "w", stdout);
#endif
  sread();
  dfs(0);
  yuki(0, n) printf("%.6lf %.6lf\n", acnt[i]/(double)cnt, bcnt[i]/(double)cnt);
  return 0;
}
