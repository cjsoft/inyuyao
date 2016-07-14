#include <cstdio>
#include <ctime>
#include <algorithm>
using namespace std;

int main(){
	freopen("hero.in","w",stdout);
	printf("290 290 1000000\n");
	for(int i=1;i<=290;i++,printf("\n"))
		for(int j=1;j<=290;j++)
			printf("%d ",rand()%1000000+1);
	return 0;
}
