#include<cstdio>
#include<algorithm>
#include<cstring>

int n,m,k;
int c[400][400];
//int dp[400][400][400];
const int maxpoint=110000;
const int maxedge=400000;
const int teachk=2133333333;

int head[maxpoint],nxt[maxedge],twd[maxedge],cost[maxedge],dat[maxedge];
int sumedge,source,sink;
int dis[maxpoint],prev[maxpoint],pree[maxpoint];
int q[maxedge],top,tail;
bool inq[maxpoint];

int ans;

void add(int s,int t,int c,int d){
	nxt[++sumedge]=head[s];
	head[s]=sumedge;
	twd[sumedge]=t;
	dat[sumedge]=d;
	cost[sumedge]=c;
}

int trans(int x,int y){
	return (x-1)*m+y;
}


void init(){
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) scanf("%d",&c[i][j]);
	//for (int j=1;j<=n;j++) 
	sumedge=1;
	source=n*m+1;
	sink=n*m+2;
	for (int i=1;i<=m;i++){
		add(source,trans(1,i),c[1][i],1);
		add(trans(1,i),source,-c[1][i],0);
	}
	for (int i=2;i<=n;i++) for (int j=1;j<=m;j++){
		add(trans(i-1,j),trans(i,j),c[i][j],1);
		add(trans(i,j),trans(i-1,j),-c[i][j],0);
	}
	for (int i=1;i<=m;i++){
		add(trans(n,i),sink,0,1);
		add(sink,trans(n,i),0,0);
	}
	for (int i=1;i<=n;i++) for (int j=1;j<m;j++){
		add(trans(i,j),trans(i,j+1),k,teachk);
		add(trans(i,j+1),trans(i,j),-k,0);
		add(trans(i,j+1),trans(i,j),k,teachk);
		add(trans(i,j),trans(i,j+1),-k,0);
	}
}

void plus(int &a){
	++a;
	if (a==300000) a=1;
}

void getpath(){
	memset(dis,0x3f,sizeof(dis));
	memset(inq,false,sizeof(inq));
	dis[source]=0;
	top=1;tail=2;
	q[1]=source;
	inq[source]=true;
	while (top!=tail){
		int u=q[top];
		plus(top);
		for (int now=head[u];now;now=nxt[now]){
			if (!dat[now]) continue;
			int v=twd[now];
			if (dis[v]>dis[u]+cost[now]){
				dis[v]=dis[u]+cost[now];
				prev[v]=u;
				pree[v]=now;
				if (!inq[v]){
					q[tail]=v;
					plus(tail);
					inq[v]=true;
				}
			}
		}
		inq[u]=false;
	}
}

void cute(){
	getpath();
	//for (int i=1;i<=sink;i++) printf("%d ",prev[i]);
	//printf("\n");
	int v=sink;
	while (v!=source){
		--dat[pree[v]];
		++dat[pree[v]^1];
		ans+=cost[pree[v]];
		v=prev[v];
	}
}

int main(){
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	init();
	cute();
	cute();
	printf("%d\n",ans);
	return 0;
}

