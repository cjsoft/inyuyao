#include<iostream>
#include<stdio.h>
using namespace std;
int cnt[25];
int n;
int a[100050];
int main(){
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		for(int j=0;j<20;j++)if(a[i]&(1<<j)) cnt[j]++;
	}
	long long ans=0;
	for(int i=1;i<=n;i++){
		int ls=0;
		for(int j=0;j<20;j++)
			if(cnt[j]){
				ls^=(1<<j);
				cnt[j]--;
			}
		ans+=(long long) ls*(long long) ls;
	}
	printf("%lld\n",ans);
}