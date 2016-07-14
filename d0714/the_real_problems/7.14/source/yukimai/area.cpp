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
#include <cmath>
#include <cstdlib>
using namespace std;
typedef pair<int, int> pii;
typedef long long lol;
int n, cur[6];
pii pos[101000];
double oC = 672672672672672.0, best, cura;
const double decr = 0.99999, eps = 1e-6;
typedef pair<double, double> poi;
int rando(int x)
{
  return rand()/(double)RAND_MAX*x;
}
void sread()
{
  srand(267267);
  scanf("%d", &n);
  yuki(0, n) scanf("%d%d", &pos[i].ft, &pos[i].sc);
  sort(pos, pos+n);
  n = unique(pos, pos+n)-pos;
  random_shuffle(pos, pos+n);
}
int dcmp(const double &a, const double &b)
{
  if(fabs(a-b) <= eps) return 0;
  if(a-b > eps) return 1;
  return -1;
}
poi get(int a, int b)
{
  return poi(pos[a].ft-pos[b].ft, pos[a].sc-pos[b].sc);
}
double cross(const poi &a, const poi &b)
{
  return a.ft*b.sc-b.ft*a.sc;
}
double calc()
{
  poi p1 = get(cur[1], cur[0]), p2 = get(cur[2], cur[0]), p3 = get(cur[3], cur[0]);
  if(dcmp(cross(p1, p2), 0) < 0) swap(p1, p2);
  if(dcmp(cross(p1, p3), 0) < 0) swap(p1, p3);
  if(dcmp(cross(p2, p3), 0) < 0) swap(p2, p3);
  return cross(p1, p2)/2+cross(p2, p3)/2;
}
double possibility(double x)
{
  return exp(-log(x+2.718281828)/oC);
}
void init()
{
  yuki(0, 4) cur[i] = rando(n);
  cura = calc();
  best = max(best, cura);
}
int modn(int x)
{
  x %= n;
  if(x < 0) x += n;
  return x;
}
void simulate()
{
  int badcnt = 0;
  for(;;)
  {
    int k = rando(4);
    cur[k] = modn(cur[k]+rando(21)-10);
    double newa = calc();
    if(dcmp(newa, cura) > 0)
    {
      cura = newa;
      best = max(best, cura);
      badcnt = 0;
    }else
    {
      if(rand()/(double)RAND_MAX < possibility(cura-newa))
      {
	oC *= decr;
	cura = newa;
      }else
	if(++badcnt >= 10) return;
    }
  }
}
int main(int argc, char **argv)
{
#ifndef snowoi
  freopen("area.in","r", stdin);
  freopen("area.out", "w", stdout);
#endif
  sread();
  init();
  simulate();
  printf("%.1lf\n", best);
  return 0;
}
