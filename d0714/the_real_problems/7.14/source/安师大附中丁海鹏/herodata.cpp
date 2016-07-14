#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int n=50,m=50,k=100;

int main(){
	freopen("hero.in","w",stdout);
	printf("%d %d %d\n",n,m,k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			printf("%d ",rand()%1000+1);
		}puts("");
	}return 0;
}
