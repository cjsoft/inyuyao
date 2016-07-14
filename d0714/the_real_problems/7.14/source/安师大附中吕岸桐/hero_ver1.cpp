#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int N=305;
const long long INF=210000000000000ll;

int n,m;
long long f[2][N][N],K,t[N][N];

template<typename T> void Read(T &x){
char ch;
while((ch=getchar())<'0' || ch>'9');
x=ch-'0';
while((ch=getchar())>='0' && ch<='9')x=x*10+ch-'0';
}

template<typename T> T Abs(T x){return x>0?x:-x;}

void Bf(){
memset(f,60,sizeof(f));
for(int i=1;i<=m;i++){
	for(int j=1;j<=m;j++){
		if(i==j)continue;
		f[1][i][j]=t[1][i]+t[1][j];
	}
}
for(int i=2;i<=n;i++){
	int now=i&1,pre=now^1;
	//printf("%d %d %d\n",i,now,pre);
	for(int j=1;j<=m;j++){
		for(int k=1;k<=m;k++){
			if(j==k)continue;
			f[now][j][k]=INF;
			for(int l1=1;l1<=m;l1++){
				for(int l2=1;l2<=m;l2++){
					if(l1==l2)continue;
					f[now][j][k]=min(f[now][j][k],f[pre][l1][l2]+t[i][j]+t[i][k]+K*(Abs(j-l1)+Abs(k-l2)));
					//printf("%d %d %d %d %d %lld %lld\n",i,j,k,l1,l2,f[now][j][k],f[pre][l1][l2]);
				}
			}
			//printf("%d %d %d:%lld\n",i,j,k,f[now][j][k]);
		}
	}
}
long long ans=INF;
for(int i=1;i<=m;i++){
	for(int j=1;j<=m;j++){
		if(i==j)continue;
		ans=min(ans,f[n&1][i][j]);
	}
}
printf("%lld\n",ans);
}

void Co(){

}

int main(){
freopen("hero.in","r",stdin);
freopen("hero.out","w",stdout);
Read(n);Read(m);Read(K);
for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++)Read(t[i][j]);
}
if(n<=50)Bf();
else Co();
return 0;
}

