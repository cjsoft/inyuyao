#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>
#include<climits>
using namespace std;

const int inf=INT_MAX/2;
const int INF=1000000007;

struct E{
	long long t,v;
};

vector<E>map[5002];
queue<long long>spfa;
long long dist[5002];
long long n,m,t,sum,t1,t2,t3;

void spfaonce(){
	for (int i=2;i<=n;i++) dist[i]=inf;
	dist[1]=0;
	spfa.push(1);
	long long now=0;
	while (!spfa.empty()){
		now=spfa.front();
		spfa.pop();
		for (int i=0;i<map[now].size();i++){
			E to=map[now][i];
			if (dist[to.t]>dist[now]+to.v){
				dist[to.t]=dist[now]+to.v;
				spfa.push(to.t);
			}
		}
	}
	for (int i=1;i<=n;i++){
		sum+=dist[i];
		sum%=INF;
		//cout<<dist[i]<<" ";
	}
	//cout<<endl;
}

int main(){
	ios::sync_with_stdio(false);
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	
	cin>>n>>m>>t;
	
	for (int i=1;i<=m;i++){
		cin>>t1>>t2>>t3;
		map[t1].push_back((E){t2,t3});
		map[t2].push_back((E){t1,t3});
	}
	
	for (int k=0;k<=t;k++){
		spfaonce();
		for (int i=1;i<=n;i++){
			for (int j=0;j<map[i].size();j++){
				map[i][j].v++;
			}
		}
	}
	
	cout<<sum<<endl;
	
	return 0;
}












