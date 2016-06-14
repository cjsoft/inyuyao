#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
int n,ans[20],tot,val[100005],cnt;
LL ret;
int main(void)
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	scanf("%d",&n);
	int x,base,bit;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d",&x);
		base=1,bit=0;
		while(x)
		{
			if(x & base)x-=base,ans[bit]++,tot=max(tot,bit);
			base<<=1;
			bit++;
		}
	}
	base=1;
	for(int i = 0; i <= tot; i++)
	{
		for(int j = 1; j <= ans[i]; j++)
			val[j]+=base;
		cnt=max(cnt,ans[i]);
		base<<=1;
	}
	for(int i = 1; i <= cnt; i++)
		ret+=((LL)val[i])*((LL)val[i]);
	printf("%lld\n",ret);
	return 0;
}
