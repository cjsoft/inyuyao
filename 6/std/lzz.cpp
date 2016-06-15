#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
const int maxn=100005,L=100;
int n,m,S;
int a[maxn];
int *sum[maxn];

double P[L+5];

void init()
{
	scanf("%d%d",&n,&m);
	S=int(sqrt(n)+.1);
	for(int d=1;d<=S;d++)
	{
		sum[d]=new int[d];
		memset(sum[d],0,d*sizeof(int));
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",a+i);
		for(int d=1;d<=S;d++)
			sum[d][i%d]+=a[i];
	}
}

void work()
{
	int all;
	double ans;
	for(int t,k,d,x,y,qi=1;qi<=m;qi++)
	{
		scanf("%d",&d);
		if(d==1)
		{
			scanf("%d%d",&k,&t);
			for(d=1;d<=S;d++)
				sum[d][k%d]+=t-a[k];
			a[k]=t;
		}
		else
		{
			ans=0;
			scanf("%d%d%d",&t,&k,&d);
			x=n-1;
			for(int i=1;i<=t;i++)
				scanf("%d",&y),x=min(x,y);
			if(t==1)
			{
				if(d<=S)all=sum[d][k%d];
				else
				{
					all=a[k];
					for(int i=1;k-i*d >0;i++)all+=a[k-i*d];
					for(int i=1;k+i*d<=n;i++)all+=a[k+i*d];
				}
				printf("%d.0000\n",all);
				continue;
			}
			P[0]=1;
			for(y=1;y<=L+1;y++)
				if(y>x)P[y]=0;
				else P[y]=P[y-1]*(x-y+1)/(n-y);
			ans=a[k];
			for(int i=1;i<=L&&k-i*d>0;i++)
				ans+=P[i]*a[k-i*d];
			for(int i=1;i<=L&&k+i*d<=n;i++)
				ans+=P[i]*a[k+i*d];
			printf("%.4lf\n",ans);
		}
	}
}

int main()
{
	freopen("lzz.in","r",stdin);
	freopen("lzz.out","w",stdout);
	init();
	work();
	return 0;
}

