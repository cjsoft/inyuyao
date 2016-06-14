#include<iostream>
#include<algorithm>
#include<map>
#include<cstdio>
using namespace std;
const int maxn = 80005;
int n,q,m,x,ch[maxn*20][2],size[maxn*20],val[maxn],tot,cnt,f[maxn],p[maxn];
map<int,int>hash;
bool check(int v,int l,int r)
{
	int ret=0;
	for(int i = l; i <= r; i++)
		if(v>=val[i])ret++;
	return ret>=x;
}
void newnode(int x,int d)
{
	ch[x][d]=++tot;
	size[tot]=0;
	ch[tot][0]=0;
	ch[tot][1]=0;
}
void insert(int ra,int rb,int l,int r,int val)
{
	size[rb]=size[ra]+1;
	if(l==r)return;
	int mid=(l+r)/2;
	if(val<=mid)
	{
		ch[rb][1]=ch[ra][1];
		if(!ch[rb][0])newnode(rb,0);
		insert(ch[ra][0],ch[rb][0],l,mid,val);
	}
	else
	{
		ch[rb][0]=ch[ra][0];
		if(!ch[rb][1])newnode(rb,1);
		insert(ch[ra][1],ch[rb][1],mid+1,r,val);
	}
}
int query(int ra,int rb,int l,int r,int k)
{
	if(l==r)return l;
	int mid = (l+r)/2;
	if(k<=size[ch[rb][0]]-size[ch[ra][0]])query(ch[ra][0],ch[rb][0],l,mid,k);
	else query(ch[ra][1],ch[rb][1],mid+1,r,k-size[ch[rb][0]]+size[ch[ra][0]]);
}
bool cmp(int a,int b)
{
	return val[a]<val[b];
}
int main(void)
{
	freopen("kth.in","r",stdin);
	freopen("kth.out","w",stdout);
	scanf("%d",&n);
	for(int i = 1; i <= n; i++)
		scanf("%d",&val[i]),p[i]=i;
	scanf("%d",&q);
	int op,l,r;
	if(n <= 1000 && q <= 1000)
	{
		for(int i = 0; i < q; i++)
		{
			scanf("%d%d%d%d",&op,&l,&r,&x);
			if(op==1){
				for(int i = l; i <= r; i++)
					val[i]+=x;
			}
			if(op==2){
				int L=-5000000,R=5000000,mid;
				while(L<R)
				{
					mid=(L+R)/2;
					if(check(mid,l,r))R=mid;
					else L=mid+1;
				}
				printf("%d\n",L);
			}
		}
	}
	else
	{
		sort(p+1,p+1+n,cmp);
		for(int i = 1; i <= n; i++)
		{
			if(!hash[val[p[i]]])hash[val[p[i]]]=++cnt;
			f[cnt]=val[p[i]];
		}
		for(int i = 1; i <= n; i++)
			insert(i-1,i,1,cnt,hash[val[i]]);
		for(int i = 0; i < q; i++)
		{
			scanf("%d%d%d%d",&op,&l,&r,&x);
			if(op==2)
				printf("%d\n",f[query(l-1,r,1,cnt,x)]);
		}
	}
	return 0;
}
	
	
