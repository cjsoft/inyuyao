#include<set>
#include<ctime>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define aabs(a) (a>0?a:-(a))
const int maxn=505;
using namespace std;
int n,K,D[maxn],C[maxn],S[maxn],W[maxn],f[maxn][maxn],ans,sum;bool bo[maxn];
void clear(){ans=0,memset(f,63,sizeof(f));}
int dis(int i,int j){return aabs(D[i]-D[j]);}

int get(int l,int r){
	memset(bo,1,sizeof(bo));
	int res=0;
	for (int i=l;i<=r;i++)
		if (dis(l,i)>S[i]&&dis(i,r)>S[i])
			res+=W[i];
	return res;
}

void work(){
	for (int i=1;i<=n;i++){
		f[i][1]=C[i];
		for (int j=1;j<=i;j++)
			if (dis(i,j)>S[j]) f[i][1]+=W[j];
	}
	for (int k=2;k<=K;k++)
		for (int i=k;i<=n;i++)
			for (int j=1;j<i;j++){
				f[i][k]=min(f[i][k],f[j][k-1]+get(j,i)+C[i]);
			}
	for (int i=1;i<=n;i++){
		int res=1e9+7;
		for (int j=1;j<=K;j++)
			res=min(res,f[i][j]);
		for (int j=i;j<=n;j++)
			if (dis(i,j)>S[j]) res+=W[j];
		ans=min(ans,res);
	}
	printf("%d\n",ans);
}

int main(){
	scanf("%d%d",&n,&K);
	clear();
	for (int i=2;i<=n;i++) scanf("%d",&D[i]);
	for (int i=1;i<=n;i++) scanf("%d",&C[i]);
	for (int i=1;i<=n;i++) scanf("%d",&S[i]);
	for (int i=1;i<=n;i++) scanf("%d",&W[i]),ans+=W[i];
	work();
	return 0;
}

