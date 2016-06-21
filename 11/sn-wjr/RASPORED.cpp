#include<iostream>
#include<stdio.h>
#include<algorithm>
#define MAXN 100050
using namespace std;
int n,m;
long long a[2][100100];
int lowbit(int x){
	return x&(-x);
}
void insert(int id,int x,long long num){
	for(int i=x;i<=MAXN;i+=lowbit(i))
		a[id][i]+=num;
}
long long getsum(int id,int x){
	long long sum=0;
	for(int i=x;i;i-=lowbit(i))
		sum+=a[id][i];
	return sum;
}
int l[200050],t[200050],lt[200050];
int main(){
	freopen("RASPORED.in","r",stdin);
	freopen("RASPORED.out","w",stdout);
	scanf("%d%d",&n,&m);
	long long ans=0;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&l[i],&t[i]);
		insert(1,t[i],t[i]);
		insert(0,t[i],1);
		ans+=(long long)(l[i]);
		lt[i]=t[i];
	}
	sort(lt+1,lt+1+n);
	for(int i=1;i<=n;i++)
		ans-=(long long)lt[i]*(n-i+1);
	printf("%lld\n",ans);
	while(m--){
		int i,L,T;
		scanf("%d%d%d",&i,&L,&T);
		ans-=l[i];ans+=L;
		l[i]=L;
		//cout<<ans<<endl;
		ans+=(long long)t[i]*(getsum(0,MAXN)-getsum(0,t[i]-1));
		//cout<<ans<<endl;
		insert(0,t[i],-1);
		ans-=(long long)T*(getsum(0,MAXN)-getsum(0,T-1)+1);
	//cout<<ans<<endl;
		insert(0,T,1);
		insert(1,t[i],-t[i]);
		ans+=getsum(1,t[i]-1)-getsum(1,T-1);insert(1,T,T);
		t[i]=T;
		printf("%lld\n",ans);
		//cout<<endl;
	}
}