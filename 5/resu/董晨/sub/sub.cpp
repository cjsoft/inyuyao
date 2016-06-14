#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define N 1000005
#define ll long long
int n,m,k,t,x,y,l;
char st[N];
int r[N],wa[N],wb[N],wv[N],ws[N],height[N],sa[N],rank[N];
int q[N],L[N],R[N];
ll ans;
bool cmp(int *r,int a,int b,int l){
	return r[a]==r[b]&&r[a+l]==r[b+l];
}
void da(int *r,int *sa,int n,int m){
	int i,j,p,*x=wa,*y=wb,*t;
	for (i=0;i<m;i++)ws[i]=0;
	for (i=0;i<n;i++)ws[x[i]=r[i]]++;
	for (i=1;i<m;i++)ws[i]+=ws[i-1];
	for (i=n-1;i>=0;i--)sa[--ws[x[i]]]=i;
	for (j=1;p<n;j*=2,m=p){
		for (p=0,i=n-j;i<n;i++)y[p++]=i;
		for (i=0;i<n;i++)if(sa[i]>=j)y[p++]=sa[i]-j;
		for (i=0;i<m;i++)ws[i]=0;
		for (i=0;i<n;i++)ws[wv[i]=x[y[i]]]++;
		for (i=1;i<m;i++)ws[i]+=ws[i-1];
		for (i=n-1;i>=0;i--)sa[--ws[wv[i]]]=y[i];
		for (t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
		x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}
void getheight(int *r,int *sa,int n){
	int i,j,k=0;
	for (i=1;i<=n;i++)rank[sa[i]]=i;
	for (i=0;i<n;height[rank[i++]]=k)
		for (k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
}
int main(){
	freopen("sub.in","r",stdin);
	freopen("sub.out","w",stdout);
	scanf("%s",st);
	n=strlen(st);
	for (int i=0;i<n;i++)r[i]=st[i];
	r[n]=0;
	da(r,sa,n+1,150);
	getheight(r,sa,n);
	for (int i=1;i<=n;i++){
		while(t&&height[i]<=height[q[t]])t--;
		L[i]=q[t];
		q[++t]=i;
	}
	q[0]=n+1;t=0;
	for (int i=n;i;i--){
		while(t&&height[i]<=height[q[t]])t--;
		R[i]=q[t]-1;
		q[++t]=i;
	}
	for (int i=1;i<=n;i++)if(R[i]>L[i])
		ans=max(ans,(ll)(R[i]-L[i]+1)*height[i]);
	printf("%lld\n",ans);
}
