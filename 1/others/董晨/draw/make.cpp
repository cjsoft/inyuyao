#include<cstdio>
int n,m,k,l;
int main(){
	freopen("draw.in","w",stdout);
	n=2000;m=2*n+2;
	printf("%d %d\n",n,m);
	for (int i=0;i<=n;i++)printf("%d 0 %d %d\n",i,i,n);
	for (int i=0;i<=n;i++)printf("0 %d %d %d\n",i,n,i);
}
