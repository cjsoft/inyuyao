#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#define maxn 100010

using namespace std;

int n,q;
int ai[maxn]={0};

vector<int> vi;
void work1()
{
	int i,j,c,l,r,k;
	for(i=0;i<q;i++)
	{scanf("%d%d%d%d",&c,&l,&r,&k);
	 if(c==1)
	 {for(j=l;j<=r;j++)
	  ai[j]+=k;
	 }
	 else 
	 {vi.clear();
	  for(j=l;j<=r;j++)
	  vi.push_back(ai[j]);
	  sort(vi.begin(),vi.end());
	  printf("%d\n",vi[k-1]);
	 }
	}
}

struct Node{Node* son[2];int s,l,r;};
Node ni[maxn*30];
int tot=0;
Node *rooti[maxn];

void pushup(Node* o)
{
	if(o->l==o->r)return;
	o->s=o->son[0]->s+o->son[1]->s;
}

void buildtree(Node* &o,int l,int r)
{
	o=&ni[tot++];
	o->l=l;
	o->r=r;
	o->s=0;
	if(o->l==o->r)return;
	int m=(l+r)>>1;
	buildtree(o->son[0],l,m);
	buildtree(o->son[1],m+1,r);
}

void addt(Node* o1,Node* &o,int key)
{
	o=&ni[tot++];
	o->l=o1->l;
	o->r=o1->r;
	if(o->l==o->r){o->s++;return;}
	int m=(o1->l+o1->r)>>1;
	int d=key<=m?0:1;
	o->son[d^1]=o1->son[d^1];
	addt(o1->son[d],o->son[d],key);
	pushup(o);
}

int query(Node* o1,Node* o,int k)
{
	if(o->l==o->r)return o->l;
	int siz=o->son[0]->s-o1->son[0]->s;
	if(k<=siz)return query(o1->son[0],o->son[0],k);
	else return query(o1->son[1],o->son[1],k-siz);
}

int sa[maxn]={0},rank[maxn]={0};
bool cmp(int a,int b)
{return ai[a]<ai[b];
}


void work2()
{
	int i,c,l,r,k;
	for(i=1;i<=n;i++)
	sa[i]=i;
	sort(sa+1,sa+n+1,cmp);
	for(i=1;i<=n;i++)
	rank[sa[i]]=i;
	
	buildtree(rooti[0],1,n);
	for(i=1;i<=n;i++)
	addt(rooti[i-1],rooti[i],rank[i]);
	
	for(i=0;i<q;i++)
	{scanf("%d%d%d%d",&c,&l,&r,&k);
	 printf("%d\n",ai[sa[query(rooti[l-1],rooti[r],k)]]);
	}
}

int main()
{
	freopen("kth.in","r",stdin);
	freopen("kth.out","w",stdout);
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	scanf("%d",&ai[i]);
	scanf("%d",&q);
	if(n<=1000&&q<=1000)work1();
	else work2();
	return 0;
}
