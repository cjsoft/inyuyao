#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 1000005;
int len,cnt[maxn],sa[maxn],wv[maxn],wa[maxn],wb[maxn];
int Rank[maxn],height[maxn];
int sta[maxn],top,ans;
char s[maxn];
void DA(char *r,int n,int m)
{
	int *x=wa,*y=wb,p;
	for(int i = 0; i < m; i++) cnt[i]=0;
	for(int i = 0; i < n; i++) cnt[x[i]=r[i]]++;
	for(int i = 1; i < m; i++) cnt[i]+=cnt[i-1];
	for(int i = n-1; i >= 0; i--) sa[--cnt[x[i]]]=i;
	//cout<<"test"<<endl;
	for(int j = 1; j < n; j<<=1)
	{
		p=0;
		for(int i = n-j; i < n; i++) y[p++]=i;
		for(int i = 0; i < n; i++) if(sa[i]>=j) y[p++]=sa[i]-j;
		for(int i = 0; i < n; i++) wv[i]=x[y[i]];
		for(int i = 0; i < m; i++) cnt[i]=0;
		for(int i = 0; i < n; i++) cnt[wv[i]]++;
		for(int i = 1; i < m; i++) cnt[i]+=cnt[i-1];
		for(int i = n-1; i >= 0; i--) sa[--cnt[wv[i]]]=y[i];
		swap(x,y);
		p=1;
		x[sa[0]]=0;
		for(int i = 1; i < n; i++)
			x[sa[i]]=((y[sa[i]]==y[sa[i-1]]) && (y[sa[i]+j]==y[sa[i-1]+j]))?p-1:p++;
		if(p>=n)break;
		m=p;
		//cout<<j<<endl;
	}
}
void calheight(char *r,int n)
{
	for(int i = 1; i <= n; i++) Rank[sa[i]]=i;
	int j=0,k=0;
	for(int i = 0; i < n; height[Rank[i]]=k,i++)
		for(k?k--:k=0,j=sa[Rank[i]-1];r[i+k]==r[j+k];k++);
}
int main(void)
{
	freopen("sub.in","r",stdin);
	freopen("sub.out","w",stdout);
	scanf("%s",s);
	len = strlen(s);
	for(int i = 0; i < len; i++)
		s[i]=s[i]-'a'+1;
	DA(s,len+1,30);
	calheight(s,len);
	for(int i = 2; i <= len; i++)
	{
		int t=2,h=height[i];
		while(top && sta[top]<=h)
		{
			h=min(h,sta[top]),t++;
			ans=max(ans,h*t);
			top--;
		}
		if(height[i])sta[++top]=height[i],ans=max(ans,(top+1)*height[i]);
		else top=0;
	}
	printf("%d\n",ans);
	return 0;
}
