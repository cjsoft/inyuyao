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
#include <cstdlib>
#include <ctime>
using namespace std;
typedef long long lol;
int rando(int x)
{
    return rand()/(double)RAND_MAX*x;
}
int randoo()
{
    if(rand()&1) return 1;
    else return 2;
}
int main(int argc, char **argv)
{
    srand(time(0)*672672+atoi(argv[1]));
    yuki(0, 1000000) putchar('a'+rando(25));
    puts("");
    return 0;
}
