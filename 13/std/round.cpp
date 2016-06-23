#include<iostream>
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef pair<int,int> pii;
namespace IO
{
	const int MAXL=1<<15;
	char buf[MAXL],*S,*T,ch;
	inline char igetch()
	{
		if(S==T)T=(S=buf)+fread(buf,1,MAXL,stdin);
		return S==T?EOF:*S++;
	}
	inline void read(int &x)
	{
		x=0;
		while(!isdigit(ch=igetch()));
		do{x=x*10+(ch^'0');}while(isdigit(ch=igetch()));
	}
}
const int MAXN=100000,MAXQ=100000;
struct edge{int u,v,w;}e[MAXQ+10];
struct node
{
	node *ch[2];
	pii key;
	int fix,size,delta;
	int cmp(const pii &_key)
	{
		if(_key==key)return -1;
		else return _key<key;
	}
	void update()
	{
		size=ch[0]->size+ch[1]->size+1;
		delta=ch[0]->delta+(ch[0]->size&1?-1:1)*(key.first-ch[1]->delta);
	}
}pool[MAXN+MAXQ*2+10],*cur=pool,*root,*null;
int n,m,q,online,deg[MAXN+10];
inline node *add_node(const pii &key)
{
	cur->ch[0]=cur->ch[1]=null;
	cur->key=key,cur->fix=rand();
	cur->size=1,cur->delta=key.first;
	return cur++;
}
inline void rotate(node *&u,int d)
{
	node *t=u->ch[d^1];
	u->ch[d^1]=t->ch[d],t->ch[d]=u;
	u->update(),t->update();
	u=t;
}
void insert(node *&u,const pii &key)
{
	if(u==null){u=add_node(key);return;}
	int d=u->cmp(key);
	insert(u->ch[d],key);
	u->update();
	if(u->ch[d]->fix>u->fix)rotate(u,d^1);
}
void remove(node *&u,const pii &key)
{
	int d=u->cmp(key);
	if(d==-1)
	{
		d=u->ch[1]->fix>u->ch[0]->fix;
		if(u->ch[d]==null){u=null;return;}
		rotate(u,d^1);
		remove(u->ch[d^1],key);
	}
	else remove(u->ch[d],key);
	u->update();
}
inline void init()
{
	root=null=cur++;
	null->ch[0]=null->ch[1]=null;
	null->fix=-1;
	IO::read(n),IO::read(q),IO::read(online);
	for(int i=1;i<=n;i++)insert(root,pii(0,i));
}
inline void modify(int id,int flag)
{
	int &u=e[id].u,&v=e[id].v,&w=e[id].w;
	if(u==v)
	{
		remove(root,pii(deg[u],u));
		deg[u]+=flag*w*2;
		insert(root,pii(deg[u],u));
	}
	else
	{
		remove(root,pii(deg[u],u));
		remove(root,pii(deg[v],v));
		deg[u]+=flag*w,deg[v]+=flag*w;
		insert(root,pii(deg[u],u));
		insert(root,pii(deg[v],v));
	}
}
inline void solve()
{
	int last=0,opt,u,v,w,id;
	while(q--)
	{
		IO::read(opt);
		if(opt)
		{
			m++;
			IO::read(e[m].u),IO::read(e[m].v),IO::read(e[m].w);
			if(online)e[m].u^=last,e[m].v^=last;
			modify(m,1);
		}
		else
		{
			IO::read(id);
			if(online)id^=last;
			modify(id,-1);
		}
		printf("%d\n",last=root->delta/2);
	}
}
int main(void)
{
	freopen("round.in","r",stdin);
	freopen("round.out","w",stdout);
	init();
	solve();
	return 0;
}
