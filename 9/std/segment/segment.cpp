#include <stdio.h>
#include <stdlib.h>
using namespace std;

int n,m,q,i,j,k,opt,aim,l,r,ll,rr,val;
int optl[100005],optr[100005],L[100005][20],R[100005][20];
int Max[400005];

struct node
{
	int l,r,Max;
}t[4000005];
int root[100005],tot;

void B(int x,int l,int r)
{
	if(l==r)
	{
		scanf("%d",&Max[x]);
		return;
	}
	int mid=l+r>>1;
	B(x<<1,l,mid);
	B(x<<1|1,mid+1,r);
	if(Max[x<<1]>Max[x<<1|1])Max[x]=Max[x<<1];
	else Max[x]=Max[x<<1|1];
}

void M(int x,int l,int r)
{
	if(l==r)
	{
		scanf("%d",&Max[x]);
		return;
	}
	int mid=l+r>>1;
	if(aim<=mid)M(x<<1,l,mid);
	else M(x<<1|1,mid+1,r);
	if(Max[x<<1]>Max[x<<1|1])Max[x]=Max[x<<1];
	else Max[x]=Max[x<<1|1];
}

void G(int x,int l,int r)
{
	if(t[x].Max>val)val=t[x].Max;
	if(l==r)return;
	int mid=l+r>>1;
	if(aim<=mid)G(t[x].l,l,mid);
	else G(t[x].r,mid+1,r);
}

void C(int &x,int l,int r)
{
	t[++tot]=t[x];x=tot;
	if(l>=ll&&r<=rr)
	{
		t[x].Max=val;
		return;
	}
	int mid=l+r>>1;
	if(rr<=mid)C(t[x].l,l,mid);
	else if(ll>mid)C(t[x].r,mid+1,r);
		else C(t[x].l,l,mid),C(t[x].r,mid+1,r);
}

void Q(int x,int l,int r)
{
	if(l>=ll&&r<=rr)
	{
		if(Max[x]>val)val=Max[x];
		return;
	}
	int mid=l+r>>1;
	if(rr<=mid)Q(x<<1,l,mid);
	else if(ll>mid)Q(x<<1|1,mid+1,r);
		else Q(x<<1,l,mid),Q(x<<1|1,mid+1,r);
}

int main()
{
	freopen("segment.in","r",stdin);
	freopen("segment.out","w",stdout);
	scanf("%d%d%d",&n,&m,&q);
	B(1,1,n);
	for(i=1;i<=m;++i)
	{
		scanf("%d%d",&optl[i],&optr[i]);
		ll=optl[i];rr=optr[i];
		aim=ll;val=0;G(root[i-1],1,n);
		for(L[i][j=0]=val;j<=16;++j)L[i][j+1]=L[L[i][j]][j];
		aim=rr;val=0;G(root[i-1],1,n);
		for(R[i][j=0]=val;j<=16;++j)R[i][j+1]=R[R[i][j]][j];
		root[i]=root[i-1];val=i;C(root[i],1,n);
	}
	for(;q;--q)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d",&aim);
			M(1,1,n);
		}
		else
		{
			scanf("%d%d%d",&l,&r,&aim);
			val=0;G(root[r],1,n);
			if(val>=l)
			{
				for(ll=val,i=16;i>=0;--i)if(L[ll][i]>=l)ll=L[ll][i];
				for(rr=val,i=16;i>=0;--i)if(R[rr][i]>=l)rr=R[rr][i];
				ll=optl[ll];rr=optr[rr];
			}else ll=rr=aim;
			val=0;Q(1,1,n);
			printf("%d\n",val);
		}
	}
}
