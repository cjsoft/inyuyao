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

struct node
{
	int k,ch,sz;
	LL t;
	node *Lc,*Rc,*next;
	vector<int> Pos;
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

void UpdatePos(node *x)
{
	x->Pos.clear();
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
}

void push_down(node* a,LL l,LL r)
{
	if(!a)
		return;
	LL Mid=l+r>>1;
	a->t=l+r;push_down(a->Lc,l,Mid);push_down(a->Rc,Mid,r);UpdatePos(a);
}

void push_up(node* a)
{
	a->sz=1;
	if(a->Lc)
		a->sz+=a->Lc->sz;
	if(a->Rc)
		a->sz+=a->Rc->sz;
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
		return (void)((a=Now)->t=l+r);
	LL Mid=l+r>>1;
	if(Now->ch<a->ch||Now->ch==a->ch&&Now->next->t<a->next->t)
	{
		Ins(a->Lc,l,Mid);push_up(a);
		if(a->Lc->k>a->k)
			Rr(a);
		else
		{
			if(flag)
				flag=0,push_down(a->Lc,l,Mid);
			a->Pos.pb(lens);
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
				flag=0,push_down(a->Rc,Mid,r);
			a->Pos.pb(lens);
		}
	}
	if(flag&&a==Rt)
		push_down(a,l,r);
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
			push_up(a);
		}
		if(f)
			push_down(a,l,r);
	}
	else
	{
		a->Pos.pop_back();
		if(Now->t>a->t)
			Del(a->Rc,(l+r>>1)+1,r);
		else
			Del(a->Lc,l,(l+r)>>1);
		push_up(a);
	}
}

inline void Insert(int ch)
{
	str[++lens]=ch;
	(++Now)->ch=ch;Now->Lc=Now->Rc=0;Now->k=Random();Now->next=Now-1;Now->sz=flag=1;
	Now->Pos.clear();
	Ins(Rt,1,1LL<<61);
}

inline void Delete()
{
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

int Al,Ar,TOTV,TT;

int Ask(node* a,int l,int r)
{
	TOTV++;
	if(!a)
		return 0;
	if(l==L&&r==L)
		return TT++,upper_bound(a->Pos.begin(),a->Pos.end(),Ar)-lower_bound(a->Pos.begin(),a->Pos.end(),Al);
	int la=LCP(a,0);
	if(la==L)
		return Ask(a->Lc,l,la)+Ask(a->Rc,la,r)+(a-T>=Al&&a-T<=Ar);
	else if(S[la+1]<str[a-T-la])
		return Ask(a->Lc,l,la);
	else
		return Ask(a->Rc,la,r);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("fantasy.in","r",stdin);
	freopen("fantasy.out","w",stdout);
#endif
	IO::get(S+1);L=strlen(S+1);
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
				Al+=L-1,Ans=Ask(Rt,0,0);
			IO::put(Ans);IO::Pc('\n');
		}
	}
	IO::end();
	return 0;
}
