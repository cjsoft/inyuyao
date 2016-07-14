#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

int n,l[26],r[26],kk,maxw;
double f[26][26],ansA,ansB;


int main()
{
	freopen("assign.in","r",stdin);
//	freopen("assign.out","w",stdout);
	scanf("%d",&n);
	maxw=0;
	for(int i=1;i<=n;++i)scanf("%d",l+i);
	for(int i=1;i<=n;++i)scanf("%d",r+i),maxw=max(r[i],maxw);
	scanf("%d",&kk);
	for(int i=1;i<=n;++i)
	{
		ansA=0,ansB=0;
		double mp=1/(double)(r[i]-l[i]+1),p;
		for(int my=l[i];my<=r[i];++my)
		{
			memset(f,0,sizeof(f));
			f[0][0]=1;
			for(int j=1;j<=n;++j)
			{
				if(j==i)for(int l1=0;l1<=n;++l1) f[j][l1]=f[j-1][l1];
				else
				{
					p=1/(double)(r[j]-l[j]+1);
					int mm=my;if(j>i) mm++;
					if(l[j]>=mm) p=1;
					else if(r[j]>=mm) p*=(double)(r[j]-mm+1);
					else p=0;
					for(int l1=0;l1<=n;++l1) f[j][l1]=f[j-1][l1]*(1-p)+l1?f[j-1][l1-1]*p:0;
				}
				
			}
			for(int j=0;j<kk;++j)
			{
				if((j+1)%4<=1) ansA+=mp*f[n][j];
				else ansB+=mp*f[n][j];
			}
		}
		printf("%lf %lf\n",ansA,ansB);
	}
	return 0;
}

