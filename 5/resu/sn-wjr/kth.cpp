#include<iostream>
#include<stdio.h>
#include<map>
#include<algorithm>
using namespace std;
int n,m;
int a[80050],b[80050];
map<int,int> vis;
int tot=0,root[800050],L[1600050],R[1600050],sum[1600050];
void insert(int x,int y,int l,int r,int num){
//	cout<<x<<' '<<y<<' '<<l<<' '<<r<<' '<<num<<endl;
	if(l==r){
		sum[y]=sum[x]+1;
		return;
	}
	int mid=(l+r)>>1;
	if(num<=mid){
		L[y]=++tot,R[y]=R[x];
		insert(L[x],L[y],l,mid,num);
	}
	else{
		R[y]=++tot,L[y]=L[x];
		insert(R[x],R[y],mid+1,r,num);
	}
	sum[y]=sum[L[y]]+sum[R[y]];
}
int query(int x,int y,int l,int r,int num){
	//cout<<x<<' '<<y<<' '<<l<<' '<<r<<' '<<num<<endl;
	if(l==r) return l;
	int mid=(l+r)>>1;
	if(L[y]&&sum[L[y]]-sum[L[x]]>=num) return query(L[x],L[y],l,mid,num);
	else return query(R[x],R[y],mid+1,r,num-(sum[L[y]]-sum[L[x]]));
}
int main(){
	freopen("kth.in","r",stdin);
	freopen("kth.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	scanf("%d",&m);
	if(n<=1000){
		for(int i=1;i<=m;i++){
			int id,l,r,k;
			scanf("%d%d%d%d",&id,&l,&r,&k);
			if(id==1){
				for(int i=l;i<=r;i++)
					a[i]+=k;
			}
			else{
				for(int i=l;i<=r;i++)
					b[i]=a[i];
				sort(b+l,b+1+r);
				printf("%d\n",b[l+k-1]);
			}
		}
	}
	else{for(int i=1;i<=n;i++)
			b[i]=a[i];
		sort(b+1,b+1+n);
		for(int i=1;i<=n;i++)
			vis[b[i]]=i;
		for(int i=1;i<=n;i++) a[i]=vis[a[i]];
//		for(int i=1;i<=n;i++) cout<<a[i]<<' ';
	//	cout<<endl;
		for(int i=1;i<=n;i++)
			root[i]=++tot,insert(root[i-1],root[i],1,n,a[i]);
		for(int i=1;i<=m;i++){
			int id,l,r,k;
			scanf("%d%d%d%d",&id,&l,&r,&k);
			if(id==2){
					printf("%d\n",b[query(root[l-1],root[r],1,n,k)]);	
			}
		}
	}
}