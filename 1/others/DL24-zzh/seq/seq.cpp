#include<cstdio>
long long s[110000];
int n,m;

void naive(){
	for (int tt=0;tt<m;tt++){
		int t1,t2;
		scanf("%d",&t1);
		if (!t1) {
			long long t3;
			scanf("%d%d%lld",&t1,&t2,&t3);
			for (int i=t1;i<=t2;i++) s[i]+=t3;
		}
		else if (t1==1){
			scanf("%d%d",&t1,&t2);
			for (int i=t1;i<=t2;i++) s[i]=-s[i];
		}
		else {
			scanf("%d%d",&t1,&t2);
			long long ans=0;
			for (int i=t1;i<=t2;i++) {
				if (s[i]<0) ans-=s[i];
				else ans+=s[i];
			}
			printf("%lld\n",ans);
		}
	}
}

int main(){
    freopen("seq.in","r",stdin);
    freopen("seq.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) scanf("%lld",s+i);
	if (n<=10000){
		naive();
		return 0;
	}
	return 0;
}
