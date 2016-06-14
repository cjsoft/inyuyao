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
struct state;
state *null, *root, *last;
char s[1200000];
int f[1200000];
lol ans;
struct state
{
  int val, rt;
  state *pa, *s[28];
  state(int iv = 0):val(iv), rt(0), pa(null)
  {
    yuki(0, 28) s[i] = null;
  }
};
state *snew(int x)
{
  return new state(x);
}
void _init()
{
  null = snew(-1);
  null->pa = null;
  yuki(0, 28) null->s[i] = null;
  root = snew(0);
  last = root;
}
void insert(char ch)
{
  int x = ch-'a';
  state *p = last, *np = snew(last->val+1);
  for(;p != null && p->s[x] == null;p = p->pa) p->s[x] = np;
  if(p == null) np->pa = root;
  else
  {
    state *q = p->s[x];
    if(q->val == p->val+1) np->pa = q;
    else
    {
      state *nq = snew(p->val+1);
      memcpy(nq->s, q->s, sizeof(nq->s));
      nq->rt = q->rt;
      nq->pa = q->pa;
      q->pa = nq;
      np->pa = nq;
      for(;p->s[x] == q;p = p->pa) p->s[x] = nq;
    }
  }
  last = np;
  for(;np != root;np = np->pa)
  {
      ++np->rt;
      f[np->val] = max(f[np->val], np->rt);
  }
}
void saminit(const char *s)
{
  _init();
  while(*s) insert(*s++);
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("sub.in", "r", stdin);
    freopen("sub.out", "w", stdout);
#endif // snowoi
  scanf("%s", s);
  saminit(s);
  int l = strlen(s);
  yui(i, l-1, 0)
  {
      f[i-1] = max(f[i-1], f[i]);
      if(f[i] > 1) ans = max(ans, f[i]*(lol)i);
  }
  printf("%I64d\n", ans);///!!!!
  return 0;
}
