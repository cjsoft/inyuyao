#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <set>
#define maxn 31

using namespace std;

const int dx[8]={1,1,-1,-1,2,2,-2,-2},dy[8]={2,-2,2,-2,1,-1,1,-1};
int n,t;
int ai[maxn][maxn]={0};
set<pair<int,int> > s[2];

int main()
{
	freopen("SKAKAC.in","r",stdin);
	freopen("SKAKAC.out","w",stdout);
	int i,j,tim,x,y,cur=0,xn,yn;
	scanf("%d%d",&n,&t);
	scanf("%d%d",&x,&y);
	s[cur].insert(make_pair(x,y));
	for(i=1;i<=n;i++)
	for(j=1;j<=n;j++)
	scanf("%d",&ai[i][j]);
	set<pair<int,int> >::iterator it;
	for(tim=1;tim<=t;tim++)
	{
		cur^=1;
		s[cur].clear();
		for(it=s[cur^1].begin();it!=s[cur^1].end();it++)
		{
			x=it->first;y=it->second;
			for(i=0;i<8;i++)
			{xn=x+dx[i];
			 yn=y+dy[i];
			 if(xn>=1&&xn<=n&&yn>=1&&yn<=n&&tim%ai[xn][yn]==0&&s[cur].find(make_pair(xn,yn))==s[cur].end())
			 s[cur].insert(make_pair(xn,yn));
			}
		}
		if(s[cur].size()==0)break;
	}
	printf("%d\n",s[cur].size());
	for(it=s[cur].begin();it!=s[cur].end();it++)
	printf("%d %d\n",it->first,it->second);

	return 0;
}
