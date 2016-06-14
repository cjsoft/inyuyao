#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
long long zans,a[10050];
int n,vis[10][10];
int cmp(int x,int y)
{
	return x>y;
}
void dfs()
{
	long long cnt=0;
	for (int i=1;i<=n;i++)
	cnt+=a[i]*a[i];
	zans=max(zans,cnt);
	for (int i=1;i<=n;i++)
	for (int j=i+1;j<=n;j++)
	if (i!=j&&vis[i][j]!=1)
	{
		//if (a[i]==0||a[j]==0) continue;
		vis[i][j]=1;
		vis[j][i]=1;
		int tmpa=a[i];
		int tmpb=a[j];
		a[i]=tmpa&tmpb;
		a[j]=tmpa|tmpb;
		//if (a[i]*a[i]+a[j]*a[j]>tmpa*tmpa+tmpb*tmpb)
		dfs();
		vis[i][j]=0;
		vis[j][i]=0;
		a[i]=tmpa;
		a[j]=tmpb;
		
	}
}
int main()
{
	freopen("B.in","r",stdin);
	freopen("B.in","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	sort(a+1,a+1+n,cmp);
	if (a[1]==0)
	{
		cout<<"0"<<endl;
		return 0;
	}
	for (int i=1;i<=n;i++)
	if (a[i]==0)
	n=i-1;
	//if (n<=4)
	//{
	//	zans=-1;
	//	dfs();
	//	printf("%d\n",zans);
	//	return 0;
	//}
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
		if (i!=j)
		{
			int nowa=a[i]&a[j];
			int nowb=a[i]|a[j];
			//if (nowa<nowb)
			//swap(nowa,nowb);
			//if (nowa!=a[i])
			//{
				a[i]=nowa;
				a[j]=nowb;
			//}
		}
	}
	long long ggg=0;
	for (int i=1;i<=n;i++)
	ggg+=a[i]*a[i];
	printf("%lld\n",ggg);
}
