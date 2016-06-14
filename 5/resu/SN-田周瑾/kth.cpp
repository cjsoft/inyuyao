#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<math.h>
using namespace std;
struct node{
	int l;int r;int x;int p;int id;
}q[80005];
int tot,len,n,m,ans[80005],a[80005],b[80005],h[5000005],mapp[80005],num[80005];
int lowbit(int x)
{
	return x&(-x);
}
void add(int x,int v)
{

	for (int i=x;i<=tot;i+=lowbit(i))
	{
		num[i]+=v;
		//cout<<i<<endl;
		//if (i==0)
		//while(1);
	}
	
}
int query(int x)
{
	int cnt=0;
	for (int i=x;i>0;i-=lowbit(i))
	{
		cnt+=num[i];
	}
	return cnt;
}
bool cmp(node aa,node bb)
{
	int ka=aa.l/len;
	int kb=bb.l/len;
	if (ka!=kb)
	return ka<kb;
	else
	return aa.r<bb.r;
}
int main()
{
	freopen("kth.in","r",stdin);
	freopen("kth.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+1+n);
	tot=0;
	for (int i=1;i<=n;i++)
	{
		if (h[a[i]]!=0) continue;
		tot++;
		h[a[i]]=tot;
		mapp[tot]=a[i];
	}
 	scanf("%d",&m);
 	int flag=1;
 	for (int i=1;i<=m;i++)
 	{
		scanf("%d%d%d%d",&q[i].p,&q[i].l,&q[i].r,&q[i].x);
 		q[i].id=i;
		if (q[i].p==1)
 		flag=0;
	}
	if (flag==1)
	{
		len=sqrt(n+1);
		sort(q+1,q+1+m,cmp);
		int nowl=1,nowr=1;
		add(h[a[1]],1);
		for (int i=1,l,r,x;i<=m;i++)
		{
			l=q[i].l,r=q[i].r,x=q[i].x;
			while(nowr<r)
			{
				nowr++;
				add(h[a[nowr]],1);
			}
			while(nowr>r)
			{
				add(h[a[nowr]],-1);
				nowr--;
			}
			while(nowl<l)
			{
				add(h[a[nowl]],-1);
				nowl++;
			}
			while(nowl>l)
			{
				nowl--;
				add(h[a[nowl]],1);
			}
			int fl=1,fr=tot;
			int kkk=-1;
			while(fl<=fr)
			{
				int mid=(fl+fr)/2;
				if (query(mid)<x)
				fl=mid+1;
				else
				{
					kkk=mid;
					fr=mid-1;
				}
			}
			ans[q[i].id]=mapp[kkk];
		}
		for (int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
		return 0;
	}
	else
	{
 		for (int i=1,l,r,p,x;i<=m;i++)
 		{
 			l=q[i].l,r=q[i].r,p=q[i].p,x=q[i].x;
 			if (p==1)
 			for (int j=l;j<=r;j++)
 			a[j]+=x;
 			else
 			{
				for (int j=l;j<=r;j++)
 				b[j-l+1]=a[j];
				sort(b+1,b+1+r-l+1);
				printf("%d\n",b[x]);
			}
		}
	}
}
