#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <ctime>
#define maxn 200010

using namespace std;

struct Node{Node* son[2];int key,siz,r;long long int sum;};
Node ni[maxn<<1],*root,*null;
int tot;
void InitTreap()
{
	srand(time(NULL));
	tot=0;
	null=&ni[tot++];
	null->son[0]=null->son[1]=null;
	null->key=null->siz=null->sum=0;
	root=null;
}
void NewNode(Node* &o,int key)
{
	o=&ni[tot++];
	o->son[0]=o->son[1]=null;
	o->key=o->sum=key;
	o->siz=1;
	o->r=rand();
}
void pushup(Node* o)
{
	if(o==null)return;
	o->siz=o->son[0]->siz+o->son[1]->siz+1;
	o->sum=o->son[0]->sum+o->son[1]->sum+o->key;
}
void rotate(Node* &o,int d)
{
	Node* k=o->son[d^1];o->son[d^1]=k->son[d];k->son[d]=o;
	pushup(o);pushup(k);
	o=k;
}
void insert(Node* &o,int key)
{
	if(o==null){NewNode(o,key);return;}
	int d=key<=o->key?0:1;
	insert(o->son[d],key);
	if(o->r>o->son[d]->r)rotate(o,d^1);
	pushup(o);
}
void erase(Node* &o,int key)
{
	if(o->key!=key)
	{
		int d=key<=o->key?0:1;
		erase(o->son[d],key);
	}
	else 
	{
		if(o->son[0]==null)o=o->son[1];
		else if(o->son[1]==null)o=o->son[0];
		else {int d=o->son[0]->r<o->son[1]->r?0:1;
		      rotate(o,d^1);
		      erase(o->son[d^1],key);
			 }
	}
	pushup(o);
}
int rank(Node* o,int key)
{
	if(o==null)return 0;
	if(o->key==key)return o->son[0]->siz+1;
	if(key<=o->key)return rank(o->son[0],key);
	else return o->son[0]->siz+rank(o->son[1],key)+1;
}
long long int sum(Node* o,int l,int r)
{
	if(r<l)return 0;
	if(o==null)return 0;
	if(r<1||l>o->siz)return 0;
	if(l==1&&r==o->siz)return o->sum;
	if(r<=o->son[0]->siz)return sum(o->son[0],l,r);
	if(l>o->son[0]->siz+1)return sum(o->son[1],l-o->son[0]->siz-1,r-o->son[0]->siz-1);
	return sum(o->son[0],l,o->son[0]->siz)+o->key+sum(o->son[1],1,r-o->son[0]->siz-1);
}
int n,q;
int ai[maxn]={0},vi[maxn]={0};
int li[maxn]={0};
long long int ans=0,s=0;
int main()
{
	freopen("RASPORED.in","r",stdin);
	freopen("RASPORED.out","w",stdout);
    InitTreap();
	int i;
	scanf("%d%d",&n,&q);
    for(i=1;i<=n;i++)
    {scanf("%d%d",&li[i],&ai[i]);
     s+=li[i];vi[i]=ai[i];
     insert(root,ai[i]);
	}
    sort(vi+1,vi+n+1);
    for(i=1;i<=n;i++)
    ans+=(long long int)(n-i+1)*vi[i];
    printf("%lld\n",s-ans);
    int x,l,t;
    int rx,rn;
    while(q--)
    {scanf("%d%d%d",&x,&l,&t);
     s-=li[x]-l;li[x]=l;
     
     if(t==ai[x]){printf("%lld\n",s-ans);continue;}
	 if(t>ai[x])
     {
	 rx=rank(root,ai[x]);rn=rank(root,t);
	 ans-=(long long int)(n-rx+1)*ai[x];
	 ans+=(long long int)(n-rn+1)*t;
	 ans+=sum(root,rx+1,rn);
     erase(root,ai[x]);insert(root,t);
     ai[x]=t;
 	 }
 	 else 
 	 {
	 rx=rank(root,ai[x]);rn=rank(root,t)+1;
 	 ans-=(long long int)(n-rx+1)*ai[x];
	 ans+=(long long int)(n-rn+1)*t;
	 ans-=sum(root,rn,rx-1);
	 erase(root,ai[x]);insert(root,t);
     ai[x]=t;
	 }
	 //cout<<rx<<" "<<rn<<" ";
	 printf("%lld\n",s-ans);
	}
    
	return 0;
}
