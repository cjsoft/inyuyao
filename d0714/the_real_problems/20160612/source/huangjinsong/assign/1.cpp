#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
#define mp make_pair<int,int>
#define fi first
#define se second
inline int read()
{
	int x=0;bool f=0;char c=getchar();
	for (;c<'0'||c>'9';c=getchar()) f=c=='-'?1:0;
	for (;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	return f?-x:x;
}
int n,k,L[21],R[21],sc[21],my[21];
pii na[21];
double pa[21],pb[21];

void dfs(int d,double p)
{
	if (d<=n) 
	{
		p/=(R[d]-L[d]+1);
		for (int i=L[d];i<=R[d];i++) 
			sc[d]=i,dfs(d+1,p);
	}
	else
	{
		for (int i=1;i<=n;i++) na[i]=mp(-sc[i],i);
		sort(na+1,na+n+1);
		for (int i=1;i<=k;i++) my[i]=na[i].se;
		sort(my+1,my+k+1);
		for (int i=1,j=0;i<=k;i++,j++,j==4?j=0:0)
		{
			if (!j||j==3) pa[my[i]]+=p;
			else pb[my[i]]+=p;
		}
	}
}

int main()
{
	n=read();
	for (int i=1;i<=n;i++) L[i]=read();
	for (int i=1;i<=n;i++) R[i]=read();
	k=read();
	dfs(1,1);
	for (int i=1;i<=n;i++)
		printf("%.6lf %.6lf\n",pa[i],pb[i]);
	return 0;
}
