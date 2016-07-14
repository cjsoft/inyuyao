#include <bits/stdc++.h>
using namespace std	;
typedef long long ll;
#define MAXN 25

int l[MAXN],r[MAXN];
int n,k;
int p[MAXN],t[MAXN];
int cmp(int x,int y){return p[x]>p[y]||(p[x]==p[y]&&x<y);}

int pa[MAXN],pb[MAXN];

void dfs(int x){
	if(x>n){
		for(int i=1;i<=n;++i)t[i]=i;
		sort(t+1,t+1+n,cmp);
		sort(t+1,t+1+k);
		for(int i=1;i<=k;++i){
			if((i&3)<2)++pa[t[i]];
			else ++pb[t[i]];
		}
		return;
	}
	for(int i=l[x];i<=r[x];++i)
		p[x]=i,dfs(x+1);
}

double ppa[MAXN],ppb[MAXN];
int b[MAXN];
void dfs2(int x){
	if(x>n){
		int cnt=0;
		for(int i=1;i<=n;++i)
			cnt+=b[i];
		if(cnt!=k)return;
		if(k==n){
			double cnt=1;
			for(int j=1;j<=n;++j)
				cnt*=r[j]-l[j]+1;
			int pn=0;
			for(int j=1;j<=n;++j){
				if(b[j]){
					++pn;
					if((pn&3)<2)ppa[j]+=cnt;
					else ppb[j]+=cnt;
				}
			}
			return;
		}
		printf("");
		for(int i=1;i<=n;++i)
			if(!b[i]){
				for(int k=l[i];k<=r[i];++k){
					double cnt=1;
					for(int j=1;j<=n;++j){
						if(j==i)continue;
						if(!b[j]){
							if(l[j]>k||(l[j]==k&&j<i))cnt=0;
							else if(j<i)cnt=cnt*(min(k-1,r[j])-l[j]+1);
							else cnt=cnt*(min(k,r[j])-l[j]+1);
						}else{
							if(r[j]<k||(r[j]==k&&j>i))cnt=0;
							else if(j>i)cnt=cnt*(r[j]-max(k+1,l[j])+1);
							else cnt=cnt*(r[j]-max(k,l[j])+1);
						}
					}
					int pn=0;
					for(int j=1;j<=n;++j){
						if(b[j]){
							++pn;
							if((pn&3)<2)ppa[j]+=cnt;
							else ppb[j]+=cnt;
						}
					}
				}
			}
		
	}else b[x]=0,dfs2(x+1),b[x]=1,dfs2(x+1);
}

int main(){
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&l[i]);
	for(int i=1;i<=n;++i)
		scanf("%d",&r[i]);
	scanf("%d",&k);
	double tm=1;
	for(int i=1;i<=n;++i)
		tm*=r[i]-l[i]+1;
	if(tm<=2000000){
		dfs(1);
		for(int i=1;i<=n;++i)
			printf("%.6lf %.6lf\n",(double)pa[i]/tm,(double)pb[i]/tm);
		return 0;
	}else{
		dfs2(1);
		for(int i=1;i<=n;++i)
			printf("%.6lf %.6lf\n",ppa[i]/tm,ppb[i]/tm);
		return 0;
	}
}
