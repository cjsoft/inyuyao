#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>


using namespace std;

const int inf=0x3fffffff;
int n,m,k;

struct E{
	int to,next,w,c;
}e[300*300*10];int heade[310*310],tope=1;
void adde(int u,int v,int w,int c)
{
//	cout<<u<<" "<<v<<" "<<w<<endl;
	++tope;e[tope].to=v;e[tope].next=heade[u];e[tope].w=w;e[tope].c=c;heade[u]=tope;
	++tope;e[tope].to=u;e[tope].next=heade[v];e[tope].w=-w;e[tope].c=0;heade[v]=tope;
}
int id(int i,int j,int k)
{
	return (i-1)*m+j+k*(n*m);
}
int s,t;
int a[305];

bool di[310*310];
int dis[310*310],pre[310*310];
queue<int>que;
bool spfa()
{
	que.push(s);
	for(int i=1;i<=s;++i) dis[i]=inf;
	dis[s]=0;di[s]=1;
	int wz;
	while(!que.empty())
	{
		wz=que.front();que.pop();di[wz]=0;
		for(int i=heade[wz];i;i=e[i].next)
			if(e[i].c&&dis[wz]+e[i].w<dis[e[i].to])
			{
				dis[e[i].to]=dis[wz]+e[i].w;pre[e[i].to]=i;
				if(di[e[i].to]==0) 
					que.push(e[i].to),di[e[i].to]=1;
			}
			
	}
	return dis[t]!=inf;
}
int ans=0;
void gx()
{
	int f=inf;
	for(int wz=t;wz!=s;wz=e[pre[wz]^1].to)
		f=min(e[pre[wz]].c,f);
	for(int wz=t;wz!=s;wz=e[pre[wz]^1].to)
	{
		e[pre[wz]].c-=f;e[pre[wz]^1].c+=f;
		ans+=f*e[pre[wz]].w;
	}
}

int main()
{
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	int ss=n*m*2+1;t=ss+1,s=t+1;
	adde(s,ss,0,2);
	for(int j=1;j<=m;++j)
		scanf("%d",&a[j]),
		adde(ss,id(1,j,0),a[j],1);
	int t1,t2,w1,w2,w3;
	for(int i=2;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
			scanf("%d",&a[j]);
		for(int l1=1;l1<=m;++l1)
		{
			w1=inf;w2=inf;
			for(int j=1;j<=m;++j)
			{
				w3=a[j]+k*abs(j-l1);
				if(w3<w2) w1=w2,w2=w3,t1=t2,t2=j;
				else if(w3<w1) w1=w3,t1=j;
			}
			adde(id(i-1,l1,1),id(i,t1,0),w1,1);
			adde(id(i-1,l1,1),id(i,t2,0),w2,1);
		}
	}
	for(int j=1;j<=m;++j)
		adde(id(n,j,1),t,0,1);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			adde(id(i,j,0),id(i,j,1),0,1);
	while(spfa()) 
	gx();
	printf("%d",ans);
	return 0;
}
