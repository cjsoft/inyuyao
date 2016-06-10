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
int enc(int* a)
{
    int ans = 0;
    yuki(0, 5)
    {
        ans <<= 2;
        ans += a[i];
    }
    return ans;
}
int *dec(int a)
{
    int *ans = new int[5];
    yui(i, 4, 0)
    {
        ans[i] = a%4;
        a>>=2;
    }
    return ans;
}
const int M =1000000007;
int has1[1080], has2[1080], n, m, ic, id, curx, cury, ans = -1;
bool m1[1000010][4], m2[1000010][4];
queue<int> q;
int ksm(int a, int b)
{
    if(b == 0) return 1;
    int t = ksm(a, b>>1);
    t = (lol)t*t%M;
    if(b & 1) t = (lol)t * a % M;
    return t;
}
void sread()
{
    scanf("%d%d%d%d", &n, &m, &ic, &id);
    int ia, ib;
    if(m == 1)
    {
        if(id) ans = 0;
        else ans = 1;
    }else if(m == 2 && !ic && !id)
        ans = ksm(2, n-1);
    while(ic--)
    {
        scanf("%d%d", &ia, &ib);
        m1[ia-1][ib-1] = true;
    }
    while(id--)
    {
        scanf("%d%d", &ia, &ib);
        m2[ia-1][ib-1] = true;
    }
}
bool goshl(int *a)
{
    if(a[m-1]) return false;
    yui(i, m-1, 1)
        a[i] = a[i-1];
    a[0] = 0;
    return true;
}
void inst(int *a, int v)
{
    if(cury == m-1)
        if(!goshl(a)) return;
    int h = enc(a);
    if(!has2[h]) q.push(h);
    has2[h] = (has2[h]+v)%M;
}
void lone(int *a, int x)
{
    int t = 0;
    do
    {
        if(a[x] == 2) ++t;
        else if(a[x] == 1)
        {
            if(t) --t;
            else {a[x] = 2;break;}
        }
    }while(x--);
}
void rone(int *a, int x)
{
    int t = 0;
    do
    {
        if(a[x] == 1) ++t;
        else if(a[x] == 2)
        {
            if(t) --t;
            else {a[x] = 1;break;}
        }
    }while(x++ < m);
}
int gofin()
{
    return has1[0];
}
int solve()
{
    if(ans >= 0) return ans;
    q.push(0);
    q.push(-1);
    has1[0] = 1;
    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        if(cur < 0)
        {
            swap(has1, has2);
            sclr(has2);
            if(++cury >= m) ++curx, cury = 0;
            if(curx >= n) return gofin();
            q.push(-1);
        }
        int *curs = dec(cur), news[5];
        memcpy(news, curs, sizeof(news));
        delete[] curs;
        int &l = news[cury], &r = news[cury+1];
        switch(l)
        {
        case 0:
            switch(r)
            {
            case 0:
                if(!m2[curx][cury])inst(news, has1[cur]);
                if(!m1[curx][cury])
                {
                    l = 1;
                    r = 2;
                    inst(news, has1[cur]);
                }
                break;
            case 1:
                if(!m1[curx][cury])
                {
                    inst(news, has1[cur]);
                    l = 1;
                    r = 0;
                    inst(news, has1[cur]);
                }
                break;
            case 2:
                if(!m1[curx][cury])
                {
                    inst(news, has1[cur]);
                    l = 2;
                    r = 0;
                    inst(news, has1[cur]);
                }
            }
            break;
        case 1:
            switch(r)
            {
            case 0:
                if(!m1[curx][cury])
                {
                    inst(news, has1[cur]);
                    l = 0;
                    r = 1;
                    inst(news, has1[cur]);
                }
                break;
            case 1:
                if(!m1[curx][cury])
                {
                    rone(news, cury+2);
                    l = r = 0;
                    inst(news, has1[cur]);
                }
                break;
            case 2:
                if(!m1[curx][cury])
                {
                    l = r = 0;
                    inst(news, has1[cur]);
                }
            }
            break;
        case 2:
            switch(r)
            {
            case 0:
                if(!m1[curx][cury])
                {
                    inst(news, has1[cur]);
                    l = 0;
                    r = 2;
                    inst(news, has1[cur]);
                }
                break;
            case 1:
                if(!m1[curx][cury])
                {
                    l = r = 0;
                    inst(news, has1[cur]);
                }
                break;
            case 2:
                if(!m1[curx][cury])
                {
                    lone(news, cury-1);
                    l = r = 0;
                    inst(news, has1[cur]);
                }
            }
        }
    }
    return -666;
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("eat.in", "r", stdin);
    freopen("eat.out", "w", stdout);
#endif // snowoi
    sread();
    printf("%d\n", solve());
    return 0;
}
