#include<cstdio>
#include<algorithm>
#include<queue>
using std::queue;
const int maxpoint=7001;
queue<int> q[maxpoint];
int head[maxpoint],nxt[maxpoint*2],twd[maxpoint*2],sumedge;
int dis[maxpoint][maxpoint];
int n,qqq;

void add(int s,int t){
	nxt[++sumedge]=head[s];
	head[s]=sumedge;
	twd[sumedge]=t;
}

void init(){
	scanf("%d",&n);
	for (int i=0;i<n-3;i++){
		int t1,t2;
		scanf("%d%d",&t1,&t2);
		add(t1,t2);add(t2,t1);
	}
	for (int i=1;i<n;i++) {
        add(i,i+1);add(i+1,i);
	}
	add(n,1);add(1,n);
	scanf("%d",&qqq);
}

int query(int t1,int t2){
	if (t1==t2) return 0;
	if (dis[t1][t2]) return dis[t1][t2];
	if (dis[t2][t1]) return dis[t2][t1];
	if (t1>t2) std::swap(t1,t2);
	while (!q[t1].empty()){
		int p=q[t1].front();
		bool ok=false;
		for (int now=head[p];now;now=nxt[now]){
			int v=twd[now];
			if (!dis[t1][v]){
				dis[t1][v]=dis[t1][p]+1;
				q[t1].push(v);
			}
			if (v==t2) ok=true;
		}
		q[t1].pop();
		if (ok) return dis[t1][t2];
	}
}


int main(){
	freopen("drive.in","r",stdin);
	freopen("drive.out","w",stdout);
	init();
	//for (int i=1;i<=n;i++) while (!q[i].empty()) q[i].pop();
	for (int i=1;i<=n;i++) q[i].push(i);
	for (int i=0;i<qqq;i++){
		int t1,t2;
		scanf("%d%d",&t1,&t2);
		printf("%d\n",query(t1,t2));
	}
	return 0;
}
