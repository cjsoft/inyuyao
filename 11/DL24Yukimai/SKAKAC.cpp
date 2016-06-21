#define yuki(x, y) for(int i = x; i < (y); ++i)
#define yukj(x, y) for(int j = x; j < (y); ++j)
#define yukii(x, y) for(int i = x; i <= (y); ++i)
#define yukji(x, y) for(int j = x; j <= (y); ++j)
#define yuk(x, y, z) for(int x = (y); x < (z); ++x)
#define yui(x, y, z) for(int x = (y); x >= (z); --x)
#define sclr(x) memset(x, 0, sizeof(x))
#define sclr1(x) memset(x, -1, sizeof(x))
#define scl(x, y) memset(x, y, sizeof(x))
#define mp make_pair
#define ft first
#define sc second
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
typedef long long lol;
using namespace std;
typedef pair<int, int> pii;
const int dx[] = {-1, 1, 2, 2, 1, -1, -2, -2}, dy[] = {2, 2, 1, -1, -2, -2, -1, 1};
struct snow
{
    int x, y;
    bool operator==(const snow &rhs) const{return x == rhs.x && y == rhs.y;}
};
const snow mark = (snow){-1, -1};
queue<snow> q;
int n, tt, k[40][40], curt, alc;
bool vis[40][40];
pii ans[1600];
inline void sread()
{
    int sx, sy;
    scanf("%d%d%d%d", &n, &tt, &sx, &sy);
    q.push((snow){sx, sy});
    q.push(mark);
    yukii(1, n)
	yukji(1, n)
	    scanf("%d", k[i]+j);
}
inline void expand(int x, int y)
{
    if(x < 1 || y < 1 || x > n || y > n || vis[x][y] || (curt+1)%k[x][y]) return;
    vis[x][y] = true;
    q.push((snow){x, y});
}
inline void solve()
{
    while(!q.empty())
    {
	snow cur = q.front();
	q.pop();
	if(cur == mark)
	{
	    ++curt;
	    sclr(vis);
	    if(curt == tt) break;
	    q.push(mark);
	    continue;
	}
	yuki(0, 8) expand(cur.x+dx[i], cur.y+dy[i]);
    }
    while(!q.empty())
    {
	snow cur = q.front();
	q.pop();
	ans[alc++] = mp(cur.x, cur.y);
    }
    sort(ans, ans+alc);
    printf("%d\n", alc);
    yuki(0, alc) printf("%d %d\n", ans[i].ft, ans[i].sc);
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("SKAKAC.in", "r", stdin);
    freopen("SKAKAC.out", "w", stdout);
#endif
    sread();
    solve();
    return 0;
}
