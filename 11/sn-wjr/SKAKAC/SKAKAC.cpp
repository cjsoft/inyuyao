#include<iostream>
#include<stdio.h>
#include<queue>
using namespace std;
int vis[35][35];
struct node{
	int x,y;
};
queue<node> q;
int a[35][35];
int mx[8]={-2,-1,-2,-1,2,1,2,1};
int my[8]={1,2,-1,-2,1,2,-1,-2};
int n,m,x,y;
int main(){
	freopen("SKAKAC.in","r",stdin);
	freopen("SKAKAC.out","w",stdout);
	scanf("%d%d",&n,&m);
	scanf("%d%d",&x,&y);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	q.push((node){x,y});
	while(!q.empty()){
		node now=q.front();
		x=now.x,y=now.y;q.pop();
		if(vis[x][y]<m)
			for(int i=0;i<8;i++)
				if((x+mx[i]>0&&x+mx[i]<=n&&y+my[i]>0&&y+my[i]<=n)&&(vis[x+mx[i]][y+my[i]]<vis[x][y]+1)&&((vis[x][y]+1)%a[x+mx[i]][y+my[i]]==0))
					vis[x+mx[i]][y+my[i]]=vis[x][y]+1,q.push((node){x+mx[i],y+my[i]});
	}
	int cnt=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(vis[i][j]==m) cnt++;
	printf("%d\n",cnt);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(vis[i][j]==m)
				printf("%d %d\n",i,j);
}