#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<math.h>
using namespace std;
string ss[2005];
char s[2005][2005];
char t[2005];
int ht[2005];
int main()
{
	freopen("sub.in","r",stdin);
	freopen("sub.out","w",stdout);
	scanf("%s",t);
	int len=strlen(t);
	for (int i=len-1;i>=0;i--)
	{
		for (int j=i,k=0;j<len;j++,k++)
		s[i][k]=t[j];
	}
	for (int i=0;i<len;i++)
	ss[i]=(string)s[i];
	sort(ss,ss+len);	
	for (int i=0;i<=len-2;i++)
	{
		int j=0;
		int tmp1=ss[i].size();
		int tmp2=ss[i+1].size();
		while(j<tmp1&&j<tmp2&&ss[i][j]==ss[i+1][j])j++;
		ht[i]=j;
	}
	int ans=0;
	//for (int i=0;i<len;i++)
	//cout<<ht[i]<<endl;
	for (int l=1;l<=len;l++)
	{
		int hhh=9999;
		int tot=1;
		for (int i=0;i<=len-2;i++)
		{
			hhh=min(hhh,ht[i]);
			if (hhh>=l)
			tot++;
			else
			{
				hhh=9999;
				if (tot>1)
				ans=max(ans,tot*l);
				tot=1;
			}
		}
		if (tot>1)
		ans=max(ans,tot*l);
	}
	printf("%d\n",ans);
}
