#include<bits/stdc++.h>
#include<ext/rope>
using namespace std;
using namespace __gnu_cxx;
int n;
#define lson(x) ((x) << 1)
#define rson(x) ((x) << 1 | 1)
#define mid(l, r) ((l) + (((r) - (l)) >> 1))
#define Update(x) (stree[x] = stree[(x) << 1] + stree[(x) << 1 | 1])
#define INF 0x3f3f3f3f
#define MXN 500007
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
/*struct treaps
{
	rope<int> a[2000100];
	int tt;
	int newnode(){return ++tt;}
	int getsize(int s){return a[s].size();}
	void clear(int s){a[s].clear();}
	pair<int,int> split(int s,int w)
	{
		int d1=newnode(),d2=newnode();
		a[d1]=a[s].substr(0,w);a[d2]=a[s].substr(w,a[s].size()-w+1);
		return pair<int,int>(d1,d2);
	}
	int merge(int d1,int d2)
	{
		int t=newnode();
		a[t]=a[d1]+a[d2];
		return t;
	}
	void push_back(int s,int w){a[s].push_back(w);}
	void pop_back(int s){a[s].pop_back();}
	int findkth(int s,int k)
	{
		return a[s][k-1];
	}
	
}treap;*/
struct treaps
{
	int son[30001000][2],size[30001000],num[30001000],rd[30001000],tt;
	int newnode(int s=0)
	{
		if (tt>30000000) assert(0); 
		int t=++tt;
		son[t][0]=son[s][0];
		son[t][1]=son[s][1];
		size[t]=size[s];
		num[t]=num[s];
		if (s) rd[t]=rd[s];else rd[t]=rand();
		return t;
	}
	void update(int s) {size[s]=size[son[s][0]]+size[son[s][1]]+1;}
	int getsize(int s) {return size[s];}
	int merge(int s,int t)
	{
		if (!s) return t;
		if (!t) return s;
		if (rd[s]>rd[t])
		{
			int d=newnode(s);
			son[d][1]=merge(son[d][1],t);
			update(d);
			return d;
		}
		else
		{
			int d=newnode(t);
			son[d][0]=merge(s,son[d][0]);
			update(d);
			return d;
		}
	}
	pair<int,int> split(int s,int k)
	{
		//if (k==0) return pair<int,int>(0,s);
		//if (k==size[s]) return pair<int,int>(s,0);
		if (!s) return pair<int,int>(0,0);
		if (size[son[s][0]]>=k)
		{
			pair<int,int> ls=split(son[s][0],k);
			int d=newnode(s);
			son[d][0]=ls.second;update(d);
			return pair<int,int>(ls.first,d);
		}
		pair<int,int> ls=split(son[s][1],k-size[son[s][0]]-1);
		int d=newnode(s);
		son[d][1]=ls.first;update(d);
		return pair<int,int>(d,ls.second);
	}
	void clear(int& s){s=0;}
	void push_back(int& s,int w)
	{
		int t=newnode();
		size[t]=1;num[t]=w;
		s=merge(s,t);
	}
	void pop_back(int& s)
	{
		s=split(s,size[s]-1).first;
	}
	int findkth(int s,int k)
	{
		if (size[son[s][0]]>=k) return findkth(son[s][0],k);
		if (size[son[s][0]]+1==k) return num[s];
		return findkth(son[s][1],k-(size[son[s][0]]+1));
	}
}treap;
struct segs
{
	int l[4000100],r[4000100],tt;
	int ins[4000100];
	int erz[4000100];
	int build(int ql=1,int qr=n)
	{	
		int t=++tt;
		if (ql==qr) return t;
		int mid=(ql+qr)>>1;
		l[t]=build(ql,mid);
		r[t]=build(mid+1,qr);
		return t;
	}
	void pushdown(int root)
	{
		if (erz[root])
		{
			if (treap.getsize(ins[l[root]])<=erz[root])
			{
				erz[l[root]]+=erz[root]-treap.getsize(ins[l[root]]);
				treap.clear(ins[l[root]]);
			}
			else ins[l[root]]=treap.split(ins[l[root]],treap.getsize(ins[l[root]])-erz[root]).first;
			
			if (treap.getsize(ins[r[root]])<=erz[root])
			{
				erz[r[root]]+=erz[root]-treap.getsize(ins[r[root]]);
				treap.clear(ins[r[root]]);
			}
			else ins[r[root]]=treap.split(ins[r[root]],treap.getsize(ins[r[root]])-erz[root]).first;
			
			erz[root]=0;
		}
		if (treap.getsize(ins[root]))
		{
			ins[l[root]]=treap.merge(ins[l[root]],ins[root]);
			ins[r[root]]=treap.merge(ins[r[root]],ins[root]);
			treap.clear(ins[root]);
		}
	}
	void push(int root,int ql,int qr,int w,int pl=1,int pr=n)
	{
		if ((pl==ql)&&(pr==qr))
		{
			treap.push_back(ins[root],w);
			return;
		}
		pushdown(root);
		int mid=(pl+pr)>>1;
		if (ql<=mid) push(l[root],ql,min(mid,qr),w,pl,mid);
		if (qr>mid) push(r[root],max(mid+1,ql),qr,w,mid+1,pr);
	}
	void work(int root,int s,int k,int pl=1,int pr=n)
	{
		if (pl==pr)
		{
			if (treap.getsize(ins[root])<k) {printf("Error\n");return;}
			printf("%d\n",treap.findkth(ins[root],treap.getsize(ins[root])-k+1));
			return;
		}
		pushdown(root);
		int mid=(pl+pr)>>1;
		if (s<=mid) work(l[root],s,k,pl,mid);
		else work(r[root],s,k,mid+1,pr);
	}
	void pop(int root,int ql,int qr,int pl=1,int pr=n)
	{
		if ((pl==ql)&&(pr==qr))
		{
			if (treap.getsize(ins[root])) {
				treap.pop_back(ins[root]);
				if (treap.getsize(ins[root])) {
					edit(1, 1, n, ql, qr, work(1, ql, 1));
				} else {
					edit(1, 1, n, ql, qr, work(1, ql, 0));
				}
			} else erz[root]++;
			return;
		}
		pushdown(root);
		int mid=(pl+pr)>>1;
		if (ql<=mid) pop(l[root],ql,min(mid,qr),pl,mid);
		if (qr>mid) pop(r[root],max(mid+1,ql),qr,mid+1,pr);
	}
}seg;
int main()
{
	// freopen("stack.in","r",stdin);
	// freopen("stack.out","w",stdout);
	int type;
	int lastans = 0;
	int q;scanf("%d%d",&n,&q, &type);
	seg.build();
	for (int i = 0; i < (MXN << 2 | 1); ++i) etag[i] = -INF;
	int l2, r2;
	while (q--)
	{
		int t;scanf("%d",&t);
		if (t==3)
		{
			int l,r,x;scanf("%d%d%d",&l,&r,&x);
			l2 = (l1 + lastans * type) % n + 1;
			r2 = (r1 + lastans * type) % n + 1;
			l = min(l2, r2);
			r = max(l2, r2);
			edit(1, 1, n, l, r, x);
			seg.push(1,l,r,x);
		}
		else if (t==2)
		{
			int l,r;scanf("%d",&l);
			l = (l + lastans * type) % n + 1;
			seg.pop(1,l,l);
		}
		else if (t==1)
		{
			int l,r;scanf("%d%d",&l,&r);
			l2 = (l1 + lastans * type) % n + 1;
			r2 = (r1 + lastans * type) % n + 1;
			l = min(l2, r2);
			r = max(l2, r2);
			printf("%d\n", lastans = query(1, 1, n, l, r));
			// int s,k;scanf("%d%d",&s,&k);
			// seg.work(1,s,k);

		}
	}
}
