#include<cstdio>
#include<ctime>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,t,x,y,z;
int main(){
	freopen("kth.in","w",stdout);
	srand(time(NULL));
	n=m=80000;
	printf("%d\n",n);
	for (int i=1;i<=n;i++)printf("%d ",rand()%3000-1500);
	puts("");
	printf("%d\n",m);
	for (int i=1;i<=m;i++){
		t=rand()%2+1;
		x=rand()%n+1,y=rand()%n+1;
		x=1,y=n;
		if(x>y)swap(x,y);
		if(t==1)z=rand()%3000-1500;
		else z=rand()%(y-x+1)+1;
		printf("%d %d %d %d\n",t,x,y,z);
	}
}	
