#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <queue>
#define maxn 50010

using namespace std;

vector<int> g[maxn];
void AddEdge(int f,int t)
{
	g[f].push_back(t);
	g[t].push_back(f);
}

int toi[maxn]={0},ans[maxn]={0};

int n,q;
vector<int> ani[maxn];

int d[maxn]={0};

void bfs(int s)
{
	int i,l,x,y;
	queue<int> q;
	for(i=1;i<=n;i++)
	d[i]=-1;
	d[s]=0;
	q.push(s);
	while(!q.empty())
	{
		x=q.front();q.pop();
		l=g[x].size();
		for(i=0;i<l;i++)
		{y=g[x][i];
		 if(d[y]==-1)
		   {d[y]=d[x]+1;
		    q.push(y);
		   }
		}
	}
	for(i=0;i<ani[s].size();i++)
	ans[ani[s][i]]=d[toi[ani[s][i]]];
}

int main()
{
	freopen("drive.in","r",stdin);
	freopen("drive.out","w",stdout);
	
	int i,x,y;
	scanf("%d",&n);
	for(i=1;i<n;i++)
	AddEdge(i,i+1);
	AddEdge(n,1);
	for(i=0;i<n-3;i++)
	{scanf("%d%d",&x,&y);
	 AddEdge(x,y);
	}
	scanf("%d",&q);
	for(i=0;i<q;i++)
	{scanf("%d%d",&x,&y);
	 if(x>y)swap(x,y);
	 toi[i]=y;
	 ani[x].push_back(i);
	}
	
	for(i=1;i<=n;i++)
	if(ani[i].size())bfs(i);
	
	for(i=0;i<q;i++)
	printf("%d\n",ans[i]);
	
	return 0;
}
