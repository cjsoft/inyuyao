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
typedef pair<int, int> pii;
int dis[400][400], n, q;
void floyd()
{
    yuk(k, 1, n+1)
        yukii(1, n)
            yukji(1, n)
                dis[i][j] = min(dis[i][j], dis[i][k]+dis[k][j]);
}
void sread()
{
    scanf("%d", &n);
    scl(dis, 0x1f);
    yuki(1, n)
    {
        dis[i][i+1] = dis[i+1][i] = 1;
        dis[i][i] = 0;
    }
    dis[n][n] = 0;
    dis[1][n] = dis[n][1] = 1;
    int a, b;
    yuki(3, n)
    {
        scanf("%d%d", &a, &b);
        dis[a][b] = dis[b][a] = 1;
    }
    floyd();
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
