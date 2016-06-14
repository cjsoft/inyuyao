#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxLen 1001000

char str[maxLen];
int s[maxLen];
int h[maxLen],sa[maxLen];
int len;
int fa[maxLen],sz[maxLen];
int maxsize;
long long ans;
struct lovelive{
    int x,y;
}gg[maxLen];

bool operator <(const lovelive &a,const lovelive &b){
    return a.x>b.x;
}
void radix(int str[],int a[],int b[],int n,int m){
	static int count[maxLen];
	memset(count,0,sizeof(count));
	for (int i=0;i<n;i++) count[str[i]]++;
	for (int i=1;i<=m;i++) count[i]+=count[i-1];
	for (int i=n-1;i>=0;i--) b[--count[str[a[i]]]]=a[i];
}
void suffix_array(int str[],int sa[],int n,int m){
	static int rank[maxLen],a[maxLen],b[maxLen];
	for (int i=0;i<n;i++) rank[i]=i;
	radix(str,rank,sa,n,m);
	rank[sa[0]]=0;
	for (int i=1;i<n;i++) rank[sa[i]]=rank[sa[i-1]]+(str[sa[i]]!=str[sa[i-1]]);
	for (int i=1;i<n;i=i<<1){
		for (int j=0;j<n;j++){
			a[j]=rank[j]+1;
			b[j]=j+i>=n? 0 : rank[j+i]+1;
			sa[j]=j;
		}
		radix(b,sa,rank,n,n);
		radix(a,rank,sa,n,n);
		rank[sa[0]]=0;
		for (int j=1;j<n;j++){
			rank[sa[j]]=rank[sa[j-1]]+(a[sa[j-1]]!=a[sa[j]] || b[sa[j-1]]!=b[sa[j]]);
		}
	}
}

void calc_height(int *str,int *sa,int *h,int n){
	static int rank[maxLen];
	int k=0;
	h[0]=0;
	for (int i=0;i<n;i++) rank[sa[i]]=i;
	for (int i=0;i<n;i++){
		k= k==0?0:k-1;
		if (rank[i]!=0) while (str[i+k]==str[sa[rank[i]-1]+k]) k++;
		h[rank[i]]=k;
	}
}

int getfa(int x){
	return fa[x]==x?x:fa[x]=getfa(fa[x]);
}
int getsz(int x){
	return sz[getfa(x)];
}
void merge(int x,int y){
	x=getfa(x);y=getfa(y);
	if (sz[x]>sz[y]) std::swap(x,y);
	sz[y]+=sz[x];
	fa[x]=y;
}



int main(){
	freopen("sub.in","r",stdin);
	freopen("sub.out","w",stdout);
	scanf("%s",str);
	len=strlen(str);
	for (int i=0;i<len;i++) s[i]=str[i];
	suffix_array(s,sa,len,123);
	calc_height(s,sa,h,len);
	//for (int i=0;i<len;i++) printf("%d ",sa[i]+1);
	//printf("\n");
	//for (int i=1;i<len;i++) printf("%d ",h[i]);
	for (int i=1;i<len;i++){
        gg[i].x=h[i];gg[i].y=i;sz[i]=1;fa[i]=i;
	};
	sz[len]=1;fa[len]=len;
    std::sort(gg+1,gg+len);
	maxsize=1;ans=0;
    for (int i=1;i<len;i++){
		merge(gg[i].y,gg[i].y+1);
		//printf("%d ",getsz(gg[i].y));
		maxsize=std::max(getsz(gg[i].y),maxsize);
		if (maxsize>1) ans=std::max(ans,(long long)gg[i].x*maxsize);
	}
	printf("%lld",ans);
	return 0;

}
