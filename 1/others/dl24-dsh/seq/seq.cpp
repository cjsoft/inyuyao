#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;

int n,m;
int t1,t2,t3,t4;
int all[10001];

int main(){
	freopen ("seq.in","r",stdin);
	freopen ("seq.out","w",stdout);
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=0;i<n;i++) cin>>all[i];
	for (int i=1;i<=m;i++){
		cin>>t1>>t2>>t3;
		if (t1==0){
			cin>>t4;
			for (int j=t2;j<=t3;j++) all[j]+=t4;
		}
		if (t1==1){
			for (int j=t2;j<=t3;j++) all[j]*=-1;
		}
		if (t1==2){
			int sum=0;
			for (int j=t2;j<=t3;j++) sum+=abs(all[j]);
			cout<<sum<<endl;
		}
	}
	
	return 0;
} 












