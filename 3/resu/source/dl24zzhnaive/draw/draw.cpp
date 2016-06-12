#include<cstdio>
#include<algorithm>
const int maxpoint=2500;
int head[maxpoint],nxt[maxpoint*2],twd[maxpoint*2],dat[maxpoint*2],sumedge;
int fab[maxpoint],dep[maxpoint];
int n;
long long ans;
int s[maxpoint],top;

void add(int s,int t,int w){
	nxt[++sumedge]=head[s];head[s]=sumedge;twd[sumedge]=t;dat[sumedge]=w;
	nxt[++sumedge]=head[t];head[t]=sumedge;twd[sumedge]=s;dat[sumedge]=w;
}

void dfs(int u,int father,int depth){
	dep[u]=depth;
	for (int now=head[u];now;now=nxt[now]){
		int v=twd[now];
		if (v==father){
			fab[u]=now;
			continue;
		}
		dfs(v,u,depth+1);
	}
}

void init(){
	scanf("%d",&n);
	for (int i=1;i<n;i++){
		int t1,t2,t3;
		scanf("%d%d%d",&t1,&t2,&t3);
		add(t1,t2,t3);
	}
	dfs(1,0,0);
	ans=0;
}

void query(int i,int j){
	int x=i,r=j;
	if (dep[i]<dep[j]) std::swap(i,j);
	if ((dep[i]-dep[j])%2==0) return;
	top=0;
	int tat=dep[i]-dep[j];
	for (int k=0;k<tat;k++){
		s[++top]=dat[fab[i]];
		i=twd[fab[i]];
	}
	while (i!=j){
		s[++top]=dat[fab[i]];
		s[++top]=dat[fab[j]];
		i=twd[fab[i]];
		j=twd[fab[j]];
	}
	//for (int i=1;i<=top;i++) printf("%d~",s[i]);
	//printf("\n");
	std::nth_element(s+1,s+(top>>1)+1,s+top+1);
	ans+=s[(top>>1)+1];
	//printf("%d %d %lld!@#!@#\n",x,r,ans);
	
}

int main(){
	freopen("draw.in","r",stdin);
	freopen("draw.out","w",stdout);
	init();
	for (int i=1;i<n;i++) for (int j=i+1;j<=n;j++) query(i,j);
	printf("%lld",ans);
	return 0;
}
