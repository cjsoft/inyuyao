#include<bits/stdc++.h>

using namespace std;

int n=3,m=3,k;
int main()
{
	freopen("hero.in","w",stdout);
	srand(time(0));
	k=rand()%100;
	cout<<n<<" "<<m<<" "<<k<<endl;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
			printf("%d ",rand()%100);
		printf("\n");
	}
	return 0;
}
