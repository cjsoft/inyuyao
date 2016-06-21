#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 400005
#define ll long long
int n,m,k,l,t,M;
int a[N],b[N],c[N],p[N],d[N];
ll tr[N],ans,s,t2[N];
bool cmp(int x,int y){
	return b[x]<b[y];
}
void add(int x,int v){
	for (int i=x;i<=M;i+=i&-i)tr[i]+=v,t2[i]+=v/abs(v);
}
ll que(int x){
	ll s=0;
	for (int i=x;i;i-=i&-i)s+=tr[i];
	return s;
}
ll ask(int x){
	ll s=0;
	for (int i=x;i;i-=i&-i)s+=t2[i];
	return s;
}
void ins(int x,int v){
	ans+=a[x]*v;
	s+=b[x]*v;
	add(d[x],b[x]*v);
	ans-=(ll)v*b[x]*(n-ask(d[x]));
	ans-=que(d[x])*v;
}
int main(){
	freopen("RASPORED.in","r",stdin);
	freopen("RASPORED.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++){
		scanf("%d%d",&a[i],&b[i]);
		ans+=a[i];
		s+=b[i];
		p[i]=i;
	}
	M=n+m;
	for (int i=n+1;i<=M;i++)scanf("%d%d%d",&c[i],&a[i],&b[i]),p[i]=i;
	sort(p+1,p+M+1,cmp);
	for (int i=1;i<=M;i++)d[p[i]]=i;
	for (int i=1;i<=n;i++)add(d[i],b[i]);
	for (int i=1;i<=n;i++)ans-=que(d[i]);
	printf("%lld\n",ans);
	for (int i=n+1;i<=M;i++){
		ins(c[i],-1);
		ins(i,1);
		a[c[i]]=a[i];
		b[c[i]]=b[i];
		d[c[i]]=d[i];
		printf("%lld\n",ans);
	}
}
