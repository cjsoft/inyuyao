#include<bits/stdc++.h>
using namespace std;
struct fastin{
	static const int buffer_size=10000000;
	char buf[buffer_size],*wbuf;
	fastin(): wbuf(0) { }

	void input(FILE *file=stdin){
		buf[fread(buf,1,buffer_size,file)]=0,wbuf=buf;
	}
	void input(const char *name){
		FILE *file=fopen(name,"r");
		buf[fread(buf,1,buffer_size,file)]=0,wbuf=buf;
		fclose(file);
	}
	inline bool eoln(){
		while(*wbuf!='\n' && !isgraph(*wbuf)) ++wbuf;
		return *wbuf=='\n';
	}
	inline bool eof(){
		while(*wbuf!=0 && !isgraph(*wbuf)) ++wbuf;
		return *wbuf==0;
	}

	template<typename int_type>
	inline void getint(int_type &x){
		int sgn=+1; while(!isdigit(*wbuf)) ++wbuf;
		if(*(wbuf-1)=='-') sgn=-1; x=0;
		while(isdigit(*wbuf)) x=x*10+(*wbuf++)-'0';
		if(sgn==-1) x=-x;
	}
	template<typename real_type>
	inline void getreal(real_type &x){
		int sgn=+1; while(!isdigit(*wbuf)) ++wbuf;
		if(*(wbuf-1)=='-') sgn=-1; x=0;
		while(isdigit(*wbuf)) x=x*10+(*wbuf++)-'0';
		if(*wbuf=='.'){
			++wbuf;
			for(real_type v=0.1;isdigit(*wbuf);v*=0.1,++wbuf)
				x+=v*(*wbuf-'0');
		}
		if(sgn==-1) x=-x;
	}
	inline void getstring(char *s){
		while(!isgraph(*wbuf)) ++wbuf;
		char *p=s; while(isgraph(*wbuf)) *p++=*wbuf++; *p=0;
	}
	inline void getline(char *s){
		char *p=s; while(*wbuf!='\n') *p++=*wbuf++; *p=0;
	}
	inline void getchar(char &ch){ ch=*wbuf++; }
}fin;
struct fastout{
	static const int buffer_size=10000000;
	char buf[buffer_size],*wbuf; int prec;
	fastout(): wbuf(buf),prec(6) { }

	void clear(){ wbuf=buf; }
	void set_precision(int newprec){ prec=newprec; }
	void output(FILE *file=stdout){
		fwrite(buf,1,wbuf-buf,file);
	}
	void output(const char *name){
		FILE *file=fopen(name,"w");
		fwrite(buf,1,wbuf-buf,file);
		fclose(file);
	}

	template<typename int_type>
	inline void putint(int_type x,char extra=0){
		if(!x) *wbuf++='0';
		if(x<0) *wbuf++='-',x=-x;
		static const int maxlen=40;
		static char s[maxlen]; int len=0;
		for(;x;x/=10) s[len++]=x%10+'0';
		for(--len;len>=0;--len) *wbuf++=s[len];
		if(extra) *wbuf++=extra;
	}
	inline void putdouble(double x,char extra=0){
		wbuf+=sprintf(wbuf,"%.*f",prec,x);
		if(extra) *wbuf++=extra;
	}
	inline void putstring(const char *s){
		while(*s) *wbuf++=*s++;
	}
	inline void putchar(char ch){ *wbuf++=ch; }
}fout;

typedef long long int64;
struct Ttree{
	static const int maxn=130010;
	struct Tedge{
		int son; Tedge *pre;
		void add(int s_,Tedge *p_){ son=s_,pre=p_; }
	}edge[maxn],*pos[maxn];
	int tot;
	void add(int a,int b){ edge[++tot].add(b,pos[a]),pos[a]=edge+tot; }
	void clear(){ tot=0,memset(pos,0,sizeof(pos)); }
};
struct palindromic_tree{
	static const int maxn=130010;
	struct Tnode{
		Tnode *c[4],*pre; int len,dep;
	}node[maxn],*root,*f[maxn];
	int s[maxn],n,tot; Ttree t;

	Tnode *newnode(int l){
		Tnode *x=&node[++tot]; memset(x->c,0,sizeof(x->c));
		x->pre=0,x->len=l,x->dep=0; return x;
	}
	void clear(){
		s[0]=-1,n=tot=0,f[0]=root=newnode(0);
		root->pre=newnode(-1),t.clear();
	}

	int encode(char ch){
		if(ch=='A') return 0;
		if(ch=='T') return 1;
		if(ch=='C') return 2;
		if(ch=='G') return 3;
		assert(false);
	}
	void append(int ch){
		Tnode *x=f[n],*y; ch=encode(ch),s[++n]=ch;
		while(s[n]!=s[n-(x->len)-1]) x=x->pre;
		if(x->c[ch]){ f[n]=x->c[ch]; return; }
		f[n]=y=newnode(x->len+2),x->c[ch]=y;
		if(x=x->pre,x){
			while(s[n]!=s[n-(x->len)-1]) x=x->pre;
			y->pre=x->c[ch];
		}
		else y->pre=root;
		y->dep=y->pre->dep+1;
		t.add(y->pre-node,y-node);
	}
	
	int fa[maxn],sz[maxn],top[maxn];
	int o[maxn],pos[maxn],sign;
	void tree_dp(int x){
		sz[x]=1;
		for(Ttree::Tedge *i=t.pos[x];i;i=i->pre)
			fa[i->son]=x,tree_dp(i->son),sz[x]+=sz[i->son];
	}
	void decompose(int x){
		++sign,o[sign]=x,pos[x]=sign; int y=-1;
		for(Ttree::Tedge *i=t.pos[x];i;i=i->pre)
			if(y==-1 || sz[i->son]>sz[y]) y=i->son;
		if(y!=-1) top[y]=top[x],decompose(y);
		for(Ttree::Tedge *i=t.pos[x];i;i=i->pre)
			if(i->son!=y) top[i->son]=i->son,decompose(i->son);
	}
	void decompose(){
		fa[1]=-1,tree_dp(1);
		top[1]=1,sign=0,decompose(1);
	}	
	int count(int x,int len){
		for(x=f[x]-node;;x=fa[top[x]])
			if(node[top[x]].len<=len) break;
		int l=pos[top[x]],r=pos[x],mid;
		while(mid=(l+r)>>1,l<=r)
			if(node[o[mid]].len<=len) l=mid+1; else r=mid-1;
		return node[o[r]].dep;
	}
}pt1,pt2;
const int maxn=130010,maxm=130010;
struct Tquery{
	int idx,l,r;
}q[maxm];
int b[maxm]; int64 ans[maxm];
char s[maxn]; int n,m,sz;

bool cmp_query(const Tquery &u,const Tquery &v){
	if(b[u.l]!=b[v.l]) return u.l<v.l;
	if(b[u.l]&1) return u.r>v.r; return u.r<v.r;
}
void init(){
	fin.getint(n),fin.getint(m);
	fin.getstring(s+1),sz=sqrt(n);
	pt1.clear(),pt2.clear();
	for(int i=1;i<=n;++i)
		pt1.append(s[i]);
	for(int i=n;i>=1;--i)
		pt2.append(s[i]);
	pt1.decompose(),pt2.decompose();
	for(int i=1;i<=m;++i){
		fin.getint(q[i].l),fin.getint(q[i].r);
		q[i].idx=i,b[i]=i/sz,ans[i]=0;
	}
	sort(q+1,q+m+1,cmp_query);
}

void solve(){
	int l=1,r=1; int64 now=1;
	for(int i=1;i<=m;++i){
		while(q[i].l<l) --l,now+=pt2.count(n-l+1,r-l+1);
		while(q[i].r>r) ++r,now+=pt1.count(r,r-l+1);
		while(q[i].l>l) now-=pt2.count(n-l+1,r-l+1),++l;
		while(q[i].r<r) now-=pt1.count(r,r-l+1),--r;
		ans[q[i].idx]=now;
	}
	for(int i=1;i<=m;++i)
		fout.putint(ans[i],'\n');
}

int main(){
	fin.input();
	init();
	solve();
	fout.output();
	return 0;
}
