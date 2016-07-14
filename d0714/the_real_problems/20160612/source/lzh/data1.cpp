#include<iostream>
#include<algorithm>
#include<cstdio>
#define N 50
#define MAXN 100
#include<ctime>
#define random(x)(rand()%(x))
using namespace std;
int n,m,k;
int main(){
	freopen("hero.in","w",stdout);
	srand((int)time(0));
	n=random(N)+1,m=random(N)+1;
	printf("%d %d %d\n",n,m,random(MAXN)+1);
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++)
			printf("%d ",random(MAXN)+1);
		printf("\n");
	}
	return 0;
}