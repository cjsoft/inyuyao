#include<cstdio>
#include<iostream>
#include<cstring>
#include<stack>
#include<queue>
#include<algorithm>
using namespace std;

int n,t1,t2,src,to,m,now,sum;
queue<int>spfa;
vector<int>map[10001];
int dist[10001];

int main(){
	ios::sync_with_stdio(false);
	freopen ("drive.in","r",stdin);
	freopen ("drive.out","w",stdout);
	cin>>n;
	for (int i=1;i<n;i++) map[i].push_back(i+1);
	for (int i=n;i>1;i--) map[i].push_back(i-1);
	map[n].push_back(1);
	for (int i=1;i<=n-3;i++){
		cin>>t1>>t2;
		map[t1].push_back(t2);
		map[t2].push_back(t1);
	}
	
	cin>>m;
	for (int i=1;i<=m;i++){
		cin>>src>>to;
		
		for (int i=1;i<=n;i++) dist[i]=10000003;
		dist[src]=0;
		spfa.push(src);
		while (!spfa.empty()){
			now=spfa.front();
			spfa.pop();
			for (int i=0;i<map[now].size();i++){
				t1=map[now][i];
				if (dist[t1]>dist[now]+1){
					dist[t1]=dist[now]+1;
					spfa.push(t1);
				}
			}
			
		}
		cout<<dist[to]<<endl;
	}
	
	return 0;
}












