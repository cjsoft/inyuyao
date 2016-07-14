#include<bits/stdc++.h>
using namespace std;
int read()
{
	int s=0,f=1;char ch=getchar();
	while(!('0'<=ch&&ch<='9')){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){s=(s<<3)+(s<<1)+ch-'0';ch=getchar();}
	return s*f;
}
int n,m,K;
int t[305][305];
int f[305][305],ans=2000000000;
int s[4][305][305];//1,1  1,-1  -1,1  -1,-1
int main()
{
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	n=read(),m=read(),K=read();
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=m;j++)
	        t[i][j]=read();
	for(int i=1;i<=m;i++)
		for(int j=i+1;j<=m;j++)
		    f[i][j]=t[1][i]+t[1][j];
	for(int i=2;i<=n;i++)
	   {for(int j=0;j<=m+1;j++)
	        for(int k=0;k<=m+1;k++)
	            s[0][j][k]=s[1][j][k]=s[2][j][k]=s[3][j][k]=2000000000;
	    for(int j=m;j>=1;j--)
	        for(int k=m;k>=j+1;k--)
	    		s[0][j][k]=min(min(s[0][j+1][k],s[0][j][k+1]),f[j][k]+(j+k)*K);
	    		
	    for(int j=m;j>=1;j--)
	        for(int k=j+1;k<=m;k++)
	    		s[1][j][k]=min(min(s[1][j+1][k],s[1][j][k-1]),f[j][k]+(j-k)*K);
	    		
	    for(int j=1;j<=m;j++)
	        for(int k=m;k>=j+1;k--)
	    		s[2][j][k]=min(min(s[2][j-1][k],s[2][j][k+1]),f[j][k]+(-j+k)*K);
	    		
	    for(int j=1;j<=m;j++)
	        for(int k=j+1;k<=m;k++)
	    		s[3][j][k]=min(min(s[3][j-1][k],s[3][j][k-1]),f[j][k]+(-j-k)*K);
	    		
	    for(int j=1;j<=m;j++)
	        for(int k=j+1;k<=m;k++)
	           {
	           	swap(f[j][k],f[j][k]);
	            f[j][k]=min(min(s[0][j][k]+(-j-k)*K
	            					,s[1][j][k]+(-j+k)*K
								  ),min(s[2][j][k]+(j-k)*K
							   	    ,s[3][j][k]+(j+k)*K
							   ));
				f[j][k]+=t[i][j]+t[i][k];
			}
		
	   }
	for(int j=1;j<=m;j++)
	    for(int k=j+1;k<=m;k++)
			ans=min(ans,f[j][k]);
	cout<<ans<<endl;//cout<<clock()<<endl;
	return 0;
}
