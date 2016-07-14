#include <cstdio>
#include <algorithm>
inline unsigned int getuint(){
	char w=getchar();
	while (w<'0'||'9'<w) w=getchar();
	unsigned int ans=0;
	for (;'0'<=w&&w<='9';w=getchar()) ans=ans*10+w-'0';
	return ans;
}
int n, m;
int L[233], R[233];
inline int calc(int i){return (i>>1)&1;}
namespace Force233{
	double pre[30][30][30], suf[30][30][30], sumpre[30][30], sumsuf[30][30], ss[30][30][30], A[30][2];
	void solve(){
		for (int i=1;i<=n;i++) L[i]=1000-L[i], R[i]=1000-R[i], std::swap(L[i], R[i]);
		for (int limit=0;limit<=1000;limit++){
			for (int i=0;i<=n;i++) for (int j=0;j<=n;j++) for (int k=0;k<=n;k++) pre[i][j][k]=0;
			pre[0][0][0]=1.0;
			for (int i=1;i<=n;i++) if (R[i]<limit){
				for (int j=0;j<i;j++) for (int k=0;k<i;k++) pre[i][j+1][k]+=pre[i-1][j][k];
			} else if (L[i]<=limit){
				double possless=(limit-L[i])/(R[i]-L[i]+1.0), possequal=1.0/(R[i]-L[i]+1.0),  posssum=possless+possequal;
				for (int j=0;j<i;j++) for (int k=0;k<i;k++){
					pre[i][j][k]+=pre[i-1][j][k]*(1-posssum);
					pre[i][j+1][k]+=pre[i-1][j][k]*possless, pre[i][j][k+1]+=pre[i-1][j][k]*possequal;
				}
			} else{
				for (int j=0;j<i;j++) for (int k=0;k<i;k++) pre[i][j][k]+=pre[i-1][j][k];
			}
			for (int i=0;i<=n;i++) for (int j=0;j<=n;j++) for (int k=n;~k;k--) ss[i][j][k]=pre[i][j][k]+ss[i][j][k+1];
			//for (int i=0;i<=n;i++) for (int j=0;j<=n;j++) for (int k=1;k<=n;k++) pre[i][j][k]+=pre[i][j][k-1];
			for (int i=0;i<=n;i++) for (int j=0;j<=n;j++) sumpre[i][j]=0;
			for (int i=0;i<=n;i++) for (int j=0;j<=n;j++) for (int k=0;j+k<=n;k++) sumpre[i][j+k]+=pre[i][j][k];
			for (int i=n+1;i;i--) for (int j=0;j<=n;j++) for (int k=0;k<=n;k++) suf[i][j][k]=0;
			suf[n+1][0][0]=1.0;
			for (int i=n;i;i--) if (R[i]<limit){
				for (int j=0;j<=n-i;j++) for (int k=0;k<=n-i;k++) suf[i][j+1][k]+=suf[i+1][j][k];
			} else if (L[i]<=limit){
				double possless=(limit-L[i])/(R[i]-L[i]+1.0), possequal=1.0/(R[i]-L[i]+1.0),  posssum=possless+possequal;
				for (int j=0;j<=n-i;j++) for (int k=0;k<=n-i;k++){
					suf[i][j][k]+=suf[i+1][j][k]*(1-posssum);
					suf[i][j+1][k]+=suf[i+1][j][k]*possless, suf[i][j][k+1]+=suf[i+1][j][k]*possequal;
				}
			} else{
				for (int j=0;j<=n-i;j++) for (int k=0;k<=n-i;k++) suf[i][j][k]+=suf[i+1][j][k];
			}
			//for (int i=n+1;i;i--) for (int j=0;j<=n;j++) for (int k=0;k<=n;k++) ss[i][j][k]=0;
			for (int i=n+1;i;i--) for (int j=0;j<=n;j++) for (int k=n;k;k--) suf[i][j][k-1]+=suf[i][j][k];
			for (int i=n+1;i;i--) for (int j=0;j<=n;j++) sumsuf[i][j]=0;
			for (int i=n+1;i;i--) for (int j=0;j<=n;j++) for (int k=0;j+k<=n;k++) sumsuf[i][j+k]+=suf[i][j][k];
			for (int i=1;i<=n;i++){
				double possless=0, possequal=0;
				if (R[i]<limit) possless=1;
				else if (L[i]<=limit) possless=(limit-L[i])/(R[i]-L[i]+1.0), possequal=1.0/(R[i]-L[i]+1.0);
				for (int j=0;j<i&&j<m;j++) for (int k=0;k<=j;k++){
					int x=m-j-1;
					if (k){
						A[i][calc(j+1)]+=pre[i-1][j-k][k]*possless*sumsuf[i+1][x];
						A[i][calc(j+1)]-=pre[i-1][j-k][k]*possless*suf[i+1][x][0];
						A[i][calc(j+1)]+=ss[i-1][j-k][k]*possless*suf[i+1][x][0];
					} else{
						for (int l=0;l<=x;l++) if (k||l){
							if (l) A[i][calc(j+1)]+=pre[i-1][j-k][k]*possless*suf[i+1][x-l][l];
							else A[i][calc(j+1)]+=ss[i-1][j-k][k]*possless*suf[i+1][x-l][l];
						}
					}
				}
				for (int j=0;j<i&&j<m;j++) for (int l=0;l+j<m;l++){
					A[i][calc(j+1)]+=sumpre[i-1][j]*possequal*suf[i+1][l][m-j-1-l];
				}
			}
		}
		for (int i=1;i<=n;i++) printf("%.6f %.6f\n", A[i][0], A[i][1]);
	}
}
int main(){
	freopen("assign.in", "r", stdin);
	freopen("assign.out", "w", stdout);
	n=getuint();
	for (int i=1;i<=n;i++) L[i]=getuint();
	for (int i=1;i<=n;i++) R[i]=getuint();
	m=getuint();
	Force233::solve();
	return 0;
}
