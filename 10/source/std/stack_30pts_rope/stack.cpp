#include<bits/stdc++.h>
#include<ext/rope>
using namespace std;
using namespace __gnu_cxx;
int n;
struct segs
{
	int l[4000100],r[4000100],tt;
	rope <int> ins[4000100];
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
			if (ins[root].size()) ins[root].pop_back();
			else erz[root]++;
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
	freopen("stack.in","r",stdin);
	freopen("stack.out","w",stdout);
	int q;scanf("%d%d",&n,&q);
	seg.build();
	while (q--)
	{
		int t;scanf("%d",&t);
		if (t==0)
		{
			int l,r,x;scanf("%d%d%d",&l,&r,&x);
			seg.push(1,l,r,x);
		}
		else if (t==1)
		{
			int l,r;scanf("%d%d",&l,&r);
			seg.pop(1,l,r);
		}
		else if (t==2)
		{
			int s,k;scanf("%d%d",&s,&k);
			seg.work(1,s,k);
		}
	}
}
