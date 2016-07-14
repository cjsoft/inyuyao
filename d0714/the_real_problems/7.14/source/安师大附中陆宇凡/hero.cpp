#include<cmath>
#include<stdio.h>
#include<memory.h>
#include<iostream>
using namespace std;
const int oo=2000000000;

//bool zg[90005];
int list[90005],S,T,a1,b1;
int s1[305][305][305],mx,tt;
int a[305][305],s[305][305],h[90005];
int n,m,k,i,j,o,_1,o1,ans,ss;//dep[5400005];

int main()
{
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	scanf("%d %d %d",&n,&m,&k);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
//	if(n<=50)
//	{
		for(i=1;i<=m;i++)
			for(j=1;j<=m;j++)
				if(i!=j)s1[1][i][j]=a[1][i]+a[1][j];
		for(i=2;i<=n;i++)
		{
			for(j=1;j<m;j++)
			{
				for(o=j+1;o<=m;o++)
				{
					if(j==o)continue;
					s1[i][j][o]=oo;//printf("%d %d\n",i,j);
					for(_1=1;_1<m;_1++)
					{
						for(o1=_1+1;o1<=m;o1++)
						{
							if(_1==o1||s1[i-1][_1][o1]>=s1[i][j][o])continue;
							s1[i][j][o]=min(s1[i][j][o],s1[i-1][_1][o1]+k*(abs(_1-j)+abs(o1-o))+a[i][j]+a[i][o]);
						}
					}
	//				printf("%d %d %d %d\n",i,j,o,s1[i][j][o]);
				}
			}
	//		printf("%d\n",s1s1);
		}
		ans=oo;
		for(i=1;i<m;i++)
			for(j=i+1;j<=m;j++)
				if(i!=j)ans=min(ans,s1[n][i][j]);
		printf("%d\n",ans);
		return 0;
//	}
//	else
//	{
//	}
//	return 0;
}
/*
struct node
{
	int v,w,next,t;
}L[5400005];

void jia(int u,int v,int w)
{
	tt++;
	L[tt].v=v,L[tt].w=w,L[tt].next=h[u],h[u]=tt,L[i].t=1;
	tt++;
	L[tt].v=u,L[tt].w=w,L[tt].next=h[v],h[v]=tt,L[i].t=-1;
}

void work(int S,int T)
{
	int tt=1,p,q,i,j,o,sl;
	memset(dep,-1,sizeof(dep));
	memset(zg,false,sizeof(zg));
	list[0]=0;
	list[++list[0]]=S;
	dep[S]=0;
	while(tt<=list[0])
	{
		p=list[tt++];zg[p]=false;
		for(i=h[p];i;i=L[i].next)
		{
			if(L[i].t==-1)continue;
			q=L[i].v;
			if(zg[q])continue;
			if(dep[q]==-1||dep[p]+L[i].w<dep[q])
			{
				if(!zg[q])
				{
					zg[q]=true;
					list[++list[0]]=q;
				}
				dep[q]=dep[p]+L[i].w;
			}
		}
	}
//	sl=ss=dep[0];o=n+1;j=0;printf("%d ",ss);
	while(o--)
	{
		for(i=h[j];i;i=L[i].next)
		{
			if(L[i].t==1)continue;
			if(dep[L[i].v]==sl)
			{
				j=L[i].v,sl-=L[i].w,printf("%d ",j),zg[j]=true;break;
			}
		}
	}
	list[++list[0]]=0;
	while(tt<=list[0])
	{
		p=list[tt++];zg[p]=false;
		for(i=h[p];i;i=L[i].next)
		{
			if(L[i].t==1)continue;
			q=L[i].v;
			if(zg[q])continue;
			if(dep[q]==-1||dep[p]+L[i].w<dep[q])
			{
				if(!zg[q])
				{
					zg[q]=true;
					list[++list[0]]=q;
				}
				dep[q]=dep[p]+L[i].w;
			}
		}
	}
	ss=dep[T];
	printf("%d\n",ss);
}

//		S=n*m+1,T=n*m+2;
//		jia(S,0,2,0);
//		for(i=1;i<m;i++)
		for(j=1;j<=m;j++)
		{
			jia(j,0,0);
		}
		for(i=2;i<=n;i++)
		{
			for(j=1;j<=m;j++)
			{
				for(o=1;o<=m;o++)
				{
					a1=(i-2)*m+o,b1=(i-1)*m+j;
					jia(b1,a1,a[i][j]+k*abs(o-j));
				}
//				printf("%d %d\n",i,j);
			}
		}
//		printf("1\n");
		ans=oo;
		for(i=1;i<m;i++)
		{
			for(j=i+1;j<=m;j++)
			{
				a1=(n-1)*m+i,b1=(n-1)*m+j;
				work(a1,b1);ans=min(ans,ss);
			}
		}
//		qiu(S,T);
		printf("%d\n",ans);
	for(i=1;i<=m;i++)s[1][i]=a[1][i];
	for(i=2;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			s[i][j]=oo;
			for(o=1;o<=m;o++)
				s[i][j]=min(s[i][j],s[i-1][o]+k*abs(o-j)+a[i][j]);
		}
	}ss=oo;j=0;
	for(i=1;i<=m;i++)
		if(s[n][i]<ss)ss=s[n][i],j=i;
	list1[n]=j,o=n-1;ans+=ss;printf("%d\n",ss);
	while(o)
	{
		for(i=1;i<=m;i++)
			if((s[o][i]+k*abs(i-j)+a[o+1][j])==ss)
			{
				ss=s[o][i],j=i;break;
			}
		list1[o]=j;
		o--;
	}
	for(i=1;i<=n;i++)printf("%d\n",list1[i]);
	memset(s,0,sizeof(s));
	for(i=1;i<=m;i++)
		if(i!=list1[1])s[1][i]=a[1][i];
	for(i=2;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			if(j==list1[i])continue;
			s[i][j]=oo;
			for(o=1;o<=m;o++)
			{
				if(o==list1[i-1])continue;
				s[i][j]=min(s[i][j],s[i-1][o]+k*abs(o-j)+a[i][j]);
			}
		}
	}ss=oo;
	for(i=1;i<=m;i++)
	{
		if(i==list1[n])continue;
		ss=min(ss,s[n][i]);
	}ans+=ss;printf("%d\n",ss);
	printf("%d\n",ans);	
	printf("1\n");*/
