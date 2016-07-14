#include<bits/stdc++.h>
using namespace std;
int l[99],r[99],i,j,k,w,n,m,t;
double f[99][99],g[99][99],u[99],v[99],h;
main()
{
	for(freopen("assign.in","r",stdin),freopen("assign.out","w",stdout),cin>>n,i=1;i<=n;i++)cin>>l[i];
	for(i=1;i<=n;i++)cin>>r[i];
	for(cin>>m,w=0;w<1001;w++)for(t=1;t<=n;t++)
	{
		memset(f,0,sizeof(f));memset(g,0,sizeof(g));
		for(f[0][0]=g[0][0]=i=1;i<=n;i++)for(j=i;~j;j--)
		{
			if(i==t)f[i][j+1]+=f[i-1][j]*(l[i]<=w&&w<=r[i])/(r[i]-l[i]+1);
			else
			{
				if(i<t)h=min(1.,1.*max(0,r[i]-w+1)/(r[i]-l[i]+1));else h=min(1.,1.*max(0,r[i]-w)/(r[i]-l[i]+1));
				f[i][j+1]+=h*f[i-1][j];f[i][j]+=(1-h)*f[i-1][j];
			}
			if(k=n-i+1,k==t)g[i][j+1]+=g[i-1][j]*(l[k]<=w&&w<=r[k])/(r[k]-l[k]+1);
			else
			{
				if(k<t)h=min(1.,1.*max(0,r[k]-w+1)/(r[k]-l[k]+1));else h=min(1.,1.*max(0,r[k]-w)/(r[k]-l[k]+1));
				g[i][j+1]+=h*g[i-1][j];g[i][j]+=(1-h)*g[i-1][j];
			}
		}
		for(i=1;i<=n;i++)for(j=0;j<m;j++)
		{
			if(i==t)h=1.*(l[i]<=w&&w<=r[i])/(r[i]-l[i]+1);
			else if(i<t)h=min(1.,1.*max(0,r[i]-w+1)/(r[i]-l[i]+1));else h=min(1.,1.*max(0,r[i]-w)/(r[i]-l[i]+1));
			if(j%4&&j%4<3)v[i]+=h*f[i-1][j]*g[n-i][m-j-1];else u[i]+=h*f[i-1][j]*g[n-i][m-j-1];
		}
	}
	for(i=1;i<=n;i++)printf("%.6lf %.6lf\n",u[i],v[i]);
}//23333
