#include<cstdio>
#include<algorithm>
#include<cstring>
#include<ctime>
using namespace std;
#define N 2505
int a[N][N],t,n,m,x,y;
int main(){
	freopen("A.in","w",stdout);
	srand(time(NULL));
	n=2500;m=2501;
	printf("%d %d 1000000000\n",n,m+2499);
	for (int i=2;i<=n;i++){
		x=rand()%(i-1)+1;
		a[x][i]=a[i][x]=1;
		printf("%d %d %d\n",x,i,rand()%1000000);
	}
	while(t<m){
		x=rand()%n+1;
		y=rand()%n+1;
		if(a[x][y]==1)continue;
		a[y][x]=a[x][y]=1;
		printf("%d %d %d\n",x,y,rand()%1000000);
		t++;
	}
}
