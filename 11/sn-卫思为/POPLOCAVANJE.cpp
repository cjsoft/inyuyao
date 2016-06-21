#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#define maxn 300010

using namespace std;

int a[maxn],x[maxn],y[maxn];
int sa[maxn],rank[maxn],height[maxn];

void getsa(char s[],int l)
{
	int i,m=128;
	int k,p;
	
	for(i=0;i<=m;i++)a[i]=0;
	for(i=0;i<l;i++)a[x[i]=s[i]-'a'+1]++;
	for(i=1;i<=m;i++)a[i]+=a[i-1];
	for(i=l-1;i>=0;i--)sa[--a[x[i]]]=i;
	
	for(k=1;k<l;k++)
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
		if(rank[i]==0){height[rank[i]]=k=0;break;}
		if(k)k--;
		j=sa[rank[i]-1];
		while(i+k<l&&j+k<l&&s[i+k]==s[j+k])k++;
		height[rank[i]]=k;
	}
}

int match(char *n,int ln,char m[],int lm)
{
	int i;
	for(i=0;i<lm;i++)
	if(*(n+i)>m[i])return 1;
	else if(*(n+i)<m[i])return 2;
	return 3;
}

int st[maxn]={0};
int n,m;
char s[maxn]={0};

void work(char s1[],int len)
{
	int l=0,r=n-1,m;
	if(match(&s[sa[l]],n-sa[l],s1,len)==1)return;
	if(match(&s[sa[r]],n-sa[r],s1,len)==2)return;
	
	while(l!=r&&l!=r-1)
	{m=(l+r)>>1;
	 if(match(&s[sa[m]],n-sa[m],s1,len)!=2)r=m;
	 else l=m;
	}
	int x=-1;
	//if(match(&s[sa[m]],n-sa[m],s1,len)==3)x=m;
    if(match(&s[sa[r]],n-sa[r],s1,len)==3)x=r;
	else return;
//	cout<<x<<" ";
	if(st[sa[x]]>=len)return;
	st[sa[x]]=len;
	int i=x,j=x+1;
	while(i>0&&height[i]>=len)
	{	if(st[sa[i-1]]>=len)break;
		st[sa[i-1]]=len;
		i--;
	}
	while(j<n&&height[j]>=len)
	{	if(st[sa[j]]>=len)break;
		st[sa[j]]=len;
		j++;
	}
}

bool flag[maxn]={0};
char s1[maxn];

int main()
{
	freopen("POPLOCAVANJE.in","r",stdin);
	freopen("POPLOCAVANJE.out","w",stdout);
	int i,j;
	scanf("%d",&n);
	scanf("%s",&s);
	getsa(s,n);
	gethei(s,n);
	
	scanf("%d",&m);
	while(m--)
	{scanf("%s",s1);
	 work(s1,strlen(s1));
	}

	i=0;j=0;
	for(i=0;i<n;i++)
	{
		for(j=max(j,i);j<=i+st[i]-1;j++)
		flag[j]=1;
	}
	int ans=0;
	for(i=0;i<n;i++)
	if(!flag[i])ans++;
	
	printf("%d\n",ans);
	
	return 0;
}
