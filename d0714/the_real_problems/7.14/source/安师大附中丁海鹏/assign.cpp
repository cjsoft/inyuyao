#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
using namespace std;

struct Node{
	int id,v;
}f[30];

int n,m,wh=1,a[2][30],ans[2][30],v[30];

int cmp1(Node x,Node y){
	if(x.v!=y.v)return x.v>y.v;
	else return x.id<y.id;
}

int cmp2(Node x,Node y){
	return x.id<y.id;
}

void work(){
	for(int i=1;i<=n;i++){
		f[i].id=i;
		f[i].v=v[i];
	}sort(f+1,f+n+1,cmp1);
	sort(f+1,f+m+1,cmp2);
	int k=0;
	for(int i=1;i<=m;i++){
		ans[k][f[i].id]++;
		if(i&1)k^=1;
	}
}

void dfs(int x){
	if(x==n+1){work();return;}
	for(int i=a[0][x];i<=a[1][x];i++){
		v[x]=i;
		dfs(x+1);
	}
}

int main(){
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<=1;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++)wh*=a[1][i]-a[0][i]+1;
	scanf("%d\n",&m);
	dfs(1);
	for(int i=1;i<=n;i++){
		printf("%.6lf %.6lf\n",1.0*ans[0][i]/wh,1.0*ans[1][i]/wh);
	}return 0;
}
