#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=233;

int N,L[maxn],R[maxn],K,C[maxn][2];

int S[maxn],idx[maxn];
inline bool by_s(const int &a,const int &b){
	if(S[a]!=S[b]) return S[a]>S[b];
	else return a<b;
}

void solve(){
	for(int i=0;i<N;++i) idx[i]=i;
	sort(idx,idx+N,by_s);
	sort(idx,idx+K);
	int d=0,c=1;
	for(int i=0;i<K;++i){
		++C[idx[i]][d];
		++c;
		if(c>=2){
			d^=1;
			c=0;
		}
	}
}

void dfs(int p){
	if(p==N){
		solve();
		return;
	}
	for(int i=L[p];i<=R[p];++i){
		S[p]=i;
		dfs(p+1);
	}
}

double tot=1;

int main(){
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	scanf("%d",&N);
	for(int i=0;i<N;++i) scanf("%d",L+i);
	for(int i=0;i<N;++i) scanf("%d",R+i);
	scanf("%d",&K);
	dfs(0);
	for(int i=0;i<N;++i) tot*=R[i]-L[i]+1;
	for(int i=0;i<N;++i){
		printf("%.6lf %.6lf\n",C[i][0]/tot,C[i][1]/tot);
	}
}
