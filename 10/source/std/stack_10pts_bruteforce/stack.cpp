#include<bits/stdc++.h>
using namespace std;
vector <int> vec[100010];
int main()
{
	freopen("stack.in","r",stdin);
	freopen("stack.out","w",stdout);
	int n,q;
	scanf("%d%d",&n,&q);
	for (int i=1;i<=q;i++)
	{
		int t;scanf("%d",&t);
		if (t==0)
		{
			int l,r,x;scanf("%d%d%d",&l,&r,&x); 
			for (int i=l;i<=r;i++) vec[i].push_back(x);
		}
		else if (t==1)
		{
			int l,r;scanf("%d%d",&l,&r);
			for (int i=l;i<=r;i++) if (vec[i].size()) vec[i].pop_back();
		}
		else
		{
			int x,k;scanf("%d%d",&x,&k);
			if (vec[x].size()<k) {printf("Error\n");continue;}
			printf("%d\n",vec[x][vec[x].size()-k]);
		}
	}
}
