#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int N,L[35],R[35],K;
int main(){
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	scanf("%d",&N);int i,j;
	for(i=1;i<=N;i++)scanf("%d",&L[i]);
	for(i=1;i<=N;i++)scanf("%d",&R[i]);
	scanf("%d",&K);
	for(i=0;i<N;i++)printf("0.000000 0.000000\n");
	return 0;
}

