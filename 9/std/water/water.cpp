#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#define inf 1000000000000000000ll
using namespace std;

int N,m,K,i,j,k,l,now,tot,sum,size;
int a[100005];
long long g;

struct seg_node
{
	int l,r,b,size,gMax;
	long long g;
}t[20000005];

void Update(int x)
{
	int L=t[x].l,R=t[x].r;
	if(L&&(t[L].g<t[R].g||!R))t[x].g=t[L].g,t[x].gMax=t[L].gMax,t[x].b=t[L].b;
	else t[x].g=t[R].g,t[x].gMax=t[R].gMax+t[L].size,t[x].b=t[R].b;
	t[x].size=t[L].size+t[R].size;
}

int B(int l,int r)
{
	int x=++tot,mid=l+r>>1;
	t[x].size=r-l+1;
	if(l==r)return x;
	t[x].l=B(l,mid);
	t[x].r=B(mid+1,r);
	return x;
}

void A_(int &x,int l,int r)
{
	t[++tot]=t[x];x=tot;
	if(l==r)
	{
		++t[x].b;
		t[x].g+=g;
		t[x].size=size;
		t[x].gMax=size;
		return;
	}
	int mid=l+r>>1;
	if(t[t[x].l].size>=sum)A_(t[x].l,l,mid);
	else sum-=t[t[x].l].size,A_(t[x].r,mid+1,r);
	Update(x);
}

void A(int &root,int sum_,long long g_,int size_)
{
	sum=sum_;g=g_;size=size_;
	A_(root,1,N);
}

void C_(int &x,int l,int r)
{
	t[++tot]=t[x];x=tot;
	if(l==r)
	{
		t[x].g=g;
		t[x].size=size;
		t[x].gMax=size;
		return;
	}
	int mid=l+r>>1;
	if(t[t[x].l].size>=sum)C_(t[x].l,l,mid);
	else sum-=t[t[x].l].size,C_(t[x].r,mid+1,r);
	Update(x);
}

void C(int &root,int sum_,long long g_,int size_)
{
	sum=sum_;g=g_;size=size_;
	C_(root,1,N);
}

void D_(int &x,int l,int r)
{
	if(t[x].size<=sum)
	{
		sum-=t[x].size;
		x=0;
		return;
	}
	int mid=l+r>>1;
	t[++tot]=t[x];x=tot;
	D_(t[x].l,l,mid);
	if(sum)D_(t[x].r,mid+1,r);
	Update(x);
}

void D(int &root,int sum_)
{
	sum=sum_;
	D_(root,1,N);
}

int Q_(int x,int l,int r)
{
	if(l==r)return a[l];
	int mid=l+r>>1;
	if(t[t[x].l].size>=sum)return Q_(t[x].l,l,mid);
	sum-=t[t[x].l].size;
	return Q_(t[x].r,mid+1,r);
}

int Q(int root,int sum_)
{
	sum=sum_;
	return Q_(root,1,N);
}

struct node
{
	int n,i,j,k,gMax,gb,root,root_;
	long long sum,sumg;
	
	void calc_g()
	{
		sumg=sum+t[root].g;
		gMax=t[root].gMax;
		gb=t[root].b;
	}
	void select()
	{
		sum=sumg;
		j=gb+1;
		int tmp=gMax-gb;
		n-=tmp;
		
		root=root_;
		C(root,gMax,inf,0);
		if(tmp>1)D(root,tmp-1);
		if(j<=n)C(root,j,Q(root,j)-Q(root,j-1),1);
		C(root,1,inf,1);
		root_=root;
		
		calc_g();
	}
	void update()
	{
		++gb;
		if(gb==gMax)C(root,gMax,inf,1);
		else A(root,gMax,Q(root,gMax)-Q(root,gMax-gb),1);
		calc_g();
	} 
}S[1000005];

int Min[2000005];
void update(int x)
{
	if(S[Min[x<<1]].sumg<S[Min[x<<1|1]].sumg)Min[x]=Min[x<<1];
	else Min[x]=Min[x<<1|1];
}

int main()
{
	freopen("water.in","r",stdin);
	freopen("water.out","w",stdout);
	scanf("%d%d",&N,&K);
	for(l=1;l<K;l<<=1);
	for(i=1;i<=N;++i)scanf("%d",&a[i]);
	sort(a+1,a+N+1);
	m=1;S[1].n=N;
	S[1].root=B(1,N);
	for(i=1;i<=N;++i)
	{
		S[1].sum+=(long long)(N-i+1)*a[i];
		if(i>1)A(S[1].root,i,a[i]-a[i-1],1);
		else A(S[1].root,i,inf,1);
	}
	S[1].root_=S[1].root;
	for(i=1;i<=l;++i)S[i].sumg=inf,Min[l+i-1]=i;
	S[1].calc_g();
	for(i=l-1;i;--i)update(i);
	printf("%lld\n",S[1].sum);
	for(--K;K;--K)
	{
		now=Min[1];
		printf("%lld\n",S[now].sumg);
		S[++m]=S[now];
		S[m].select();
		for(i=l+m-1>>1;i;i>>=1)update(i);
		S[now].update();
		for(i=l+now-1>>1;i;i>>=1)update(i);
	}
}
