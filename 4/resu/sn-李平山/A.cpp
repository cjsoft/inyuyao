#include<iostream>
#include<stdio.h>
#include<string.h>
#include<queue>
#include<vector>
using namespace std;

long long  mod=1e9+7;
int head[2505],tot,to[2505],val[2505],nex[2505];
long long  dis[505][505];
long long d[505];
bool vv[303][303];
int minn[505],xi[505];
int n,m,t;
bool vis[505];
long long ans;
void add(int x,int y,int v)
{
	int tmp=head[x];
	head[x]=++tot;
	to[tot]=y;
	val[tot]=v;
	nex[tot]=tmp;	
}
struct node{
	int x,st;	
};

queue<int> q;
queue<node> qq;
void spfa1(int x)
{
	for(int i=1;i<=n;i++)
	d[i]=-1;
	d[1]=0;
	vis[1]=1;
	q.push(1);
	while(!q.empty())
	{
		int now=q.front();
		q.pop();
		vis[now]=0;
		
		for(int i=head[now];i!=-1;i=nex[i])
		{
			int v=to[i];
		
			if(d[v]==-1||d[v]>(d[now]+val[i]+x)%mod)
			{
					d[v]=(d[now]+val[i]+x)%mod;
				
					if(!vis[v])
					{
						vis[v]=1;
						q.push(v);	
					}
					
			}	
		}
	}
	for(int i=1;i<=n;i++)
	{
		ans=(ans+d[i])%mod;	
	}

	
}
void spfa()
{
	memset(d,-1,sizeof(d));
	d[1]=0;
	vis[1]=1;
	q.push(1);
	minn[1]=0;
	while(!q.empty())
	{
		int now=q.front();
		q.pop();
		vis[now]=0;
		
		for(int i=head[now];i!=-1;i=nex[i])
		{
			int v=to[i];
			if(d[v]==-1||d[v]>=d[now]+val[i])
			{
					if(d[v]==d[now]+val[i])
					minn[v]=min(minn[v],minn[now]+1);
					else 
					{
						minn[v]=minn[now]+1;
						d[v]=d[now]+val[i];
						if(!vis[v])
						{
							vis[v]=1;
							q.push(v);	
						}
					}
					
			}	
		}
	}

//	for(int i=1;i<=n;i++)
//	for(int j=minn[i];j<=n;j++)
//			dis[i][j]=d[i];
//	
	
}
void bfs()
{
	memset(vv,0,sizeof(vv));
	vv[1][0]=1;
	dis[1][0]=0;
	node no;
	no.x=1;
	no.st=0;
	qq.push(no);
	while(!qq.empty())
	{
		node now=qq.front();
		qq.pop();
		int nn=now.x;
		int st=now.st;
		for(int i=head[nn];i!=-1;i=nex[i])
		{
			int v=to[i];
	
			if(dis[v][st+1]==-1||dis[v][st+1]>dis[nn][st]+val[i])
			{	
				dis[v][st+1]=dis[nn][st]+val[i];
				if(!vv[v][st+1])
				{
					vv[v][st+1]=1;
					node nex;
					nex.x=v;
					nex.st=st+1;
					qq.push(nex);	
				}
			}
		}
	}
}
int main()
{
	
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	int aa,bb,cc;
	scanf("%d%d%d",&n,&m,&t);
	memset(head,-1,sizeof(head));
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&aa,&bb,&cc);
		add(aa,bb,cc);
		add(bb,aa,cc);
	}
	if(t*n<=6000)
	{
		for(int i=0;i<=t;i++)
		{
		spfa1(i);	
		}
		cout<<ans<<endl;
		return 0;
	}
	else 
	memset(dis,-1,sizeof(dis));
	spfa();

	bfs();
	xi[1]=0;
	
	for(int i=2;i<=n;i++)
	{
		int now;
		for(int j=1;j<=minn[i];j++)
		{
			if(dis[i][j]!=-1&&!xi[i])
			{
				 xi[i]=j;
				 now=dis[i][j];
			}
			if(dis[i][j]==-1||dis[i][j]>now)
			dis[i][j]=-1;
	
		}
	}
	
	for(int i=2;i<=n;i++)
	{
		ans=(ans+dis[i][minn[i]])%mod;	
	}
	for(int tt=1;tt<=t;tt++)
	{

		for(int i=2;i<=n;i++)
		{
			long long now=1e9+77;
	
			for(int j=1;j<=minn[i];j++)
			{
					if(dis[i][j]==-1) continue;
				
					now=min(now,(dis[i][j]+j*tt)%mod);
			}
			
			ans=(ans+now)%mod;	
		}
	
	}
	cout<<ans<<endl;
		
}
