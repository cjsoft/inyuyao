#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

int n,m,k;
long long a[100001][5],b[100001],c[100001]; 

bool cmp(int a,int b){
	return a>b;
}

int main(){
	freopen ("b.in","r",stdin);
	freopen ("b.out","w",stdout);
	
	ios::sync_with_stdio(false);
	cin>>n>>m>>k;
	
	for (int i=0;i<m;i++){
		for (int j=0;j<n;j++){
			cin>>a[j][i];
		}
	}
	
	for (int i=0;i<n;i++) cin>>b[i];

	for (int i=0;i<n;i++){
		for (int j=0;j<n;j++){
			c[i]+=a[j][b[(i*j)%n]];
		}
	}
	
	sort (c,c+n,cmp);

	cout<<c[k-1];


	return 0;
}


















