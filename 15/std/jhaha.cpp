#include<cstdio>
#include<cassert>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int inf=0x3f3f3f3f;
const int maxn=20005,maxm=105;
int n,m,x[maxn],c[maxn],r[maxn],p[maxn];
bool init(){
	scanf("%d%d",&n,&m);
	for (int i=2;i<=n;++i) scanf("%d",x+i);
	for (int i=1;i<=n;++i) scanf("%d",c+i);
	for (int i=1;i<=n;++i) scanf("%d",r+i);
	for (int i=1;i<=n;++i) scanf("%d",p+i);
	return 1;
}
struct segment_tree{
	#define c0 p<<1
	#define c1 p<<1|1
	int fmn[maxn<<2],tag[maxn<<2];
	void update(int p){fmn[p]=min(fmn[c0],fmn[c1]);}
	void add_tag(int p,int v){fmn[p]+=v,tag[p]+=v;}
	void clear(int p){if (tag[p]) add_tag(c0,tag[p]),add_tag(c1,tag[p]),tag[p]=0;}
	void build(int p,int l,int r,int v[]){
		tag[p]=0;
		if (l==r){fmn[p]=v[l];return;}
		int mid=(l+r)>>1;
		build(c0,l,mid,v),build(c1,mid+1,r,v),update(p);
	}
	int query(int p,int l,int r,int a,int b){
		if (l==a&&r==b) return fmn[p];
		int mid=(l+r)>>1;clear(p);
		if (b<=mid) return query(c0,l,mid,a,b);
		else if (a>=mid+1) return query(c1,mid+1,r,a,b);
		else return min(query(c0,l,mid,a,mid),query(c1,mid+1,r,mid+1,b));
	}
	int query(int l,int r){
		if (l>r) return inf;
		return query(1,1,n,l,r);
	}
	void modify(int p,int l,int r,int a,int b,int v){
		if (l==a&&r==b){add_tag(p,v);return;}
		int mid=(l+r)>>1;clear(p);
		if (b<=mid) modify(c0,l,mid,a,b,v);
		else if (a>=mid+1) modify(c1,mid+1,r,a,b,v);
		else modify(c0,l,mid,a,mid,v),modify(c1,mid+1,r,mid+1,b,v);
		update(p);
	}
	void modify(int l,int r,int v){
		if (l>r) return;
		modify(1,1,n,l,r,v);
	}
}seg;
typedef pair<int,int> pii;
int pfx[maxn],sfx[maxn],lef[maxn];
int f[maxm][maxn];
pii t[maxn];
void prepare(){
	for (int i=1;i<=n;++i)
		lef[i]=lower_bound(x+1,x+n+1,x[i]-r[i])-x;
	for (int i=1;i<=n;++i)
    	t[i]=pii(x[i]-r[i],i);
    sort(t+1,t+n+1),sfx[n+1]=0;
    for (int j=n,i=n;i>=1;--i){
    	sfx[i]=sfx[i+1];
    	while (j>=1&&t[j].first>x[i])
    		sfx[i]+=p[t[j--].second];
    }
    for (int i=1;i<=n;++i)
    	t[i]=pii(x[i]+r[i],i);
    sort(t+1,t+n+1),pfx[0]=0;
    for (int j=1,i=1;i<=n;++i){
        pfx[i]=pfx[i-1];
        while (j<=n&&t[j].first<x[i])
            pfx[i]+=p[t[j++].second];
    }
}
int solve(){
	prepare();
	for (int i=1;i<=n;++i)
		f[1][i]=pfx[i]+c[i];
	for (int k=2;k<=m;++k){
		seg.build(1,1,n,f[k-1]);
		for (int j=1,i=1;i<=n;++i){
			while (j<=n&&t[j].first<x[i])
				seg.modify(1,lef[t[j].second]-1,p[t[j].second]),++j;
			f[k][i]=seg.query(1,i-1)+c[i];
		}
	}
	int ans=0;
    for (int i=1;i<=n;++i) ans+=p[i];
    for (int k=1;k<=m;++k)
        for (int i=1;i<=n;++i){
            int t=f[k][i]+sfx[i];
            ans=min(ans,t);
        }
    return ans;
}
int main(){
	freopen("jhaha.in","r",stdin);
	freopen("jhaha.out","w",stdout);
	init(),printf("%d\n",solve());
    return 0;
}
