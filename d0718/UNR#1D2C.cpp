#include<bits/stdc++.h>
#include<ext/rope>
#define lson(x) ((x) << 1)
#define rson(x) ((x) << 1 | 1)
#define mid(l, r) ((l) + (((r) - (l)) >> 1))
#define Update(x) (stree[x] = stree[(x) << 1] + stree[(x) << 1 | 1])
#define INF 0x3f3f3f3f
#define MXN 500007
using namespace std;
using namespace __gnu_cxx;
int n;
int stree[MXN << 2 | 1];
int etag[MXN << 2 | 1];
void edit(int root, int l, int r, int data) {
    stree[root] = data * (r - l + 1);
    etag[root] = data;
}
void pushdown(int root, int l, int r) {
    if (etag[root] != -INF) {
        edit(lson(root), l, mid(l, r), etag[root]);
        edit(rson(root), mid(l, r) + 1, r, etag[root]); 
        etag[root] = -INF;
    }
}
void edit(int root, int l, int r, int ql, int qr, int data) {
    if (l > qr || r < ql) return;
    if (l >= ql && r <= qr) {
        edit(root, l, r, data);
        return;
    }
    pushdown(root, l, r);
    edit(lson(root), l, mid(l, r), ql, qr, data);
    edit(rson(root), mid(l, r) + 1, r, ql, qr, data);
    Update(root);
}
int query(int root, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) return 0;
    if (l >= ql && r <= qr) return stree[root];
    pushdown(root, l, r);
    return query(lson(root), l, mid(l, r), ql, qr) + query(rson(root), mid(l, r) + 1, r, ql, qr);
}
struct segs
{
	int l[2000100],r[2000100],tt;
	rope <int> ins[2000100];
	int erz[2000100];
    inline void update(int root) {
        stree[root] = stree[l[root]] + stree[r[root]];
    }
	int build(int ql=1,int qr=n)
	{	
		int t=++tt;
		if (ql==qr) { etag[t] = -INF; return t; }
		int mid=(ql+qr)>>1;
		l[t]=build(ql,mid);
		r[t]=build(mid+1,qr);
		return t;
	}
	void pushdown(int root)
	{
		if (erz[root])
		{
			if (ins[l[root]].size()<=erz[root])
			{
				erz[l[root]]+=erz[root]-ins[l[root]].size();
				ins[l[root]].clear();
			}
			else ins[l[root]]=ins[l[root]].substr(0,ins[l[root]].size()-erz[root]);
			
			if (ins[r[root]].size()<=erz[root])
			{
				erz[r[root]]+=erz[root]-ins[r[root]].size();
				ins[r[root]].clear();
			}
			else ins[r[root]]=ins[r[root]].substr(0,ins[r[root]].size()-erz[root]);
			
			erz[root]=0;
		}
		if (ins[root].size())
		{
			ins[l[root]]+=ins[root];
			ins[r[root]]+=ins[root];
			ins[root].clear();
		}
	}
	void push(int root,int ql,int qr,int w,int pl=1,int pr=n)
	{
		if ((pl==ql)&&(pr==qr))
		{
			ins[root].push_back(w);
			return;
		}
		pushdown(root);
		int mid=(pl+pr)>>1;
		if (ql<=mid) push(l[root],ql,min(mid,qr),w,pl,mid);
		if (qr>mid) push(r[root],max(mid+1,ql),qr,w,mid+1,pr);
	}
	void pop(int root,int ql,int qr,int pl=1,int pr=n)
	{
		if ((pl==ql)&&(pr==qr))
		{
			if (ins[root].size()) {
                ins[root].pop_back();
                if (ins[root].size()) edit(1, 1, n, ql, qr, ins[root][ins[root].size() - 1]);
                else edit(1, 1, n, ql, qr, 0);
            } else erz[root]++;
            
			return;
		}
		pushdown(root);
		int mid=(pl+pr)>>1;
		if (ql<=mid) pop(l[root],ql,min(mid,qr),pl,mid);
		if (qr>mid) pop(r[root],max(mid+1,ql),qr,mid+1,pr);
	}
	void work(int root,int s,int k,int pl=1,int pr=n)
	{
		if (pl==pr)
		{
			if (ins[root].size()<k) {printf("Error\n");return;}
			printf("%d\n",ins[root][ins[root].size()-k]);
			return;
		}
		pushdown(root);
		int mid=(pl+pr)>>1;
		if (s<=mid) work(l[root],s,k,pl,mid);
		else work(r[root],s,k,mid+1,pr);
	}
}seg;
int main()
{
    int type;
	// freopen("stack.in","r",stdin);
	// freopen("stack.out","w",stdout);
    int lastans = 0;
	int q;scanf("%d%d%d",&n,&q, &type);
	seg.build();
    for (int i = 0; i < (MXN << 2 | 1); ++i) etag[i] = -INF;
	while (q--)
	{
		int t;scanf("%d",&t);
		if (t==3)
		{
			int l,r,x;scanf("%d%d%d",&l,&r,&x);
            // if (type) {
                int l2, r2;
                l2 = (l + lastans * type) % n + 1;
                r2 = (r + lastans * type) % n + 1;
                l = min(l2, r2);
                r = max(l2, r2);
            // }
            edit(1, 1, n, l, r, x);
			seg.push(1,l,r,x);
		}
		else if (t==2)
		{
			int l,r;scanf("%d",&l);
            //if (type || 1) 
            l = (l + lastans * type) % n + 1;
			seg.pop(1,l,l);
		}
		else if (t==1)
		{
			int l,r;scanf("%d%d",&l,&r);
            // if (type) {
                int l2, r2;
                l2 = (l + lastans * type) % n + 1;
                r2 = (r + lastans * type) % n + 1;
                l = min(l2, r2);
                r = max(l2, r2);
            // }
            printf("%d\n", lastans = query(1, 1, n, l, r));
			// seg.work(1,s,k);
		}
	}
}
