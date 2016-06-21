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
typedef long long lol;
using namespace std;
struct node
{
    int l, r, s;
    lol t;
    node *lht, *rht;
    node(int il = 0, int ir = 0):l(il), r(ir), s(0), t(0ll), lht(0), rht(0) {}
    void upd(){s = lht->s+rht->s;t = lht->t+rht->t;}
}*root;
const int L = 1, R = 100000;
int n, ti[200100], li[200100], q, cnt[100100];
lol lsum, tsum;
node *mktree(int l, int r)
{
    node *ans = new node(l, r);
    if(l == r)
    {
	ans->s = cnt[l];
	ans->t = (lol)cnt[l]*l;
	return ans;
    }
    int m = l+((r-l)>>1);
    ans->lht = mktree(l, m);
    ans->rht = mktree(m+1, r);
    ans->upd();
    return ans;
}
void decrease(node *cur, int val)
{
    if(cur->l == cur->r)
    {
	--cur->s;
	cur->t -= val;
	return;
    }
    int m = cur->lht->r;
    if(val <= m)
	decrease(cur->lht, val);
    else decrease(cur->rht, val);
    cur->upd();
}
void increase(node *cur, int val)
{
    if(cur->l == cur->r)
    {
	++cur->s;
	cur->t += val;
	return;
    }
    int m = cur->lht->r;
    if(val <= m)
	increase(cur->lht, val);
    else increase(cur->rht, val);
    cur->upd();
}
lol qsum(node *cur, int l, int r)
{
    if(cur->l == l && cur->r == r)
	return cur->t;
    int m = cur->lht->r;
    if(r <= m)
	return qsum(cur->lht, l, r);
    else if(l > m)
	return qsum(cur->rht, l, r);
    return qsum(cur->lht, l, m)+qsum(cur->rht, m+1, r);
}
int getrank(node *cur, int val)
{
    if(cur->l == cur->r) return 1;
    int m = cur->lht->r;
    if(val <= m)
	return getrank(cur->lht, val);
    else return cur->lht->s+getrank(cur->rht, val);
}
void sread()
{
    scanf("%d%d", &n, &q);
    yukii(1, n) scanf("%d%d", li+i, ti+i);
    yukii(1, n)
    {
	lsum += li[i];
	++cnt[ti[i]];
    }
    root = mktree(L, R);
    for(int i = 1, j = 1;j <= n;++j)
    {
	while(!cnt[i]) ++i;
	--cnt[i];
	tsum += i*(n-j+1ll);
    }
    printf("%lld\n", lsum-tsum);
}
int main(int argc, char **argv)
{
#ifndef snowoi
    freopen("RASPORED.in", "r", stdin);
    freopen("RASPORED.out", "w", stdout);
#endif
    sread();
    int id, l, t;
    while(q--)
    {
	scanf("%d%d%d", &id, &l, &t);
	lsum -= li[id]-l;
	li[id] = l;
	if(t != ti[id])
	{
	    tsum -= ti[id]*(n-getrank(root, ti[id])+1ll);
	    decrease(root, ti[id]);
	    if(t < ti[id])
		tsum -= qsum(root, t, ti[id]-1);
	    else
		tsum += qsum(root, ti[id], t-1);
	    increase(root, t);
	    tsum += t*(n-getrank(root, t)+1ll);
	    ti[id] = t;
	}
	printf("%lld\n", lsum-tsum);
    }
    return 0;
}
