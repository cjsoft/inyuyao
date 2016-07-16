#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=101000;
const long long oo=20000000;
long long h[MAXN];
int n;
long long st[MAXN][30];
int pow2[21];
int lg[MAXN];
long long cost;
long long sum[MAXN];
long long sumsqr[MAXN];
void init_st()
{
	pow2[0]=1;
	for(int i=1;i<=20;i++)pow2[i]=pow2[i-1]*2;
	int p=-1;
	for(int j=1;j<=n;j++)
	{
		st[j][0]=h[j];
		if(j==pow2[p+1])p++;
		lg[j]=p;
	}
	for(int k=1;pow2[k]<=n;k++)
	{
		for(int j=1;j+pow2[k]-1<=n;j++)
		st[j][k]=max(st[j][k-1],st[j+pow2[k-1]][k-1]);
	}
}
int RMQ(int a,int b)
{
	int del=b-a+1;
	del=lg[del];
	return max(st[a][del],st[b-pow2[del]+1][del]);
}
void init_sum()
{
	sum[0]=sumsqr[0]=0;
	for(int i=1;i<=n;i++)
	{
		sum[i]=sum[i-1]+h[i];
		sumsqr[i]=sumsqr[i-1]+(long long)h[i]*(long long)h[i];
	}
}
void init()
{
	scanf("%d%I64d",&n,&cost);
	for(int i=1;i<=n;i++)scanf("%I64d",&h[i]);
	h[0]=h[n+1]=oo;
	init_st();
	init_sum();
}

int stack[MAXN],top;
long long f[MAXN];
long long fmin(long long A,long long B,long long C,long long mn,long long mx)
{
	long long ret=oo*oo;
	long long topx=(-B)/(2*A);
	for(int i=0;i<=1;i++)
	{
		if(mn<=topx&&topx<=mx)ret=min(ret,A*topx*topx+B*topx+C);
		topx++;
	}
	ret=min(ret,min(A*mn*mn+B*mn+C,A*mx*mx+B*mx+C));
	return ret;
}
long long H(int a,int b)
{
	if(a==b-1)return cost*abs(h[b]-h[a]);
	int mn=RMQ(a+1,b-1)+1;
	int mx=min(h[a],h[b]);
	long long A=b-a-1,
		 		B=-2*(sum[b-1]-sum[a]),
				C=sumsqr[b-1]-sumsqr[a];
	if(a!=0)B-=cost,C+=cost*h[a];
	if(b!=n+1)B-=cost,C+=cost*h[b];
	return fmin(A,B,C,mn,mx);
}
void work()
{
	top=0;
	stack[top++]=0;
	stack[top++]=1;
	f[1]=0;
	for(int i=2;i<=n+1;i++)
	{
		if(i!=n+1)f[i]=f[i-1]+cost*abs(h[i]-h[i-1]);
		else f[i]=f[i-1];
		while(h[stack[top-1]]<h[i])
		{
			f[i]=min(f[i],f[stack[top-1]]+H(stack[top-1],i));
			top--;
		}
		f[i]=min(f[i],f[stack[top-1]]+H(stack[top-1],i));
		if(h[stack[top-1]]==h[i])top--;
		stack[top++]=i;
	}
	printf("%I64d\n",f[n+1]);
}
int main()
{
	freopen("repair.in","r",stdin);
	freopen("repair.out","w",stdout);
	init();
	work();
}
