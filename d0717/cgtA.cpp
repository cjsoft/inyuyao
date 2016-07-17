#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 1000005
#define mod 998244353
using namespace std;
typedef long long ll;
int ans,now,n,i;
int A[N],a[N],b[N];
int read()
{
	char ch=getchar(),last=' ';int ans=0;
	while (ch<'0' || ch>'9')last=ch,ch=getchar();
	while (ch>='0' && ch<='9')ans=ans*10+ch-'0',ch=getchar();
	if (last=='-')ans=-ans;
	return ans;
}
void work(int l,int r)
{
	if (l>r)return;
	if (l==r)
	{
		A[1]=(A[1]+a[l])%mod;
		A[2]=(A[2]-a[l]+mod)%mod;
		return;
	}
	int mid=(l+r)/2,i,now,pre;
	work(l,mid);work(mid+1,r);
	b[mid]=a[mid];
	for (i=mid-1;i>=l;i--)b[i]=max(b[i+1],a[i]);
	b[mid+1]=a[mid+1];
	for (i=mid+2;i<=r;i++)b[i]=max(b[i-1],a[i]);
	b[r+1]=1e9+10;b[l-1]=1e9+10;
	now=mid+1;
	//printf("l %d r %d\n",l,r);
	for (i=mid;i>=l;i--)
	{
		while (b[now]<=b[i])
			now++;
		A[mid-i+2]=(A[mid-i+2]+b[i])%mod;
		A[now-i+1]=(A[now-i+1]-b[i]+mod)%mod;
	}
	now=mid;
	for (i=mid+1;i<=r;i++)
	{
		while (b[now]<b[i])
			now--;
		A[i-mid+1]=(A[i-mid+1]+b[i])%mod;
		A[i-now+1]=(A[i-now+1]-b[i]+mod)%mod;
	}
}
int main()
{
	freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	n=read();
	for (i=1;i<=n;i++)a[i]=read();
	work(1,n);
	ans=0;now=0;
	for (i=1;i<=n;i++)
	{
		now=((now+A[i])%mod+mod)%mod;
		//printf("%d\n",now);
		ans^=now;
	}
	printf("%d\n",ans);
}