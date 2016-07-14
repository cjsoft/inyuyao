#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
using namespace std;
const int dx[]={-1,0,0,1},dy[]={0,-1,1,0};
int a[305][305],d[305][305],qx[90005],qy[90005];
bool b[305][305];
int main()
{
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	register int i,j,k,l,n,m,K,he,ta;
	scanf("%d%d%d",&n,&m,&K);
	for(i=1;i<=n;i++)for(j=1;j<=m;j++)scanf("%d",a[i]+j);
	for(i=1;i<=n;i++)
	{
		for(j=1,he=ta=0;j<=m;j++)for(k=1;k<j;k++)
		{
			qx[ta]=j;
			qy[ta++]=k;
			b[j][k]=1;
		}
		while(he!=ta)
		{
			j=qx[he];
			k=qy[he++];
			b[j][k]=0;
			if(he==90005)he=0;
			for(l=0;l<4;l++)if(j+dx[l]>k+dy[l]&&d[j+dx[l]][k+dy[l]]>d[j][k]+K)
			{
				d[j+dx[l]][k+dy[l]]=d[j][k]+K;
				if(!b[j+dx[l]][k+dy[l]])
				{
					b[j+dx[l]][k+dy[l]]=1;
					qx[ta]=j+dx[l];
					qy[ta++]=k+dy[l];
					if(ta==90005)ta=0;
				}
			}
		}
		for(j=1;j<=m;j++)for(k=1;k<j;k++)d[j][k]+=a[i][j]+a[i][k];
	}
	for(i=1,k=1000000000;i<=m;i++)for(j=1;j<i;j++)k=min(k,d[i][j]);
	cout<<k<<endl;
	return 0;
}

