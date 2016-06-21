#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int n,m,maxn;
int C[100010];
long long S[100010];
struct node{
	int id,t,w;	
}q[200005];
//int t[200005],w[200005];
long long ans;
int cmp(node x,node y)
{
	return x.t<y.t;	
}
void add2(int x,long long v)
{
	while(x<=100005)
	{
		S[x]+=v;
		x+=x&(-x);
	}
}
long long get2(int x)
{
	long long  ret=0;
	while(x>0)
	{
		ret+=S[x];
		x-=x&(-x);
	}
	return ret;
}
void add1(int x,int v)
{
	while(x<=100005)
	{
		C[x]+=v;
		x+=x&(-x);
	}
}
int get1(int x)
{
	int ret=0;
	while(x>0)
	{
		ret+=C[x];
		x-=x&(-x);
	}
	return ret;
}
void solve()
{
	int id,aa,bb;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&id,&aa,&bb);
		bb++;
		ans+=aa;
		ans-=q[id].w;
		q[id].w=aa;
	//	cout<<ans<<endl;
		if(bb>q[id].t)
		{	
			long long rr=get1(bb-1);
			long long  ll=get1(q[id].t-1);
			long long  tmp=rr-ll-1;
			ans+=tmp*(long long)(q[id].t-1);
			ans-=(n-rr)*(long long)(bb-q[id].t);
			ans+=get2(q[id].t-1)+(long long)q[id].t-1;
			add2(q[id].t,-q[id].t+1);
			ans-=get2(bb-1)+bb-1;
			add2(bb,bb-1);
			add1(q[id].t,-1);
			add1(bb,1);
		}
		else if(bb<q[id].t)
		{
			long long  rr=get1(q[id].t-1);
			long long  ll=get1(bb-1);
			long long tmp=rr-ll;
			ans-=tmp*(bb-1);
		
			ans+=(n-rr-1)*(long long)(q[id].t-bb);
		
			ans+=get2(q[id].t-1)+(long long)q[id].t-1;
		//	cout<<q[id].t-1<<endl;	
			
			ans-=get2(bb-1)+(long long)bb-1;
			add2(q[id].t,(long long)-q[id].t+1);
			add2(bb,(long long)bb-1);
			add1(q[id].t,-1);
			add1(bb,1);
		}
		q[id].t=bb;
		printf("%lld\n",ans);	

	}
	
	
}



int cc(node xx,node yy)
{
	return xx.id<yy.id;	
}
int main()
{
	freopen("RASPORED.in","r",stdin);
	freopen("RASPORED.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{	
		scanf("%d%d",&q[i].w,&q[i].t);
		q[i].t++;
		q[i].id=i;	
	}
	sort(q+1,q+1+n,cmp);
	long long tmp=0;
	
	for(int i=1;i<=n;i++)
	{
		tmp+=q[i].t-1;
		add1(q[i].t,1);
		add2(q[i].t,(long long)q[i].t-1);
		ans+=q[i].w;
		ans-=tmp;
		//cout<<ans<<endl;
	}
	sort(q+1,q+1+n,cc);

	printf("%lld\n",ans);
	//while(1);
	solve();
}
