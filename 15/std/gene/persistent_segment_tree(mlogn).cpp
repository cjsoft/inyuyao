#include<bits/stdc++.h>
using namespace std;
typedef long long int64;
struct Tsegment_tree{
	static const int maxn=260010,maxnode=6000000;
	struct Tseg{
		Tseg *lc,*rc;
		int64 sf,si; int cnt;
	}t[maxnode],*root[maxn],*null;
	int n,tot;
	void clear(int newn){
		memset(t,0,sizeof(t)),tot=0;
		null=t,null->lc=null->rc=null;
		null->sf=null->si=null->cnt=0;
		n=newn,root[0]=null;
	}
	
	void modify(Tseg *t1,Tseg *&t2,int l,int r,const int &x,const int &f,const int &i){
		t2=&t[++tot],*t2=*t1,t2->sf+=f,t2->si+=i,++t2->cnt;
		if(l==r) return; int mid=(l+r)>>1;
		if(x<=mid) modify(t1->lc,t2->lc,l,mid,x,f,i);
		else modify(t1->rc,t2->rc,mid+1,r,x,f,i);
	}
	void query(Tseg *t1,Tseg *t2,int l,int r,int a,int b,int64 &sf,int64 &si,int64 &cnt){
		if(l>=a && r<=b){
			sf+=(t2->sf)-(t1->sf),si+=(t2->si)-(t1->si);
			cnt+=(t2->cnt)-(t1->cnt); return;
		}
		int mid=(l+r)>>1;
		if(a<=mid) query(t1->lc,t2->lc,l,mid,a,b,sf,si,cnt);
		if(b>mid) query(t1->rc,t2->rc,mid+1,r,a,b,sf,si,cnt);
	}
	void modify(int t1,int t2,int x,int f,int i){
		modify(root[t1],root[t2],0,n+1,min(x,n+1),f,i);
	}
	void query(int l,int r,int a,int b,int64 &sf,int64 &si,int64 &cnt){
		sf=si=cnt=0,query(root[l-1],root[r],0,n+1,a,b,sf,si,cnt);
	}
}t1,t2;

const int maxn=260010;
char s[maxn]; int f[maxn],n,m;
void init(){
	scanf("%d%d%s",&n,&m,s+1);
	for(int i=n;i>=1;--i)
		s[i*2]=s[i],s[i*2-1]='#';
	n=n*2+1,s[n]='#',s[n+1]=0,s[0]='$';
}

void manacher(){
    static int f[maxn]; int k=1; f[1]=0;
    for(int i=2;i<=n;++i){
        if(k+f[k]>=i)
            f[i]=min(k+f[k]-i,f[2*k-i]);
        else f[i]=-1;
        while(s[i+f[i]+1]==s[i-f[i]-1]) ++f[i];
        if(i+f[i]>=k+f[k]) k=i;
    }
    t1.clear(n),t2.clear(n);
    for(int i=1;i<=n;++i){
    	t1.modify(i-1,i,i-f[i],f[i],i);
    	t2.modify(i-1,i,i+f[i],f[i],i);
    }
}

void solve(){
	for(int i=1,l,r,mid;i<=m;++i){
		scanf("%d%d",&l,&r); int64 cnt,sf,si,ans=r-l+1;		
		l=2*l-1,r=2*r+1,mid=(l+r)>>1;
		t1.query(l,mid,0,l,sf,si,cnt),ans+=si-l*cnt;//i-f[i]<=l,ans+=(i-l)
		t1.query(l,mid,l+1,n+1,sf,si,cnt),ans+=sf;//i-f[i]>l,ans+=f[i]
		t2.query(mid+1,r,0,r,sf,si,cnt),ans+=sf;//i+f[i]<=r,ans+=f[i]
		t2.query(mid+1,r,r+1,n+1,sf,si,cnt),ans+=r*cnt-si;//i+f[i]>r,ans+=(r-i)
		printf("%lld\n",ans>>1);
	}
}

int main(){
	init();
	manacher();
	solve();
	return 0;
}
