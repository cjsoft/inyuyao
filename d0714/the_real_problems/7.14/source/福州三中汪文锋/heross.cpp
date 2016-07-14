#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
using namespace std;
typedef long long ll;
const ll INF=2147483640;
ll a[351][351],g[351][351][351];
ll n,m,kk;
void init()
{
	scanf("%d%d%d",&n,&m,&kk);
	cout<<n<<" "<<m<<" "<<kk<<endl;
	srand(time(0));
	for(int i=1;i<=n;printf("\n"),i++)
	  for(int j=1;j<=m;j++)
	    printf("%d ",rand()%1000+1);
}
int main()
{
	freopen("hero.in","w",stdout);
	init();
	return 0;
}
