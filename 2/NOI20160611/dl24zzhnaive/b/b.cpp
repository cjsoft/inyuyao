#include<cstdio>
#include<algorithm>
int n,m,k;
int a[32999][4];
int c[32999],b[32999];
int main(){
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for (int j=0;j<m;j++) for (int i=0;i<n;i++) scanf("%d",&a[i][j]);
	for (int i=0;i<n;i++) scanf("%d",b+i);
	for (int i=0;i<n;i++) for (int j=0;j<n;j++) c[i]+=a[j][b[i*j%n]];
	//for (int i=0;i<n;i++) printf("%d ",c[i]);
	std::nth_element(c,c+n-k,c+n);
	printf("%d",c[n-k]);
	return 0;
}
