#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
using namespace std;
int n,m,l[30],r[30];
double x[30],y[30],f[30][30],g[30][30],a[30],b[30];
int main()
{
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	int i,j,k,u;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	  scanf("%d",&l[i]);
	for(i=1;i<=n;i++)
	  scanf("%d",&r[i]);
	scanf("%d",&m);
	for(k=1;k<=n;k++)
	  for(u=l[k];u<=r[k];u++)
	    {
	     for(i=1;i<=n;i++)
	       {
	       	if(u<l[i])
	       	  x[i]=1;
	       	else if(u>r[i])
	       	  x[i]=0;
	       	else
	       	  x[i]=double(r[i]-u+(i<k))/(r[i]-l[i]+1);
	       	y[i]=1-x[i];
	       }
	     x[k]=double(1)/(r[k]-l[k]+1);
	     y[k]=0;
	     f[0][0]=1;
	     for(i=1;i<=n;i++)
	       {
	       	f[i][0]=f[i-1][0]*y[i];
	        for(j=1;j<=i && j<=m;j++)
	          f[i][j]=f[i-1][j]*y[i]+f[i-1][j-1]*x[i];
	       }
	     g[n+1][0]=1;
	     for(i=n;i>0;i--)
	       {
	       	g[i][0]=g[i+1][0]*y[i];
	       	for(j=1;j<=n-i+1 && j<=m;j++)
	       	  g[i][j]=g[i+1][j]*y[i]+g[i+1][j-1]*x[i];
	       }
	     for(i=1;i<=n;i++)
	       for(j=0;j<m;j++)
	         if((j&3)==0 || (j&3)==3)
	           a[i]+=f[i-1][j]*g[i+1][m-1-j]*x[i];
	         else
	           b[i]+=f[i-1][j]*g[i+1][m-1-j]*x[i];
	    }
	for(i=1;i<=n;i++)
	  printf("%.6lf %.6lf\n",a[i],b[i]);
	return 0;
}

