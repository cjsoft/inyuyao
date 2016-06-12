#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define ll unsigned long long
#define N 10000005
ll n,m,k,l,t,s;
ll a[N],b[N],ans[N];
int main(){
	freopen("biao.out","w",stdout);
	for (int i=1;i<=10000000;i++){
		ll x=i;
		int t1=0,t2=0;
		while(x){
			t1++;
			if(x&1)a[t1]=1;else a[t1]=0;
			x>>=1;
		}
		for (int i=t1;i;i--)x=x*10+a[i];
		k=x;
		while(x){
			if(t2>t1)break;
			t2++;
			if(x&1)b[t2]=1;else b[t2]=0;
			x>>=1;
		}
		l=1;
		for (int i=1;i<=t1;i++)if(a[i]!=b[i])l=0;
		if(l)ans[++m]=k;
		if(m==349)break;
	}
	for (int i=324;i<=349;i++)printf("if(n==%d)puts(%c%llu%c);\n",i,'"',ans[i],'"');
	//for (int i=1;i<=m;i++)printf("%d,%llu\n",i,ans[i]);
}
