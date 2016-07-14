#include <algorithm>
#include <cstdio>
#include <vector>
const int N=26;
int n,m,ans,L[N],R[N],a[N],c[N],A[N],B[N];
std::pair<int,int> b[N];
void Dfs(int x)
{
	if(x>n)
	{
		for(int i=1;i<=n;i++)
			b[i]=std::make_pair(a[i],-i);
		std::sort(b+1,b+n+1);
		for(int i=1;i<=n;i++)
			c[-b[i].second]=(n-i<m);
		for(int i=1,j=0;i<=n;i++)
			if(c[i])
			{
				if((++j)%4<=1) A[i]++;
				else B[i]++;
			}
		ans++;
		return;
	}
	for(int i=L[x];i<=R[x];i++)
	{
		a[x]=i;Dfs(x+1);
	}
}
int main()
{
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&L[i]);
	for(int i=1;i<=n;i++) scanf("%d",&R[i]);
	scanf("%d",&m);
	Dfs(1);
	for(int i=1;i<=n;i++)
		printf("%.6lf %.6lf\n",(double)A[i]/ans,(double)B[i]/ans);
}
