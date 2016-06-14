#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define M 1000000007
#define inf 1000000007
#define maxn 2510

using namespace std;

struct Edge{int to,wi;};
vector<Edge> g[maxn];
void AddE(int f,int to,int wi)
{
	Edge ex;
	ex.to=to;ex.wi=wi;
	g[f].push_back(ex);
}
void AddEdge(int f,int to,int wi)
{
	AddE(f,to,wi);
	AddE(to,f,wi);
}

int n,m,t;

int d[maxn]={0},dis[maxn]={0};
bool inq[maxn]={0};

long long int ans=0;

void init()
{
	int x,l,i;
	for(x=1;x<=n;x++)
	{l=g[x].size();
	 for(i=0;i<l;i++)
	 g[x][i].wi++;
	}
}

void spfa(int s)
{
	int i,x,y,l;
	queue<int> q;
	for(i=1;i<=n;i++)
	{d[i]=-1;dis[i]=inf;inq[i]=0;}
	d[s]=dis[s]=0;
	q.push(s);inq[s]=1;
	
	while(!q.empty())
	{
		x=q.front();q.pop();inq[x]=0;
		l=g[x].size();
		for(i=0;i<l;i++)
		{y=g[x][i].to;
		 if(dis[y]>dis[x]+g[x][i].wi)
		 {dis[y]=dis[x]+g[x][i].wi;
		  d[y]=d[x]+1;
		  if(!inq[y])
		  {q.push(y);inq[y]=1;
		  }
		 }
		}
	}
	
	for(i=1;i<=n;i++)
	ans=(ans+dis[i])%M;
}
void zhushi()
{
/*struct Line{int k,b;};
vector<Line> vl;

long long int fx(Line l,int x)
{
	return (long long int)l.k*x+l.b;
}

struct Point{long long int x,y;};
vector<Point> pi;

int du[maxn]={0};
int ki[maxn]={0};
void bfs(int s,int t)
{
	int i,x,y,l;
	queue<int> q;
	for(i=1;i<=n;i++)
	du[i]=-1;
	q.push(s);
	
}
*/
}
int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	int i,x,y,w;
	scanf("%d%d%d",&n,&m,&t);
	for(i=0;i<m;i++)
	{scanf("%d%d%d",&x,&y,&w);
	 AddEdge(x,y,w);
	}
	for(i=0;i<=t;i++)
	{spfa(1);
	 init();
	}
	cout<<ans<<endl;
	return 0;
}
