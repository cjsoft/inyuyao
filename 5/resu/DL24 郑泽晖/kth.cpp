/*#include<cstdio>
struct node{
	node *child[2];
	int dat,priority,sz;
}*gg;

struct treap{
	node *root;
	treap(){
		if (!gg){
			gg=new node;
			gg->child[0]=gg->child[1]=gg;
			gg->dat=0;


struct segnode{
	int l,r;
*/

#include<cstdio>
#include<algorithm>
#include<cstring>

const int ksize=256;
//shl 8



int s[82000],k[82000];
//int ks[600];
int n,q,laststart;
int sumk;
int buf[600];
int xiaoyu,dengyu;
int tmp[600];
/*
void init(){
	scanf("%d",&n);
	laststart=ks((n-1)>>8);
	for (int i=0;i<n;i++) {
		scanf("%d",s+i);
		k[i]=s[i];
	}
	for (int i=0;i<=getk(n-1);i++) std::sort(s+ks(i),s+ke(i)+1);
	scanf("%d",&q);
}
*/

void check(int i){
	for (int j=(i<<8);j<(i+1)<<8;j++) k[j]=s[j];
	std::sort(k+(i<<8),k+((i+1)<<8));
}

void pushdown(int i){
	if (buf[i]){
		for (int j=(i<<8);j<(i+1)<<8;j++) {
			s[j]+=buf[i];
			k[j]=s[j];
		}
		buf[i]=0;
		std::sort(k+(i<<8),k+((i+1)<<8));
	}
}



void init(){
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		scanf("%d",s+i);
		k[i]=s[i];
	}
	scanf("%d",&q);
	while ((n & 255) != 0) {
		s[n]=k[n]=10000000;
		++n;
	}
	int ks=n>>8;
	memset(buf,0,sizeof(buf));
	for (int i=0;i<ks;i++) std::sort(k+(i<<8),k+((i+1)<<8));
}

void insert(int l,int r,int k){
	pushdown(l>>8);
	for (int i=l;i<=r;i++) s[i]+=k;
	check(l>>8);

}

void prin(){
    for (int i=0;i<4;i++) printf("%d ",k[i]);
}

void add(int l,int r,int k){
	if ((l>>8)==(r>>8)){
		insert(l,r,k);
		//prin();
		return;
	}
	insert(l,(l/256)*256+255,k);
	for (int i=(l>>8)+1;i<=(r>>8)-1;i++) buf[i]+=k;
	insert((r/256)*256,r,k);
}

void xy(int l,int r,int d){
	//prin();
	int *pos=std::lower_bound(k+l,k+r+1,d-buf[l>>8]);
	int *pos2=std::upper_bound(k+l,k+r+1,d-buf[l>>8]);
	xiaoyu+=pos-k-l;
	dengyu+=pos2-pos;
}

void xy2(int l,int r,int d){
	int tot=0;
	for (int i=l;i<=r;i++) tmp[++tot]=s[i];
	std::sort(tmp+1,tmp+tot+1);
	for (int i=1;i<=tot;i++) {
		if (tmp[i]<d) ++xiaoyu;
		else if (tmp[i]==d) ++dengyu;
		else break;
	}
}

void pan(int l,int r,int ans){
	xiaoyu=dengyu=0;
	pushdown(l>>8);pushdown(r>>8);
	if ((l>>8)==(r>>8)){
		xy2(l,r,ans);
		return;
	}
	xy2(l,(l/256)*256+255,ans);
	for (int i=(l>>8)+1;i<=(r>>8)-1;i++) xy(i<<8,(i<<8)+255,ans);
	xy2((r/256)*256,r,ans);
}

void query(int ll,int rr,int k){
	int l=-5100000,r=5100000;
	//printf("~~~%d %d %d\n",ll,rr,n);
	while (l!=r){
		int mid=(l+r)>>1;
		pan(ll,rr,mid);
		//printf("%d~%d~%d~\n",mid,xiaoyu,dengyu);
		if ((xiaoyu<k)&&(xiaoyu+dengyu>=k)){
			printf("%d\n",mid);
			return;
		}
		else if (k<=xiaoyu) r=mid;
		else l=mid+1;
	}
}


int main(){
	freopen("kth.in","r",stdin);
	freopen("kth.out","w",stdout);
	init();
	for (int qqq=0;qqq<q;qqq++){
		int t1,t2,t3,t4;
		scanf("%d%d%d%d",&t1,&t2,&t3,&t4);
		if (t1==1) add(t2-1,t3-1,t4);
		else query(t2-1,t3-1,t4);
		//for (int i=0;i<n;i++) printf("%d ",s[i]-buf[i>>8]);
		//printf("\n");
	}
	return 0;
}

