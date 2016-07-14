#include<cstdio>
#include<algorithm>

struct cute{
	int d,p;
	bool operator <(const cute &b)const{
		if (d!=b.d) return d>b.d;
		return p<b.p;
	}
}tmp[30];

bool cmp(const cute &a,const cute &b){
	return a.p<b.p;
}

const int TAT[]={0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1};

int l[30],r[30],k;
int mark[30];
long long cnt[30][2];
double ans[30][2];
long long tot;

int n;

void init(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",l+i);
	for (int i=1;i<=n;i++) scanf("%d",r+i);
	tot=1;
	for (int i=1;i<=n;i++) tot*=(r[i]-l[i]+1);
	scanf("%d",&k);
}

void check(){
	for (int i=1;i<=n;i++){
		tmp[i].d=mark[i];
		tmp[i].p=i;
	}
	
	std::sort(tmp+1,tmp+n+1);
	
	std::sort(tmp+1,tmp+k+1,cmp);
	
	
	for (int i=1;i<=k;i++) cnt[tmp[i].p][TAT[i]]++;
}


void dfs(int now){
	if (now==n+1) {
		check();
		return;
	}
	for (int i=l[now];i<=r[now];i++){
		mark[now]=i;
		dfs(now+1);
	}
}

int main(){
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	init();
	dfs(1);
	for (int i=1;i<=n;i++) for (int j=0;j<=1;j++) ans[i][j]=cnt[i][j]*1.0/tot;
	for (int i=1;i<=n;i++) printf("%.6lf %.6lf\n",ans[i][0],ans[i][1]);
	return 0;
}

