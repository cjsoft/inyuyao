#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
int ans;
int a[25][25];
int b[25][25];
int y[25];
int n;
void dfs(int x)
{
	if(x==n+1)
	{
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		b[i][j]=y[i]^y[j];
		
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			
			if(((!a[i][j])|b[i][j])==0) return;
		
		}
		
	
		int cnt=0;
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		if(((!b[i][j])|a[i][j])==0) cnt++;
		ans=max(ans,cnt);
		return ;
	}
		y[x]=0;
		dfs(x+1);
		y[x]=1;
		dfs(x+1);
}
int main()
{
		freopen("fxxk.in","r",stdin);
	freopen("fxxk.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		scanf("%d",&a[i][j]);
		ans=-1;
		dfs(1);
		cout<<ans<<endl;
	}
	
}
