#include<cmath>
#include<cstdio>
#include<cstring>
#include<cassert>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=20005,maxm=105;
int n,m,dist[maxn],cost[maxn],radius[maxn],price[maxn];
void init(){
    scanf("%d%d",&n,&m);
    for (int i=2;i<=n;++i) scanf("%d",&dist[i]);
    for (int i=1;i<=n;++i) scanf("%d",&cost[i]);
    for (int i=1;i<=n;++i) scanf("%d",&radius[i]);
    for (int i=1;i<=n;++i) scanf("%d",&price[i]);
}
struct funcional_segtree{
    static const int maxnode=maxn*25;
    struct node{
        node *c[2];int sum;
    }*root[maxn],t[maxnode];
    int ver,tot;
    void clear(){
        root[0]=t,root[0]->c[0]=root[0]->c[1]=root[0];
        ver=tot=root[0]->sum=0;
    }
    node *newnode(node *x){
        node *cur=t+(++tot);
        return *cur=*x,cur;
    }
    void modify(node *ever,node *&now,int l,int r,int a,int b,int v){
        now=newnode(ever);
        if (l==a&&r==b){now->sum+=v;return;}
        int mid=(l+r)>>1;
        if (b<=mid) modify(ever->c[0],now->c[0],l,mid,a,b,v);
        else if (a>=mid+1) modify(ever->c[1],now->c[1],mid+1,r,a,b,v);
        else modify(ever->c[0],now->c[0],l,mid,a,mid,v),modify(ever->c[1],now->c[1],mid+1,r,mid+1,b,v);
    }
    int modify(int l,int r,int v){
        modify(root[ver],root[ver+1],1,n,l,r,v);
        return ++ver;
    }
    int query(node *p,int l,int r,int x){
        if (l==r) return p->sum;
        int mid=(l+r)>>1;
        if (x<=mid) return p->sum+query(p->c[0],l,mid,x);
        else return p->sum+query(p->c[1],mid+1,r,x);
    }
    int query(int tim,int x){
        return query(root[tim],1,n,x);
    }
}seg;
typedef pair<int,int> pii;
int root[maxn];
int pfx[maxn],sfx[maxn];
void prepare(){
	seg.clear(),root[0]=0;
    static pii t[maxn];
    for (int i=1;i<=n;++i)
        t[i]=pii(dist[i]+radius[i],i);
    sort(t+1,t+n+1),pfx[0]=0;
    for (int j=1,i=1;i<=n;++i){
        root[i]=root[i-1],pfx[i]=pfx[i-1];
        while (j<=n&&t[j].first<dist[i]){
            int idx=t[j].second;
            int pos=lower_bound(dist+1,dist+n+1,dist[idx]-radius[idx])-dist;
            if (pos>1) root[i]=seg.modify(1,pos-1,price[idx]);
            pfx[i]+=price[idx],++j;
        }
    }
    for (int i=1;i<=n;++i)
    	t[i]=pii(dist[i]-radius[i],i);
    sort(t+1,t+n+1),sfx[n+1]=0;
    for (int j=n,i=n;i>=1;--i){
    	sfx[i]=sfx[i+1];
    	while (j>=1&&t[j].first>dist[i]){
    		int idx=t[j].second;
    		sfx[i]+=price[idx],--j;
    	}
    }
}
const int inf=0x3f3f3f3f;
int f[maxm][maxn];
void solve(int k,int st,int ed,int l,int r){
    if (st>ed) return;
    int mid=(st+ed)>>1,best_id=-1;
    for (int i=l;i<=min(mid-1,r);++i){
        int t=f[k-1][i]+seg.query(root[mid],i)+cost[mid];
        if (f[k][mid]>t) f[k][mid]=t,best_id=i;
    }
    solve(k,st,mid-1,l,best_id);
    solve(k,mid+1,ed,best_id,r);
}
void work(){
    prepare();
    memset(f,63,sizeof(f));
    for (int i=1;i<=n;++i)
        f[1][i]=pfx[i]+cost[i];
    for (int i=2;i<=m;++i)
        solve(i,1,n,1,n);
    int ans=0;
    for (int i=1;i<=n;++i)
        ans+=price[i];
    for (int k=1;k<=m;++k)
        for (int i=1;i<=n;++i){
            int t=f[k][i]+sfx[i];
            ans=min(ans,t);
        }
    printf("%d\n",ans);
}
int main(){
    init(),work();
    return 0;
}
/*
O(nm*log^2n)
*/
