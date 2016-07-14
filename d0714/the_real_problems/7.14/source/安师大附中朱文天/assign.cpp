#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 30

int n,m,s,a[N],b[N],L[N],R[N],A[N],B[N],temp[1005];

void init(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&L[i]);
	for(int i=1;i<=n;i++) scanf("%d",&R[i]);
	scanf("%d",&m);
}

void dfs(int x){
	if(x>n){
		s++;
		memset(temp,0,sizeof(temp));
		for(int i=1;i<=n;i++) temp[a[i]]++;
		for(int i=999;i>=0;i--) temp[i]+=temp[i+1];
		for(int i=n;i>=1;i--) b[i]=temp[a[i]]--;
		int tmp=0;
		for(int i=1;i<=n;i++){
			if(b[i]>m) continue;
			tmp++;
			if(tmp%4==1||tmp%4==0) A[i]++;
			else B[i]++;
		}
		return;
	}
	for(int i=L[x];i<=R[x];i++){
		a[x]=i;
		dfs(x+1);
	}
}

void out(){
	for(int i=1;i<=n;i++){
		if(i%4==1||i%4==0) printf("1.000000 0.000000\n");
		else printf("0.000000 1.000000\n");
	}
}

int main(){
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	init();
	if(n==m) out();
	else{
		dfs(1);
		for(int i=1;i<=n;i++) printf("%.6lf %.6lf\n",1.0*A[i]/s,1.0*B[i]/s);
	}
	return 0;
}
