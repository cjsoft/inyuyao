#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define maxn 100010

using namespace std;

long long int ans=0;
int ai[maxn]={0};
int n;

int main()
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	int i,s=0;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	scanf("%d",&ai[i]);
	
	for(n=n;n>=1;n--)
	{s=0;
	 for(i=1;i<=n;i++)
	 {s|=ai[i];
	  ai[i]=s&ai[i+1];
	 }
	 ans+=(long long int)s*s;
	 if(s==0)break;
	}
	printf("%lld\n",ans);
	return 0;
}
