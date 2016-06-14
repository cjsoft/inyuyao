#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define N 100005
#define INF 5000005
int n,m,k,l,t,s,ans,Q,T,r,x,y,z;
int a[N],b[N];
int main(){
	freopen("kth.in","r",stdin);
	freopen("baoli.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)scanf("%d",&a[i]);
	scanf("%d",&Q);
	while(Q--){
		scanf("%d%d%d%d",&t,&l,&r,&x);
		if(t==1)for (int i=l;i<=r;i++)a[i]+=x;
		if(t==2){
			k=0;
			for (int i=l;i<=r;i++)b[++k]=a[i];
			nth_element(b+1,b+x,b+k+1);
			printf("%d\n",b[x]);
		}
	}
}
