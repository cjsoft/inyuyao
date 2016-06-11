#include<cstdio>
#include<algorithm>

struct node{
	int sz;
	node *ls,*rs;
}pool[200000000/sizeof(node)];

const int maxpoint=270000;
const int lll=1;

int n,rrr,q;

node *root[maxpoint];

int tdat[maxpoint];
int head[maxpoint],nxt[maxpoint*2],twd[maxpoint*2],sumedge;
int hson[maxpoint],siz[maxpoint],dep[maxpoint],fa[maxpoint];
int fir[maxpoint],ts[maxpoint],st[maxpoint];
int s[maxpoint],tot;
int t1,t2,t3;
//int xiaoyu,dengyu,dayu;
int dengyu;
int ans1,ans2,ans3;

void add(int s,int t){
	nxt[++sumedge]=head[s];
	head[s]=sumedge;
	twd[sumedge]=t;
	nxt[++sumedge]=head[t];
	head[t]=sumedge;
	twd[sumedge]=s;
}

void dfs1(int u,int father,int depth){
	siz[u]=1;
	hson[u]=0;
	fa[u]=father;
	dep[u]=depth;
	for (int now=head[u];now;now=nxt[now]){
		int v=twd[now];
		if (v==father) continue;
		dfs1(v,u,depth+1);
		if (siz[v]>siz[hson[u]]) hson[u]=v;
		siz[u]+=siz[v];
	}
}

void dfs2(int u,int First){
	s[++tot]=tdat[u];
	ts[u]=tot;
	st[tot]=u;
	fir[u]=First;
	if (hson[u]!=0) dfs2(hson[u],First);
	for (int now=head[u];now;now=nxt[now]){
		int v=twd[now];
		if (v==fa[u]||v==hson[u]) continue;
		dfs2(v,v);
	}
}

void add(node *&now,int k,int l,int r){
	node *t=now;
	now=&pool[++tot];
	if (t) *now=*t;
	else {
		now->sz=0;
		now->ls=now->rs=0;
	}
	++now->sz;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (k<=mid) add(now->ls,k,l,mid);
	else add(now->rs,k,mid+1,r);
}

int queryxiaoyu(node *a,int k,int l,int r){
	if (!a) {
		dengyu=0;
		return 0;
	}
	if (l==r){
		dengyu=a->sz;
		return 0;
	}
	int mid=(l+r)>>1;
	if (k<=mid) return queryxiaoyu(a->ls,k,l,mid);
	//else if (k==mid+1) return a->ls->sz;
	else return ((a->ls)?(a->ls->sz):0)+queryxiaoyu(a->rs,k,mid+1,r);
}

void query(int ll,int rr,int k){
	int xxx,yyy,zzz;
	if (ll>rr) std::swap(ll,rr);
	dengyu=0;
	//if (ll==1&&rr==3) printf("@#$@#$@#$\n");
	xxx=queryxiaoyu(root[rr],k,1,rrr);
	yyy=dengyu;
	//if (ll==1&&rr==3) printf("@#$@#$@#$\n");
	xxx-=queryxiaoyu(root[ll-1],k,1,rrr);
	yyy-=dengyu;
	zzz=0;
	if (root[rr]) zzz+=root[rr]->sz;
	if (root[ll-1]) zzz-=root[ll-1]->sz;
	ans1+=xxx;ans2+=yyy;ans3+=(zzz-xxx-yyy);
}

/* void _ask(int tx,int ty,int k){
	if (fir[tx]==fir[ty]){
		query(ts[tx],ts[ty],k);
		return;
	}
	if (dep[tx]<dep[ty]) std::swap(ty,tx);
	query(ts[fir[tx]],ts[tx],k);
	_ask(fa[fir[tx]],ty,k);
} */
void _ask(int tx,int ty,int k){
    //printf("%d!!!%d\n",tx,ty);
	if (fir[tx]==fir[ty]){
		query(ts[tx],ts[ty],k);
		return;
	}
	if (dep[fir[tx]]<dep[fir[ty]]) std::swap(ty,tx);
	//printf("%d~~%d\n",tx,ty);
	if (fir[tx]!=tx){
		query(ts[hson[fir[tx]]],ts[tx],k);
		_ask(fir[tx],ty,k);
		return;
	}
	if (tdat[tx]<k) ++ans1;
	else if (tdat[tx]==k) ++ans2;
	else ++ans3;
	//printf(")(*&^%\n");
	_ask(fa[tx],ty,k);
}

void ask(int tx,int ty,int k){
	ans1=0;ans2=0;ans3=0;
	_ask(tx,ty,k);
	printf("%d %d %d\n",ans1,ans2,ans3);
}


int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d%d",&n,&rrr,&q);
	for (int i=1;i<=n;i++) scanf("%d",tdat+i);
	for (int i=1;i<n;i++){
		scanf("%d%d",&t1,&t2);
		add(t1,t2);
	}
	siz[0]=0;
	tot=0;
	dfs1(1,1,0);
	//printf("!@#!@%$!@%!\n");
	dfs2(1,1);
	//printf("!@#!@%$!@%!\n");
	/* for (int i=1;i<=n;i++){
		printf("%d %d %d %d %d\n",ts[i],hson[i],fir[i],fa[i],s[i]);
	} */
	tot=0;
	for (int i=1;i<=n;i++){
		root[i]=root[i-1];
		add(root[i],s[i],1,rrr);
	}
	ans1=ans2=ans3=0;
	for (int i=0;i<q;i++){
		scanf("%d%d%d",&t1,&t2,&t3);
		ans1=ans1^ans2^ans3;
		//printf("!@#!@%$!@%!\n");
		ask(t1^ans1,t2^ans1,t3^ans1);

	}
	return 0;
}
