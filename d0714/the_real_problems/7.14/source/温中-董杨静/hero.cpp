#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
const int maxn=333;
const int maxm=maxn*maxn;
typedef long long LL;

inline LL my_abs(const LL &v){
	return v>0?v:-v;
}

void putLL(LL v){
	cout<<v<<endl;
}
int N,M,K,V[maxn][maxn];
int B[maxn];

LL mindis[maxn][maxn];
int last[maxn][maxn];

int Qx[maxn*maxn],Qy[maxn*maxn],qh,qr;
bool inQ[maxn][maxn];
LL bfs(){
	qh=qr=0;
	memset(mindis,-1,sizeof(mindis));
	for(int i=1;i<=M;++i) if(i!=B[1]){
		mindis[1][i]=V[1][i];
		Qx[qr]=1;Qy[qr]=i;++qr;
	}
	while(qh!=qr){
		int x=Qx[qh],y=Qy[qh];++qh;
		inQ[x][y]=false;
		if(qh>=maxm) qh-=maxm;
		if(y==B[x] && x>1){
			LL nd=mindis[x][y]-K*my_abs(y-B[x-1])-V[x][y];
			if(mindis[x-1][B[x-1]]==-1 || mindis[x-1][B[x-1]]>nd){
				mindis[x-1][B[x-1]]=nd;
				if(!inQ[x-1][B[x-1]]){
					if(nd<mindis[Qx[qh]][Qy[qh]]){
						qh=qh?qh-1:maxm-1;
						Qx[qh]=x-1;
						Qy[qh]=B[x-1];
					}else{
						Qx[qr]=x-1;Qy[qr]=B[x-1];++qr;
						if(qr>=maxm) qr-=maxm;
					}
					inQ[x-1][B[x-1]]=true;
				}
			}
		}
		if(x<N){
			for(int i=1;i<=M;++i) if(i!=B[x+1]){
				LL nd=mindis[x][y]+K*my_abs(i-y)+V[x+1][i];
				if(mindis[x+1][i]==-1 || mindis[x+1][i]>nd){
					mindis[x+1][i]=nd;
					last[x+1][i]=y;
					if(inQ[x+1][i]) continue;
					if(nd<mindis[Qx[qh]][Qy[qh]]){
						qh=qh?qh-1:maxm-1;
						Qx[qh]=x+1;
						Qy[qh]=i;
					}else{
						Qx[qr]=x+1;Qy[qr]=i;++qr;
						if(qr>=maxm) qr-=maxm;
					}
					inQ[x+1][i]=true;
				}
			}
			if(B[x+1] && y!=B[x]){
				LL nd=mindis[x][y]+K*my_abs(y-B[x+1])-K*my_abs(B[x]-B[x+1]);
				if(mindis[x][B[x]]==-1 || mindis[x][B[x]]>nd){
					mindis[x][B[x]]=nd;
					if(!inQ[x][B[x]]){
						if(nd<mindis[Qx[qh]][Qy[qh]]){
							qh=qh?qh-1:maxm-1;
							Qx[qh]=x;
							Qy[qh]=B[x];
						}else{
							Qx[qr]=x;Qy[qr]=B[x];++qr;
							if(qr>=maxm) qr-=maxm;
						}
						inQ[x][B[x]]=true;
					}
				}
			}

		}
	}
	LL ret=1E18;int p=-1;
	for(int i=1;i<=M;++i) if(mindis[N][i]!=-1 && mindis[N][i]<ret){
		ret=mindis[N][i];
		p=i;
	}
	for(int x=N,y=p;x;){
		B[x]=y;
		y=last[x][y];
		--x;
	}
	return ret;
}

int main(){
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	scanf("%d%d%d",&N,&M,&K);
	for(int i=1;i<=N;++i) for(int j=1;j<=M;++j) scanf("%d",V[i]+j);
	putLL(bfs()+bfs());
}
