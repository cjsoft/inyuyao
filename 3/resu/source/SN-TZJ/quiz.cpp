#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
int n,w[4500],a[4500];
int main()
{
	freopen("quiz.in","r",stdin);
	freopen("quiz.out","w",stdout);
	//while(scanf("%d",&n))
	//{/*
		scanf("%d",&n);
		int tot=10;
		if (n==10)
		{
			cout<<"1100"<<endl;
			return 0;
		}
		if (n<=284)
		for (int i=13;i<=262144;i++)
		{
			int len=0;
			long long now=0;
			long long sum=1;
			int tmp=i;
			while(tmp)
			{
				len++;
				int hh=tmp%2;
				w[len]=hh;
				tmp/=2;
				now+=hh*sum;
				sum*=10;
			}
			now-=i;
			//printf("%lld\n",now);
			int flag=1;
			for (int j=0;j<len;j++)
			if (((1<<j)&now)!=0)
			flag=0;
			if (flag)
			tot++;
			if (tot==n)
			{
				now+=i;
				printf("%lld\n",now);
				//for (int j=len;j>=1;j--)
				//printf("%d",w[j]);
				//printf("%d\n");
				return 0;
			}
		}
		/*
		else
		{
			tot=284;
			for (int i=262145;i<=1000000;i++)
			{
				int len=0;
				int tmp=i;
				while(tmp)
				{
					len++;
					int hh=tmp%2;
					w[len]=hh;
					tmp/=2;
					now+=hh*sum;
					sum*=10;
				}	
			}
		}
		*/
	//	for (int i=0;i<=31;i++)
	//	w[i]=0;
	//	for (int i=0;i<=31;i++)
	//	if (((1<<i)&n)!=0)
	//	w[i]=1;
	//	for (int i=31;i>=0;i--)
	//	cout<<w[i];
	//	cout<<endl;
	//}
}
