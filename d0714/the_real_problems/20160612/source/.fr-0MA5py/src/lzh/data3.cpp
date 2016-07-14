#include<iostream>
#include<algorithm>
#include<cstdio>
#include<ctime>
#define N 25
#define MAXN 1000
#define random(x)(rand()%(x))
using namespace std;
int l[N+1],r[N+1];
int n,k;
int main(){
	freopen("assign.in","w",stdout);
	srand((int)time(0));
	n=N;
	printf("%d\n",n);
	for (int i=1;i<=n;i++){
		l[i]=random(MAXN);
		r[i]=random(MAXN);
		if (l[i]>r[i])swap(l[i],r[i]);
	}
	for (int i=1;i<=n;i++)
		printf("%d ",l[i]);
	printf("\n");
	for (int i=1;i<=n;i++)
		printf("%d ",r[i]);
	printf("\n");
	printf("%d\n",random(n)+1);
	return 0;
}