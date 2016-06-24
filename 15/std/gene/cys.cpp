#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long int64;
char ch;
bool ok;
void read(int &x){
	for (ok=0,ch=getchar();!isdigit(ch);ch=getchar()) if (ch=='-') ok=1;
	for (x=0;isdigit(ch);x=x*10+ch-'0',ch=getchar());
	if (ok) x=-x;
}
char num[20];
void write(int64 x){
//	printf("%lld\n",x);
	if (!x){putchar('0'),putchar('\n');return;}
	int tot=0;
	while (x) num[++tot]=x%10,x/=10;
	for (int i=tot;i;i--) putchar(num[i]+'0'); putchar('\n');
}
const int maxn=260005;
const int maxnode=4000005;
char s[maxn],ss[maxn];
int f[maxn],n,cnt,lim,q;
struct Quer{
	int l,r;
	int64 ans;
	void init(){read(l),read(r),ans=0;}
}quer[maxn];
struct Seg{
	int tot,root[maxn],son[maxnode][2],cnt[maxnode];
	int64 sumf[maxnode],sumi[maxnode];
	int64 ansf,ansi; int tim;
	void init(){tot=0;}
	void insert(int &k,int p,int l,int r,int x,int f,int i){
		k=++tot;
		sumf[k]=sumf[p]+f,sumi[k]=sumi[p]+i,cnt[k]=cnt[p]+1;
		if (l==r) return;
		int m=(l+r)>>1;
		if (x<=m) son[k][1]=son[p][1],insert(son[k][0],son[p][0],l,m,x,f,i);
		else son[k][0]=son[p][0],insert(son[k][1],son[p][1],m+1,r,x,f,i);
	}
	void insert(int id,int x,int f,int i){insert(root[id],root[id-1],0,lim,x,f,i);}
	void query(int a,int b,int l,int r,int x,int y){
		if (l==x&&r==y){ansf+=sumf[a]-sumf[b],ansi+=sumi[a]-sumi[b],tim+=cnt[a]-cnt[b];return;}
		int m=(l+r)>>1;
		if (y<=m) query(son[a][0],son[b][0],l,m,x,y);
		else if (x<=m) query(son[a][0],son[b][0],l,m,x,m),query(son[a][1],son[b][1],m+1,r,m+1,y);
		else query(son[a][1],son[b][1],m+1,r,x,y);
	}
	int64 query(int a,int b,int x,int op){
		if (a>b) return 0;
		ansf=0,ansi=0,tim=0;
		if (op){
			query(root[b],root[a-1],0,lim,x,lim);
			ansi=sumi[root[b]]-sumi[root[a-1]]-ansi,tim=cnt[root[b]]-cnt[root[a-1]]-tim;
			return ansf+ansi-1LL*tim*x;
		}
		else{
			query(root[b],root[a-1],0,lim,0,x);
			ansi=sumi[root[b]]-sumi[root[a-1]]-ansi,tim=cnt[root[b]]-cnt[root[a-1]]-tim;
			return ansf-ansi+1LL*tim*x;
		}
	}
}T;
void manacher(){
	cnt=(n<<1)+1,lim=n+1,ss[1]='#';
	for (int i=1;i<=n;i++) ss[i<<1]=s[i],ss[(i<<1)+1]='#';
	int id=0;
	for (int i=1;i<=cnt;i++){
		if (id+f[id]>=i) f[i]=min(f[(id<<1)-i],id+f[id]-i);
		while (i-f[i]-1&&i+f[i]+1<=cnt&&ss[i-f[i]-1]==ss[i+f[i]+1]) f[i]++;
		if (i+f[i]>id+f[id]) id=i;
	}
}
void solve(){
	for (int i=1;i<=q;i++) quer[i].ans+=quer[i].r-quer[i].l+1;
	T.init();
	for (int i=2;i<=cnt;i+=2) T.insert(i>>1,(i>>1)-(f[i]>>1),f[i]>>1,i>>1);
	for (int i=1;i<=q;i++){
		int l=quer[i].l,r=quer[i].r,m=(l+r)>>1;
		quer[i].ans+=T.query(l,m,l,1);
	}
	T.init();
	for (int i=2;i<=cnt;i+=2) T.insert(i>>1,(i>>1)+(f[i]>>1),f[i]>>1,i>>1);
	for (int i=1;i<=q;i++){
		int l=quer[i].l,r=quer[i].r,m=(l+r)>>1;
		quer[i].ans+=T.query(m+1,r,r,0);
	}
	T.init();
	for (int i=3;i<=cnt;i+=2) T.insert(i>>1,(i>>1)-(f[i]>>1)+1,f[i]>>1,(i>>1)+1);
	for (int i=1;i<=q;i++){
		int l=quer[i].l,r=quer[i].r,m=(l+r-1)>>1;
		quer[i].ans+=T.query(l,m,l,1);
	}
	T.init();
	for (int i=3;i<=cnt;i+=2) T.insert(i>>1,(i>>1)+(f[i]>>1),f[i]>>1,i>>1);
	for (int i=1;i<=q;i++){
		int l=quer[i].l,r=quer[i].r,m=(l+r-1)>>1;
		quer[i].ans+=T.query(m+1,r,r,0);
	}
}
int main(){
	read(n),read(q);
	scanf("%s",s+1);
	manacher();
	for (int i=1;i<=q;i++) quer[i].init();
	solve();
	for (int i=1;i<=q;i++) printf("%lld\n",quer[i].ans);
	return 0;
}
