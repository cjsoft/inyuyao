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
char tar[300100];
int m, n, rit[300100], alc;
struct node
{
    node *s[26], *fail, *last;
    int val;
    node():fail(0), last(0), val(0){sclr(s);}
}*root, pool[4500000];
node *New()
{
    return &(pool[alc++] = node());
}
void insert()
{
    int l = 0;
    char ch = getchar();
    while(ch < 'a' || ch > 'z') ch = getchar();
    node *cur = root;
    while(ch >= 'a' && ch <= 'z')
    {
	int x = ch-'a';
	if(!cur->s[x]) cur->s[x] = New();
	cur = cur->s[x];
	++l;
	ch = getchar();
    }
    cur->val = l;
}
void getfail()
{
    queue<node*> q;
    yuki(0, 26)
    {
	if(root->s[i])
	{
	    root->s[i]->fail = root;
	    root->s[i]->last = root;
	    q.push(root->s[i]);
	}else root->s[i] = root;
    }
    root->fail = root->last = root;
    while(!q.empty())
    {
	node *cur = q.front();
	q.pop();
	yuki(0, 26)
	{
	    if(!cur->s[i])
	    {
		cur->s[i] = cur->fail->s[i];
		continue;
	    }
	    node *noi = cur->s[i], *f = cur->fail;
	    while(!f->s[i]) f = f->fail;
	    noi->fail = f->s[i];
	    noi->last = noi->fail->val ? noi->fail : noi->fail->last;
	    noi->val = max(noi->val, noi->last->val);
	    q.push(noi);
	}
    }
}
void find(char *s)
{
    int len = n;
    node *cur = root;
    yuki(0, len)
    {
	cur = cur->s[s[i]-'a'];
	if(cur->val)
	{
	    int lf = i-cur->val+1;
	    rit[lf] = max(i, rit[lf]);
	}
    }
}
void sread()
{
    root = New();
    scanf("%d%s%d", &n, tar, &m);
    int cnt = 0;
    yuki(0, m)
    {
	insert();
	if(++cnt >= 500)
	{
	    getfail();
	    find(tar);
	    alc = cnt = 0;
	    root = New();
	}
    }
    if(cnt)
    {
	getfail();
	find(tar);
    }
}
void printans()
{
    int ans = 0, currt = -1;
    yuki(0, n)
    {
	if(~currt && i > currt) currt = -1; 
	if(rit[i]) currt = max(currt, rit[i]);
	if(!~currt) ++ans;
    }
    printf("%d\n", ans);
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("POPLOCAVANJE.in", "r", stdin);
    freopen("POPLOCAVANJE.out", "w", stdout);
#endif
    sread();
    printans();
    return 0;
}
