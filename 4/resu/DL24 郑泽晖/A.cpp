#include<cstdio>
#include<cstring>
#include<algorithm>

const int maxpoint=6410000;
const int maxedge=26000000;
const int saffah=1000000007;

int head[maxpoint],nxt[maxedge],twd[maxedge],dat[maxedge],sumedge,sumpoint;
int dist[maxpoint];
bool vis[maxpoint];
int tree[maxpoint*2];
int pt[maxpoint],dis[maxpoint];

int n,m,tttt;
int source;
int ans;

int q1[2700],q2[2700],top;
int tim[2700];

void modsaffah(){
	printf("%d ",sizeof(head)+sizeof(nxt)+sizeof(twd)+sizeof(dat)+sizeof(dist)+sizeof(vis)+sizeof(tree)+sizeof(pt)+sizeof(dis));
}


void add(int s,int t,int w){
	nxt[++sumedge]=head[s];head[s]=sumedge;twd[sumedge]=t;dat[sumedge]=w;
	//nxt[++sumedge]=head[t];head[t]=sumedge;twd[sumedge]=s;dat[sumedge]=w;
}

inline int trans(int i,int j){
	return (i-1)*(n+1)+j+1;
}

void maketree(int l,int r,int now){
	if (l==r) {
		tree[now]=l;
		pt[l]=now;
		return;
	}
	maketree(l,(l+r)>>1,now<<1);
	maketree(((l+r)>>1)+1,r,now<<1|1);
	tree[now]= dis[tree[now<<1]]<dis[tree[now<<1|1]] ? tree[now<<1] : tree[now<<1|1];
}

void update(int p,int k){
	int now=pt[p];
	dis[p]=k;
	now=now>>1;
	while (now){
		tree[now]= dis[tree[now<<1]]<dis[tree[now<<1|1]] ? tree[now<<1] : tree[now<<1|1];
		now=now>>1;
	}
}

void dijkstra(){
	memset(dist,0x3f,sizeof(dist));
	memset(dis,0x3f,sizeof(dis));
	memset(vis,false,sizeof(vis));
	dist[source]=dis[source]=0;
	maketree(1,sumpoint,1);
	for (int j=1;j<sumpoint;j++){
		int p=tree[1];
		//printf("%d\n",p);
		vis[p]=true;
		update(p,0x3f3f3f3f);
		for (int now=head[p];now;now=nxt[now]){
			int v=twd[now];
			if ((!vis[v]) && (dist[p]+dat[now]<dist[v])){
				dist[v]=dist[p]+dat[now];
				update(v,dist[v]);
			}
		}
	}
}

void init(){
	scanf("%d%d%d",&n,&m,&tttt);
	for (int i=0;i<m;i++){
		int t1,t2,t3;
		scanf("%d%d%d",&t1,&t2,&t3);
		for (int j=0;j<n;j++){
			add(trans(t1,j),trans(t2,j+1),t3);
			add(trans(t2,j),trans(t1,j+1),t3);
		}
	}

	sumpoint=trans(n,n);
	source=trans(1,0);
}

int calc(int cost,int bian,int s,int t){
	if ((t-s)&1) return ((long long)((cost<<1)+bian*(s+t)))*((t-s+1)>>1) % saffah;
	else return ((long long)(((cost<<1)+bian*(s+t))>>1))*(t-s+1) % saffah;
}

int main(){
    freopen("A.in","r",stdin);
    freopen("A.out","w",stdout);
	ans=0;
	init();
	dijkstra();
	/*for (int i=1;i<=n;i++){
		for (int j=(n+1)*(i-1)+1;j<=(n+1)*i;j++){
			printf("%d ",dist[j]);
		}
		printf("\n");
	}*/
	//for (int i=1;i<=sumpoint;i++) printf("%d!",dist[i]);
	for (int i=1;i<=n;i++){
		int s=(n+1)*(i-1)+1,t=(n+1)*i;
		for (int j=s+1;j<=t;j++) dist[j]=std::min(dist[j],dist[j-1]);
		//if (i==4){
		//for (int j=s;j<=t;j++) printf("%d ",dist[j]);
		//printf("~~~\n");}
		top=1;
		for (int j=s;j<=t;j++) if (dist[j]<0x3f3f3f2f){
			q1[top]=j-s;
			q2[top]=dist[j];
			break;
		}
		//printf("$#^%$#%\n");
		for (int j=q1[top]+1+s;j<=t;j++){
			if (dist[j]==q2[top]) continue;
			while (top>1){
				if (((long long)q2[top-1]-q2[top])*((long long)j-s-q1[top])<=((long long)q1[top]-q1[top-1])*((long long)q2[top]-dist[j])) --top;
			}

			q1[++top]=j-s;
			q2[top]=dist[j];
			//for (int k=1;k<=top;k++) printf("%d>%d ",q1[k],q2[k]);
			//printf("\n");
		}
		//printf("!@#!@$\n");
		//for (int j=1;j<=top;j++) printf("%d %d~\n",q1[j],q2[j]);
		tim[top+1]=-1;
		for (int j=top;j>1;j--){
			tim[j]=(q2[j-1]-q2[j])/(q1[j]-q1[j-1]);
			ans=(ans+calc(q2[j],q1[j],tim[j+1]+1,tim[j]))%saffah;
		}
		ans=(ans+calc(q2[1],q1[1],tim[2]+1,tttt))%saffah;
		//printf("!@#!@$\n");

	}
    printf("%d\n",ans);

	return 0;
}
