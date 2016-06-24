#include<bits/stdc++.h>
using namespace std;
typedef long long int64;
const int maxn=4010;
int f[maxn][maxn];
char s[maxn]; int n,m;

int main(){
	scanf("%d%d%s",&n,&m,s+1);
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;++i)
		f[i][i]=true;
	for(int len=2;len<=n;++len)
		for(int i=1,j=len;j<=n;++i,++j)
			f[i][j]=(j-i==1||f[i+1][j-1])&&(s[i]==s[j]);
	for(int i=n;i>=1;--i)
		for(int j=i;j<=n;++j)
			f[i][j]+=f[i+1][j]+f[i][j-1]-f[i+1][j-1];
	for(int i=1,l,r;i<=m;++i){
		scanf("%d%d",&l,&r);
		printf("%d\n",f[l][r]);
	}
	return 0;
}

