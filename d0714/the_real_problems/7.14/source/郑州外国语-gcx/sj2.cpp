#include<bits/stdc++.h>
using namespace std;


int main()
{
	freopen("area.in","w",stdout);
	int n=20,li=1000000;
	srand(time(0));
	printf("%d\n",n);
	for(int i=1;i<=n;++i)
		printf("%d %d\n",rand()%100,rand()%100);
	
}
