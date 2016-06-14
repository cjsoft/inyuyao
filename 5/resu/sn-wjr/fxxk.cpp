#include<iostream>
#include<stdio.h>
#include<vector>
using namespace std;
int a[1050][1050],n,vis[1005],num[1005],dp[1005][2005],tot;
int T;vector<int> G[1005];
int flag=0;
void dfs(int x,int col){
	vis[x]=2*tot-col;
	for(int i=0;i<G[x].size();i++){
		int nex=G[x][i];
		if(vis[nex]==vis[x]) flag=1;
		if(vis[nex]) continue;
		dfs(nex,col^1);
	}
}
int main(){
	freopen("fxxk.in","r",stdin);
	freopen("fxxk.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);flag=0;int cnt=0;
		for(int i=1;i<=n;i++) G[i].clear(),vis[i]=0; 
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				scanf("%d",&a[i][j]);
				if(a[i][j]&&i<=j){
					if(i!=j) G[i].push_back(j),G[j].push_back(i);
					else flag=1;cnt++;
				}
			}
		if(flag) {printf("-1\n");continue;}
		tot=0;
		for(int i=1;i<=n;i++)
			if(!vis[i]){
				tot++;
				dfs(i,0);
			}
		if(flag) {printf("-1\n");continue;}
		for(int i=1;i<=2*tot;i++) num[i]=0;
		for(int i=1;i<=n;i++) num[vis[i]]++;
		dp[0][0]=1;
		for(int i=0;i<tot;i++)
			for(int j=0;j<=n;j++)
				dp[i+1][j+num[2*i+1]]|=dp[i][j],dp[i+1][j+num[2*i+2]]|=dp[i][j];
		for(int i=n/2;i;i--)
				if(dp[tot][i]){
					printf("%d\n",(i*(n-i)-cnt)*2);break;
				}
	}
}
	