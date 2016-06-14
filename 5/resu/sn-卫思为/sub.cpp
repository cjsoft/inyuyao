#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#define maxn 1000010

using namespace std;

int sa[maxn]={0},rank[maxn]={0},height[maxn]={0};
int a[maxn]={0},x[maxn]={0},y[maxn]={0};

void getsa(char s[],int l)
{
	int i,m=128;
	int k,p;
	for(i=0;i<=m;i++)a[i]=0;
	for(i=0;i<l;i++)a[x[i]=s[i]-'a'+1]++;
	for(i=1;i<=m;i++)a[i]+=a[i-1];
	for(i=l-1;i>=0;i--)sa[--a[x[i]]]=i;
	
	for(k=1;k<l;k<<=1)
	{
		p=0;
		for(i=l-k;i<l;i++)y[p++]=i;
		for(i=0;i<l;i++)if(sa[i]>=k)y[p++]=sa[i]-k;
		
		for(i=0;i<=m;i++)a[i]=0;
		for(i=0;i<l;i++)a[x[y[i]]]++;
		for(i=1;i<=m;i++)a[i]+=a[i-1];
		for(i=l-1;i>=0;i--)sa[--a[x[y[i]]]]=y[i];
		
		for(i=0;i<l;i++)y[i]=x[i];
		
		p=1;
		for(i=0;i<l-1;i++)
		{x[sa[i]]=p;
		 if(y[sa[i]]!=y[sa[i+1]]||y[sa[i]+k]!=y[sa[i+1]+k])p++;
		}
		x[sa[l-1]]=p;
		if(p==l)break;
		m=p+1;
	}
	
	for(i=0;i<l;i++)
	rank[sa[i]]=i;
}

void gethei(char s[],int l)
{
	int i,j,k=0;
	for(i=0;i<l;i++)
	{
		if(rank[i]==0){height[rank[i]]=k=0;continue;}
		if(k)k--;
		j=sa[rank[i]-1];
		while(i+k<l&&j+k<l&&s[i+k]==s[j+k])k++;
		height[rank[i]]=k;
	}
}

char s[maxn]={0};
int d[maxn]={0};

int main()
{
	freopen("sub.in","r",stdin);
	freopen("sub.out","w",stdout);
	
	scanf("%s",s);
	int i,j,l=strlen(s);
	getsa(s,l);
	gethei(s,l);
	
	long long int ans=0;
	for(i=l-1;i>=1;i--)
	{if(i==l-1){d[i]=l-1;continue;}
	 j=i+1;
	 while(height[i]<=height[j]&&j<l)j=d[j]+1;
	 d[i]=j-1;
	}
	
	for(i=1;i<l;i++)
	if(ans<(long long int)(height[i])*(d[i]-i+2))ans=(long long int)(height[i])*(d[i]-i+2);
	
	cout<<ans<<endl;
	
	return 0;
}
