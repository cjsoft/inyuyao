#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#define maxn 1010

using namespace std;

int n;
int ai[maxn][maxn]={0};
bool used[maxn]={0};
int flag[maxn]={0};

vector<int> ss[2];
int s[2]={0};
int s1=0;

bool dfs(int x,int fl)
{
	if(used[x]&&flag[x]!=fl)return false;
	if(used[x]&&flag[x]==fl)return true;
	int i;
	used[x]=1;
	flag[x]=fl;
	s[fl]++;
	for(i=1;i<=n;i++)
	if(ai[x][i]&&!dfs(i,fl^1))return false;
	return true;
}

vector<int> ve;
bool get[maxn]={0};

void dodp()
{
	int i,j;
	for(i=1;i<=n;i++)
	get[i]=0;
	
	get[ss[0][0]]=get[ss[1][0]]=1;
	
	for(i=1;i<ss[0].size();i++)
	{
		ve.clear();
		for(j=1;j<=n;j++)
		if(get[j]){ve.push_back(j);get[j]=0;}
		for(j=0;j<ve.size();j++)
		{get[ss[0][i]+ve[j]]=get[ss[1][i]+ve[j]]=1;
		}
	}
	
	i=n/2;j=(n+1)/2;
	while(1)
	{
		if(get[i]){printf("%d\n",2*i*(n-i)-s1);return;}
		if(get[j]){printf("%d\n",2*j*(n-j)-s1);return;}
		i--;j++;
	}
}

void work()
{   
	int i;

	ss[0].clear();
	ss[1].clear();
	for(i=1;i<=n;i++)
	used[i]=0;
	
	for(i=1;i<=n;i++)
	if(!used[i])
	{s[0]=s[1]=0;
	 if(!dfs(i,0)){printf("-1\n");return;}
	 ss[0].push_back(s[0]);
	 ss[1].push_back(s[1]);
	}
	dodp();
}

int t;
int main()
{
	freopen("fxxk.in","r",stdin);
	freopen("fxxk.out","w",stdout);
	int i,j;
	scanf("%d",&t);
	while(t--)
	{
	scanf("%d",&n);
	s1=0;
	for(i=1;i<=n;i++)
	for(j=1;j<=n;j++)
	{scanf("%d",&ai[i][j]);
	 if(ai[i][j])s1++;
	}
	work();
	}
	return 0;
}
