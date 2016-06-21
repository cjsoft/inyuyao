#include<iostream>
#include<algorithm>
#include<stdio.h>
#define lson id*2
#define rson id*2+1
#define maxn (200005)
#define mx (100001)
using namespace std;
int n,m;
struct node{
	int s;int t;
}a[maxn],b[maxn];
bool cmp(node x,node y)
{
	return x.t<y.t;
}
long long tr[800005];
int vis[800005],num[800005];
void pushup(int id)
{
	tr[id]=tr[lson]+tr[rson];
	num[id]=num[lson]+num[rson];
}
void build(int id,int l,int r)
{
	if (l>r)return ;
	if (l==r)
	{
		num[id]=vis[l];
		tr[id]=(long long)vis[l]*(long long)l;
		return ;
	}
	int mid=(l+r)/2;
	build(lson,l,mid);
	build(rson,mid+1,r);
	pushup(id);
	return ;
}
void add(int id,int l,int r,int x,int v)
{
	if (l>r) return ;
	if (l==r&&r==x)
	{
		num[id]+=v;
		tr[id]+=(long long)l*(long long)v;
		return ;
	}
	int mid=(l+r)/2;
	if (mid>=x)
	add(lson,l,mid,x,v);
	else
	add(rson,mid+1,r,x,v);
	pushup(id);
}
long long tmp;
void query(int id,int l,int r,int L,int R,int p)
{
	if (l>r|| L>R) return ;
	if (l>=L && r<=R)
	{
		if (p==1)
		tmp+=num[id];
		if (p==2)
		tmp+=tr[id];
		return ;
	}
	int mid=(l+r)/2;
	if (mid>=L)
	query(lson,l,mid,L,R,p);
	if (mid+1<=R)
	query(rson,mid+1,r,L,R,p);
	return ;
}
int main()
{
	freopen("RASPORED.in","r",stdin);
	freopen("RASPORED.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].s,&a[i].t);
		b[i].s=a[i].s;
		b[i].t=a[i].t;
		vis[a[i].t]++;
	}
	sort(a+1,a+1+n,cmp);
	long long t=0;
	long long ans=0;
	for (int i=1;i<=n;i++)
	{
		t+=a[i].t;
		ans+=a[i].s-t;
	}
	printf("%lld\n",ans);
	build(1,0,mx);
	for (int i=1,id,l,s;i<=m;i++)
	{
		scanf("%d%d%d",&id,&l,&s);
		if (s>b[id].t)
		{
			tmp=0;
			query(1,0,mx,0,b[id].t,2);
			ans-=b[id].s-tmp;
			add(1,0,mx,b[id].t,-1);
			add(1,0,mx,s,1);
			tmp=0;
			query(1,0,mx,0,s,2);
			ans+=l-tmp;
			tmp=0;
			query(1,0,mx,b[id].t+1,s,1);
			ans+=(tmp-1)*b[id].t;
			tmp=0;
			query(1,0,mx,s+1,mx,1);
			ans-=tmp*(s-b[id].t);
		}
		else
		{	
			tmp=0;
			query(1,0,mx,0,b[id].t,2);
			ans-=b[id].s-tmp;
			add(1,0,mx,b[id].t,-1);
			add(1,0,mx,s,1);
			tmp=0;
			query(1,0,mx,0,s,2); 
			ans+=l-tmp;
			tmp=0;
			query(1,0,mx,s+1,b[id].t,1);
			ans-=tmp*s;
			tmp=0;
			query(1,0,mx,b[id].t+1,mx,1);
			ans+=tmp*(b[id].t-s);
		}
		b[id].t=s;
		b[id].s=l;
		printf("%lld\n",ans);
	}
}
