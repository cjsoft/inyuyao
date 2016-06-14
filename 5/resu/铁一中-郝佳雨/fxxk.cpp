#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
using namespace std;
const int maxn = 1500;
vector<int> edge[maxn];
int T,n,cnt,flag,ans,vis[maxn],size[maxn],sum,dp[maxn],a[maxn][maxn];
void link(int a,int b)
{
	edge[a].push_back(b);
	edge[b].push_back(a);
}
void dfs(int u,int pre,int col)
{
	if(vis[u])
	{
		if(vis[u]!=col)flag=true;
		return;
	}
	vis[u]=col;size[cnt+col]++;
	for(int i = 0; i < edge[u].size(); i++)
		if(edge[u][i]!=pre)dfs(edge[u][i],u,3-col);
}
int main(void)
{
	freopen("fxxk.in","r",stdin);
	freopen("fxxk.out","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		sum=0;flag=false;
		memset(dp,0,sizeof(dp));
		memset(vis,0,sizeof(vis));
		for(int i = 1; i <= n; i++)edge[i].clear();
		scanf("%d",&n);
		for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
		{
			scanf("%d",&a[i][j]);
			if(a[i][j])sum++,link(i,j);
		}
		for(int i = 1; i <= n; i++)
			if(!vis[i])dfs(i,0,1),cnt+=2;
		if(flag)
		{
			printf("-1\n");
			continue;
		}
		dp[0]=1;
		for(int i = 0; i < cnt; i+=2)
		for(int j = 1000; j >= 0; j--)
		if(dp[j])
		{
			 dp[j+size[i+1]]=1;
			 dp[j+size[i+2]]=1;
		}
		ans=0;
		for(int i = 1; i <= n; i++)
			if(dp[i] && abs(i-(n/2))<abs(ans-(n/2)))ans=i;
		printf("%d\n",n*n-ans*ans-(n-ans)*(n-ans)-sum);
	}
	return 0;
}
		
		
