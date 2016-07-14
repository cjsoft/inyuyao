#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 100
using namespace std;
int n,K,i,l[N],r[N],b[N],num,flag[N];
double ans[2][N];
double calc1(int l,int r,int x)
{
	if (x>r)return 0;
	if (x<=l)return 1;
	return (double)(r-x+1)/(r-l+1);
}
double calc2(int l,int r,int x)
{
	if (x>r)return 0;
	if (x<l)return 1;
	return (double)(r-x)/(r-l+1);
}
double calc3(int l,int r,int x)
{
	if (x>r)return 1;
	if (x<=l)return 0;
	return (double)(x-l)/(r-l+1);
}
double calc4(int l,int r,int x)
{
	if (x>=r)return 1;
	if (x<l)return 0;
	return (double)(x-l+1)/(r-l+1);
}
void work()
{
	int i,j,k;
	double p;
	for (i=1;i<=n;i++)flag[i]=0;
	for (i=1;i<=K;i++)
		flag[b[i]]=1;
	//for (i=1;i<=n;i++)printf("%d ",flag[i]);puts("");
	//for (i=1;i<=K;i++)printf("%d ",b[i]);puts("");
	for (i=1;i<=K;i++)
		for (j=l[b[i]];j<=r[b[i]];j++)
		{
			p=1.0/(r[b[i]]-l[b[i]]+1);
			for (k=1;k<b[i];k++)
				if (!flag[k])
					p=p*calc3(l[k],r[k],j);
			//printf("%.6f\n",p);
			for (k=b[i]+1;k<=n;k++)
				if (!flag[k])
					p=p*calc4(l[k],r[k],j);
			//printf("%.6f\n",p);
			for (k=1;k<i;k++)
				p=p*calc1(l[b[k]],r[b[k]],j);
			//printf("%.6f\n",p);
			for (k=i+1;k<=K;k++)
				p=p*calc2(l[b[k]],r[b[k]],j);
			//printf("%d %d %.6f\n",i,j,p);
			ans[1][b[1]]+=p;
			for (k=2;k<=K;k++)
				if ((k-2)%4<2)
					ans[0][b[k]]+=p;else
					ans[1][b[k]]+=p;
		}
}
void dfs(int k,int sum)
{
	if (n-k+1+sum<K)return;
	if (sum==K)
	{
		work();
		return;
	}
	if (k>n)return;
	dfs(k+1,sum);
	b[++num]=k;
	dfs(k+1,sum+1);
	num--;
}
int main()
{
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	//printf("%.6f\n",calc3(1,1,1));
	scanf("%d",&n);
	for (i=1;i<=n;i++)scanf("%d",&l[i]);
	for (i=1;i<=n;i++)scanf("%d",&r[i]);
	scanf("%d",&K);
	dfs(1,0);
	for (i=1;i<=n;i++)
		printf("%.6f %.6f\n",ans[1][i],ans[0][i]);
}