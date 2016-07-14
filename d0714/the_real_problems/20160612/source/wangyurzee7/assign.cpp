#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#define N 27

using namespace std;
int n,kk;


int l[N],r[N];
int a[N];
int scr[N];
inline bool cmp(const int &x,const int &y){
	return scr[x]>scr[y]||scr[x]==scr[y]&&x<y;
}
long double ans[N][2];
void baoli(int u){
	if (u>n){
//		puts("qwq");
		for (int i=1;i<=n;++i) a[i]=i;
		sort(a+1,a+n+1,cmp);
		sort(a+1,a+kk+1);
//		for (int i=1;i<=n;++i) printf("%d ",a[i]);puts("");
		for (int i=1;i<=kk;++i)
			++ans[a[i]][(i&3)>1];
		return;
	}
	for (int i=l[u];i<=r[u];++i){
		scr[u]=i;
		baoli(u+1);
	}
}

bool psd[N];
int cnt0;
void dfs_0(int u){
	if (n-u+1<kk-cnt0) return;
	if (cnt0>kk) return;
	if (u>n){
		long double res=0;
		int mx=1000,mn=0;
		for (int i=1;i<=n;++i)
			if (psd[i]) mx=min(mx,r[i]);
			else mn=max(mn,l[i]);
		for (int i=1;i<=n;++i)if (psd[i])
			for (int j=max(mn,l[i]);j<=mx;++j){
				long double now=1;
				for (int k=1;k<i;++k)
					if (psd[k])now*=((long double)r[k]-max(j,l[k])+1)/(r[k]-l[k]+1);
					else now*=((long double)min(j-1,r[k])-l[k]+1)/(r[k]-l[k]+1);
				for (int k=i+1;k<=n;++k)
					if (psd[k])now*=((long double)r[k]-max(j+1,l[k])+1)/(r[k]-l[k]+1);
					else now*=((long double)min(j,r[k])-l[k]+1)/(r[k]-l[k]+1);
				res+=now/(r[i]-l[i]+1);
			}
		for (int i=1;i<=kk;++i)
			ans[a[i]][(i&3)>1]+=res;
		return;
	}
	a[++cnt0]=u;
	psd[u]=1;
	dfs_0(u+1);
	psd[u]=0;
	--cnt0;
	
	dfs_0(u+1);
}

int main(){
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;++i) scanf("%d",&l[i]);
	for (int i=1;i<=n;++i) scanf("%d",&r[i]);
	scanf("%d",&kk);
	int sum=1;
	for (int i=1;i<=n;++i){
		sum*=(r[i]-l[i]+1);
		if (sum>2e6) break;
	}
	if (sum>2e6){
		memset(psd,0,sizeof(psd));
		memset(ans,0,sizeof(ans));
		cnt0=0;
		dfs_0(1);
		for (int i=1;i<=n;++i)
			printf("%.6lf %.6lf\n",(double)ans[i][0],(double)ans[i][1]);
	}
	else{
		memset(ans,0,sizeof(ans));
		baoli(1);
		for (int i=1;i<=n;++i)
			printf("%.6lf %.6lf\n",(double)ans[i][0]/sum,(double)ans[i][1]/sum);
	}
	return 0;
}
