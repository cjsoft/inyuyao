#include<bits/stdc++.h>
using namespace std;
int N,L[30],R[30],K;
typedef struct{
	int id,val;
}aa;
aa B[30];
int A[30],Ta[30],Tb[30];
bool cmp1(aa a,aa b){
	if(a.val==b.val)return a.id<b.id;
	return a.val>b.val;
}
bool cmp2(aa a,aa b){
	return a.id<b.id;
}
void dfs(int d){
	if(d>N){
		for(int i=1;i<=N;i++)
		B[i]=(aa){i,A[i]};
		sort(B+1,B+N+1,cmp1);
		sort(B+1,B+K+1,cmp2);
		for(int i=1;i<=K;i++)
		if(i%4<2)Ta[B[i].id]++;
		else Tb[B[i].id]++;
		return;
	}
	for(int i=L[d];i<=R[d];i++){
		A[d]=i;
		dfs(d+1);
		A[d]=0;
	}
}
int main(){
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
	scanf("%d",&L[i]);
	for(int i=1;i<=N;i++)
	scanf("%d",&R[i]);
	scanf("%d",&K);
	dfs(1);
	long long smg=1;
	for(int i=1;i<=N;i++)
	smg*=R[i]-L[i]+1;
	for(int i=1;i<=N;i++)
	printf("%.6lf %.6lf\n",1.0*Ta[i]/smg,1.0*Tb[i]/smg);
	return 0;
}
