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
typedef unsigned long long ulol;
int n, cur, len, leng;
lol num;
const int biao[] = {1835008,1949696,2389696,2932736,3211264,3765952,4194304,5046272,6078464,6911680,7698112,8503296,9795264,12369920, 13631488};
void pushn()
{
    ++len;
    num = 0ll;
    leng = -1;
    yui(i, 31, 0)
    {
        num *= 10;
        if(~leng) num %= 1<<leng;
        if(len & (1<<i))
        {
            ++num;
            if(leng < 0) leng = i+1;
            num %= 1<<leng;
        }
    }
    if(!(num^len))
    {
        ++cur;
        if(!(len & 1) && cur < n)
        {
            ++cur;
            ++len;
        }
    }
}
void printans()
{
    bool ok = false;
    yui(i, 31, 0)
        if(len & (1<<i))
        {
            ok = true;
            putchar('1');
        }else if(ok) putchar('0');
}
void printans(int)
{
    printf("%d\n", len);
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("quiz.in", "r", stdin);
    freopen("quiz.out", "w", stdout);
#endif // snowoi
    scanf("%d", &n);
    if(n >= 400 && n < 550)
    {
        int k = (n-400)/10;
        len = biao[k];
        cur = 400+k*10;
    }
    while(cur < n) pushn();
    printans();
    return 0;
}
