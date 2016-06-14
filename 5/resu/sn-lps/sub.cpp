#include<iostream>
#include<string.h>
#include<stdio.h>
#include<algorithm>
using namespace std;
char s[10005];
int len;
int nex[10005];
int cnt[10005];
int fa[10005];
long long ans=0;
void get_nex(int x)
{
	int j=x-1;
	for(int i=x;i<len;i++)
	{
		cnt[i]=0;
		while(j!=x-1&&s[i]!=s[j+1]) j=nex[j];
		if(i!=x&&s[i]==s[j+1]) j++;
		nex[i]=j;
		int now=j;
		while(now!=x-1)
		{
			cnt[now]++;
			now=nex[now];	
		}
	}
	for(int i=x;i<len;i++)
	if(cnt[i]!=0)
	ans=max(ans,(long long )(cnt[i]+1)*(i+1-x));
}
int main()
{
	freopen("sub.in","r",stdin);
	freopen("sub.out","w",stdout);
	scanf("%s",s);
	len=strlen(s);
	for(int i=0;i<len-1;i++)
	get_nex(i);	
//	cout<<cnt[2]<<endl;
	cout<<ans<<endl;
	
}
