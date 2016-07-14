#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
typedef long long LL;
inline int read()
{
	int x=0;bool f=0;char c=getchar();
	for (;c<'0'||c>'9';c=getchar()) f=c=='-'?1:0;
	for (;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	return f?-x:x;
}
int n,m,k,t[21][21];
LL ans=(LL)1e18;

void dfs(int d,int a,int b,LL rec)
{
	rec+=t[d][a]+t[d][b];
	if (d==n) {ans=min(ans,rec);return;}
	for (int i=1;i<=m;i++)
		for (int j=1;j<=m;j++) if (i!=j) 
		{
			LL na=k*(abs(i-a)+abs(j-b));
			dfs(d+1,i,j,rec+na);
		}
} 

int main()
{
	n=read();m=read();k=read();
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) t[i][j]=read();
	for (int i=1;i<=m;i++)
		for (int j=1;j<=m;j++)
			if (j!=i) dfs(1,i,j,0);
	cout<<ans<<endl;
}
