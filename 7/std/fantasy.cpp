#include<algorithm>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include  <stdio.h>
#include   <math.h>
#include   <time.h>
#include   <vector>
#include   <bitset>
#include    <queue>
#include      <set>
#include      <map>
using namespace std;

#define pb push_back

inline int Random()
{
	if(RAND_MAX==32768)
		return ((rand()<<15)^rand());
	return rand();
}

namespace IO
{
	const int L=1<<15,Lim=1<<20;
	char buffer[L],*S,*T,ch,outbuf[Lim+5];
	int Now;
	
	inline char Gc()
	{
		if(S==T)
		{
			T=(S=buffer)+fread(buffer,1,L,stdin);
			if(S==T)
				return EOF;
		}
		return *S++;
	}
	
	inline void get(int& x)
	{
		for(ch=Gc();(ch<'0'||ch>'9')&&ch!='-';ch=Gc());
		x=ch^'0';
		for(ch=Gc();ch>='0'&&ch<='9';ch=Gc())
			x=x*10+(ch^'0');
	}
	
	inline void get(char *s)
	{
		for(ch=Gc();ch<'A'||ch<'a'&&ch>'Z'||ch>'z';ch=Gc());
		*s=ch;
		for(ch=Gc();ch>='a'&&ch<='z'||ch>='A'&&ch<='Z';ch=Gc())
			*++s=ch;
		*++s=0;
	}
	
	inline void Pc(char ch)
	{
		outbuf[Now++]=ch;
		if(Now==Lim)
			fwrite(outbuf,1,Now,stdout),Now=0;
	}
	
	inline void put(int x)
	{
		if(x>9)
			put(x/10);
		Pc(x%10+'0');
	}
	
	inline void end()
	{
		if(Now)
			fwrite(outbuf,1,Now,stdout),Now=0;
	}
}

typedef long long LL;
const int N=500005;

int TOT,SS,TOTT;

namespace HASH
{
	const int Mod1=1000000007,Mod2=1000000009;
	
	int H1[N],H2[N],p1[N],p2[N],n;
	
	inline void init()
	{
		p1[0]=p2[0]=1;
		for(int i=1;i<N;i++)
			p1[i]=p1[i-1]*233ll%Mod1,p2[i]=p2[i-1]*233ll%Mod2;
	}
	
	inline void insert(int ch)
	{
		n++;H1[n]=(H1[n-1]*233ll+ch)%Mod1;H2[n]=(H2[n-1]*233ll+ch)%Mod2;
	}
	
	inline int Hash1(int a,int b)
	{
		return (Mod1+int(H1[b]-H1[a-1]*(LL)p1[b-a+1]%Mod1))%Mod1;
	}
	
	inline int Hash2(int a,int b)
	{
		return (Mod2+int(H2[b]-H2[a-1]*(LL)p2[b-a+1]%Mod2))%Mod2;
	}
	
	inline int Lcp(int a,int b)
	{
		int len=0,l=1,r=min(a,b);
		while(l<=r)
		{
			int Mid=l+r>>1;
			if(Hash1(a-Mid+1,a)==Hash1(b-Mid+1,b)&&Hash2(a-Mid+1,a)==Hash2(b-Mid+1,b))
				len=Mid,l=Mid+1;
			else
				r=Mid-1;
		}
		return len;
	}
}

struct node
{
	int k,ch,sz,Min,lcp,lm,rm;
	LL t;
	node *Lc,*Rc,*next;
	vector<int> Pos,Lp,Rp;
}T[N],*Now=T,*Rt;

int q,L,Ans,flag,lens;
char S[N*10],str[N];

inline int change1(char x)
{
	return x<='Z'?x-'A'+26:x-'a';
}

inline char change2(int x)
{
	return x<26?x+'a':x-26+'A';
}

void fix()
{
	for(int i=1;i<=L;i++)
		S[i]=change2((change1(S[i])+Ans)%52);
}

void push_down(node* a,LL l,LL r)
{
	if(!a)
		return;
	LL Mid=l+r>>1;
	a->t=l+r;push_down(a->Lc,l,Mid);push_down(a->Rc,Mid,r);
}

void push_up(node* a)
{
	a->sz=1;a->Min=a->lcp;a->lm=1e9;a->rm=a->lcp;
	if(a->Lc)
		a->sz+=a->Lc->sz,a->Min=min(a->Min,a->lm=a->Lc->Min);
	if(a->Rc)
		a->sz+=a->Rc->sz,a->Min=min(a->Min,a->Rc->Min),a->rm=min(a->rm,a->Rc->Min);
}

void UpdatePos(node *x)
{
	x->Pos.clear();x->Lp.clear();x->Rp.clear();
	int p=x-T;
	int lenl=x->Lc?x->Lc->Pos.size():0,lenr=x->Rc?x->Rc->Pos.size():0,sz=x->sz;
	int i=0,j=0,flag=0,vi=i==lenl?N:x->Lc->Pos[i],vj=j==lenr?N:x->Rc->Pos[j];
	while(vi<p||vj<p)
		if(vi<vj)
			x->Pos.pb(vi),i++,vi=i==lenl?N:x->Lc->Pos[i];
		else
			x->Pos.pb(vj),j++,vj=j==lenr?N:x->Rc->Pos[j];
	x->Pos.pb(p);
	while(i<lenl||j<lenr)
		if(vi<vj)
			x->Pos.pb(vi),i++,vi=i==lenl?N:x->Lc->Pos[i];
		else
			x->Pos.pb(vj),j++,vj=j==lenr?N:x->Rc->Pos[j];
	x->Lp.pb(0);x->Rp.pb(0);
	i=j=0;
	for(int k=0;k<sz;k++)
	{
		while(i<lenl&&x->Pos[k]>=x->Lc->Pos[i])
			i++;
		while(j<lenr&&x->Pos[k]>=x->Rc->Pos[j])
			j++;
		x->Lp.pb(i);x->Rp.pb(j);
		TOTT++;
	}
}

void Lr(node* &a)
{
	node *b=a->Rc;a->Rc=b->Lc;b->Lc=a;
	push_up(a);push_up(b);a=b;
}

void Rr(node* &a)
{
	node *b=a->Lc;a->Lc=b->Rc;b->Rc=a;
	push_up(a);push_up(b);a=b;
}

void Ins(node* &a,LL l,LL r)
{
	if(!a)
		return (void)((a=Now)->t=l+r,UpdatePos(a));
	LL Mid=l+r>>1;
	if(Now->ch<a->ch||Now->ch==a->ch&&Now->next->t<a->next->t)
	{
		Ins(a->Lc,l,Mid);push_up(a);
		if(a->Lc->k>a->k)
			Rr(a),UpdatePos(a->Rc);
		else
		{
			if(flag)
				flag=0,push_down(a->Lc,l,Mid),UpdatePos(a->Lc);
			a->Pos.pb(lens);a->Lp.pb(a->Lc?a->Lc->Pos.size():0);a->Rp.pb(a->Rc?a->Rc->Pos.size():0);
		}
	}
	else
	{
		Ins(a->Rc,Mid,r);push_up(a);
		if(a->Rc->k>a->k)
			Lr(a),UpdatePos(a->Lc);
		else
		{
			if(flag)
				flag=0,push_down(a->Rc,Mid,r),UpdatePos(a->Rc);
			a->Pos.pb(lens);a->Lp.pb(a->Lc?a->Lc->Pos.size():0);a->Rp.pb(a->Rc?a->Rc->Pos.size():0);
		}
	}
	if(flag&&a==Rt)
		push_down(a,l,r),UpdatePos(a);
}

void Del(node* &a,LL l,LL r)
{
	if(a==Now)
	{
		int f=0;
		if(flag)
			f=1,flag=0;
		if(!a->Lc&&!a->Rc)
		{
			a=NULL;return;
		}
		if(!a->Lc)
			a=a->Rc;
		else if(!a->Rc)
			a=a->Lc;
		else
		{
			if(a->Lc->k>a->Rc->k)
				Rr(a),Del(a->Rc,(l+r>>1)+1,r);
			else
				Lr(a),Del(a->Lc,l,(l+r)>>1);
			push_up(a);UpdatePos(a);
		}
		if(f)
			push_down(a,l,r);
	}
	else
	{
		a->Pos.pop_back();a->Lp.pop_back();a->Rp.pop_back();
		if(Now->t>a->t)
			Del(a->Rc,(l+r>>1)+1,r);
		else
			Del(a->Lc,l,(l+r)>>1);
		push_up(a);
	}
}

node *PRE,*SUF,*pre[N];int prelcp[N];

void find_pre(node *x)
{
	if(x->Rc)
		find_pre(x->Rc);
	else
		PRE=x;
}

void find_suf(node *x)
{
	if(x->Lc)
		find_suf(x->Lc);
	else
		SUF=x;
}

void find(node *x,LL k)
{
	if(x->t<k)
		find(x->Rc,k);
	else if(x->t>k)
		find(x->Lc,k);
	else
	{
		if(x->Lc)
			find_pre(x->Lc);
		if(x->Rc)
			find_suf(x->Rc);
	}
	if(x->t<k&&!PRE)
		PRE=x;
	if(x->t>k&&!SUF)
		SUF=x;
}

void Update(node *x,LL k)
{
	if(x->t<k)
		Update(x->Rc,k),x->rm=min(x->lcp,x->Rc->Min);
	else if(x->t>k)
		Update(x->Lc,k),x->lm=x->Lc->Min;
	else if(x->Rc)
		x->rm=min(x->lcp,x->Rc->Min);
	else
		x->rm=x->lcp;
	x->Min=min(x->lm,x->rm);
}

inline void Insert(int ch)
{
	HASH::insert(ch);str[++lens]=ch;
	(++Now)->ch=ch;Now->Lc=Now->Rc=0;Now->k=Random();Now->next=Now-1;Now->sz=flag=1;Now->lm=1e9;
	Now->Pos.clear();Now->Lp.clear();Now->Rp.clear();
	Ins(Rt,1,1LL<<61);
	PRE=SUF=0;find(Rt,Now->t);
	if(PRE)
		prelcp[lens]=PRE->lcp,PRE->lcp=HASH::Lcp(PRE-T,Now-T),Update(Rt,PRE->t);
	if(SUF)
		Now->lcp=HASH::Lcp(SUF-T,Now-T),Update(Rt,Now->t);
	pre[lens]=PRE;
}

inline void Delete()
{
	HASH::n--;
	if(pre[lens])
		pre[lens]->lcp=prelcp[lens],Update(Rt,pre[lens]->t);
	flag=1;Del(Rt,1,1LL<<61);
	Now--;lens--;
}

int LCP(node* a,int l)
{
	int p=a-T;
	while(l+1<=L&&p-l&&S[l+1]==str[p-l])
		l++,TOT++;
	return l;
}

int Al,Ar,TOTV;

int Ask(node* a,int l,int r,int pl,int pr)
{
	TOTV++;
	if(!a||pl>=pr)
		return 0;
	if(l==L&&r==L)
		return pr-pl;
	int la=LCP(a,max(min(l,a->lm),min(r,a->rm)));
	if(la==L)
		return Ask(a->Lc,l,la,a->Lp[pl],a->Lp[pr])+Ask(a->Rc,min(la,a->lcp),r,a->Rp[pl],a->Rp[pr])+(a-T>=Al&&a-T<=Ar);
	else if(S[la+1]<str[a-T-la])
		return Ask(a->Lc,l,la,a->Lp[pl],a->Lp[pr]);
	else
		return Ask(a->Rc,min(la,a->lcp),r,a->Rp[pl],a->Rp[pr]);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("fantasy.in","r",stdin);
	freopen("fantasy.out","w",stdout);
#endif
	IO::get(S+1);HASH::init();L=strlen(S+1);
	for(int i=1;i<=L;i++)
		Insert(S[i]);
	IO::get(q);
	while(q--)
	{
		int type;IO::get(type);
		if(type==1)
		{
			IO::get(S+1);L=strlen(S+1);fix();
			for(int i=1;i<=L;i++)
				Insert(S[i]);
		}
		else if(type==2)
			Delete();
		else
		{
			IO::get(Al);IO::get(Ar);Al^=Ans;Ar^=Ans; 
			IO::get(S+1);L=strlen(S+1);fix();
			for(int i=1;i<L-i+1;i++)
				swap(S[i],S[L-i+1]);
			if(Ar-Al+1<L)
				Ans=0;
			else
				Al+=L-1,Ans=Ask(Rt,0,0,Al-1,Ar);
			IO::put(Ans);IO::Pc('\n');
		}
	}
	IO::end();
	return 0;
}
