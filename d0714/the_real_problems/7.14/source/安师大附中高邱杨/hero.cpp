#include <bits/stdc++.h>
using namespace std;

const int N=305;
const int M=N*N;
int n,m,k,s,t,ans;
int a[N][N];
int in[N],out[N];
bool orz[N][N];
char c[M][N][2];
queue<int> Qx,Qy;
queue<bool> Qz;
bool inQ[N][N][2];
int dis[N][N][2];
int lasx[N][N][2];
int lasy[N][N][2];
bool lasz[N][N][2];

int id(int x,int y)
{
	return (x-1)*n+y;
}

void add(int i1,int j1,int i2,int j2,int C,int W)
{
	int s=id(i1,j1),t=id(i2,j2);
	c[s][j2][0]=C;
	c[t][j1][1]=0;
}

void spfa()
{
	memset(inQ,0,sizeof(inQ));
	memset(dis,127,sizeof(dis));
	int i,x,y,z,xx,yy,zz,st;
	x=0;y=0;z=0;
	Qx.push(x);Qy.push(y);Qz.push(z);
	inQ[x][y][z]=1;
	dis[x][y][z]=0;
	while(!Qx.empty())
	{
		x=Qx.front();Qx.pop();
		y=Qy.front();Qy.pop();
		z=Qz.front();Qz.pop();
		inQ[x][y][z]=0;
		if(x==0&&y==0&&z==0)
		{
			for(i=1;i<=m;i++)
			    if(in[i])
			    {
			    	xx=1;yy=i;zz=0;
			    	dis[xx][yy][zz]=0;
			    	lasx[xx][yy][zz]=x;
			    	lasy[xx][yy][zz]=y;
			    	lasz[xx][yy][zz]=z;
			    	if(!inQ[xx][yy][zz])
			    	{
			    		inQ[xx][yy][zz]=1;
			    		Qx.push(xx);Qy.push(yy);Qz.push(zz);
			    	}
			    }
		}
		else if(x==n&&z==1)
		{
			if(out[y])
			{
			    xx=0;yy=1;zz=0;
			    if(dis[x][y][z]<dis[xx][yy][zz])
			    {
    			    dis[xx][yy][zz]=dis[x][y][z];
			    	lasx[xx][yy][zz]=x;
			    	lasy[xx][yy][zz]=y;
			    	lasz[xx][yy][zz]=z;
	    		}
			}
		}
		else if(z==0)
		{
			if(orz[x][y])
			{
				xx=x;yy=y;zz=1;
				if(dis[x][y][z]+a[x][y]<dis[xx][yy][zz])
			    {
			    	lasx[xx][yy][zz]=x;
			    	lasy[xx][yy][zz]=y;
			    	lasz[xx][yy][zz]=z;
			    	dis[xx][yy][zz]=dis[x][y][z]+a[x][y];
			    	if(!inQ[xx][yy][zz])
			    	{
				    	inQ[xx][yy][zz]=1;
				    	Qx.push(xx);Qy.push(yy);Qz.push(zz);
				    }
			    }
		    }
		    if(x>1)
		    {
			    st=id(x,y);
				xx=x-1;zz=1;
				for(yy=1;yy<=m;yy++)
				    if(dis[x][y][z]-abs(y-yy)*k<dis[xx][yy][zz]&&c[st][yy][1])
				    {
				    	dis[xx][yy][zz]=dis[x][y][z]-abs(y-yy)*k;
			    		lasx[xx][yy][zz]=x;
			    		lasy[xx][yy][zz]=y;
			    		lasz[xx][yy][zz]=z;
			    		if(!inQ[xx][yy][zz])
			    		{
				    		inQ[xx][yy][zz]=1;
				    		Qx.push(xx);Qy.push(yy);Qz.push(zz);
					    }
				    }
			}
		}
		else
		{
			st=id(x,y);
			xx=x+1;zz=0;
			for(yy=1;yy<=m;yy++)
			    if(dis[x][y][z]+abs(y-yy)*k<dis[xx][yy][zz]&&c[st][yy][0])
			    {
			    	dis[xx][yy][zz]=dis[x][y][z]+abs(y-yy)*k;
			    	lasx[xx][yy][zz]=x;
			    	lasy[xx][yy][zz]=y;
			    	lasz[xx][yy][zz]=z;
			    	if(!inQ[xx][yy][zz])
			    	{
				    	inQ[xx][yy][zz]=1;
				    	Qx.push(xx);Qy.push(yy);Qz.push(zz);
				    }
			    }
		}
	}
}

void adjust()
{
	int x,y,xx,yy,st,ed;
	bool z,zz;
	x=0;y=1;z=0;
	while(!(x==0&&y==0&&z==0))
	{
		xx=lasx[x][y][z];
		yy=lasy[x][y][z];
		zz=lasz[x][y][z];
		
		
		if(x==0&&y==1)
		    out[yy]=0;
		else if(xx==0&&yy==0)
		    in[y]=0;
		else if(zz==0)
		{
			if(xx-1==x)
			{
			    st=id(xx,yy);
    			ans-=abs(y-yy)*k;
    			c[st][y][1]--;
    			c[ed][yy][0]++;
			}
			else
    		    orz[x][y]=0,ans+=a[x][y];
		}
		else
		{
			st=id(xx,yy);
			ed=id(x,y);
			if(xx+1==x)
			{
    			ans+=abs(y-yy)*k;
    			c[st][y][0]--;
    			c[ed][yy][1]++;
    		}
		}
		x=xx;
		y=yy;
		z=zz;
	}
}

int main()
{
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	int i,j,l;
	for(i=1;i<=n;i++)
	    for(j=1;j<=m;j++)
	        scanf("%d",&a[i][j]);
	s=n*m*2+1;t=n*m*2+2;
	for(i=1;i<=m;i++)
		in[i]=out[i]=1;
	for(i=1;i<=n;i++)
	    for(j=1;j<=m;j++)
	    {
	    	orz[i][j]=1;
	    	if(i<n)
    	        for(l=1;l<=m;l++)
	                add(i,j,i+1,l,1,abs(j-l)*k);
	    }
	spfa();adjust();
	spfa();adjust();
	printf("%d\n",ans);
	return 0;
}

