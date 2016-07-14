#include<bits/stdc++.h>
using namespace std;
bool f[30000000];
int N,M,K,S,T,n,smg;
int t[310][310];
int d[200010],p[200010],q[200010];
bool inq[200010];
inline int eid(int xa,int xb,int ya,int yb){
	if(xa==S)return smg+yb;
	else if(ya==T)return smg+M+xb;
	else if(xa==ya&&xb==yb)return (xa-1)*M+xb;
	else return xa*M*M+xb*M+yb;
}
inline int abs(int x){return x>0?x:-x;}
inline int cost(int e){
	if(e>smg)return 0;
	else if(e<=N*M)return t[(e-1)/M+1][(e-1)%M+1];
	else return K*abs((((e-M-1)%(M*M))/M+1)-(((e-M-1)%(M*M))%M+1));
}
long long ans;
int Q[5000010],fr,re;
bool flow(){
	memset(d,0x3f,sizeof(d));
	d[S]=0;
	fr=1,re=0;
	Q[++re]=S;
	inq[S]=1;
	while(fr<=re){
		int h=Q[fr++];
		inq[h]=0;
		int a=((h+1)/2-1)/M+1,b=((h+1)/2-1)%M+1;
		 if(h==S){
		for(int i=1;i<=M;i++){
		int j=i*2-1,e=eid(h,0,1,i),z;
		if(f[e]==0&&(z=d[h]+cost(e))<d[j]){
					d[j]=z;
			p[j]=h;
			q[j]=e;
			if(!inq[j]){
				Q[++re]=j;
				inq[j]=1;
			}
			}
		}
		}
		else if(h==T){
			for(int i=1;i<=M;i++){
			int j=((N-1)*M+i)*2,e=eid(N,i,h,0),z;
			if(f[e]==1&&(z=d[h]-cost(e))<d[j]){
			d[j]=z;
			p[j]=h;
			q[j]=-e;
			if(!inq[j]){
				Q[++re]=j;
				inq[j]=1;
			}
			}
		}
		}
		else if(h%2){
			int e=eid(a,b,a,b),j=h+1,z;
			if(f[e]==0&&(z=d[h]+cost(e))<d[j]){
					d[j]=z;
			p[j]=h;
			q[j]=e;
			if(!inq[j]){
				Q[++re]=j;
				inq[j]=1;
			}
			}
			if(h>M*2){
				for(int i=1;i<=M;i++){
					int e=eid(a-1,i,a,b),j=((a-2)*M+i)*2,z;
					if(f[e]==1&&(z=d[h]-cost(e))<d[j]){
					d[j]=z;
					p[j]=h;
					q[j]=-e;
					if(!inq[j]){
						Q[++re]=j;
						inq[j]=1;
					}
				}
				}
			}
			else{
				int e=eid(S,0,h,0),j=S,z;
				if(f[e]==1&&(z=d[h]-cost(e))<d[j]){
					d[j]=z;
					p[j]=h;
					q[j]=-e;
					if(!inq[j]){
						Q[++re]=j;
						inq[j]=1;
					}
				}
			}
		}
		else{
			int e=eid(a,b,a,b),j=h-1,z;
			if(f[e]==1&&(z=d[h]-cost(e))<d[j]){
			d[j]=z;
			p[j]=h;
			q[j]=-e;
			if(!inq[j]){
				Q[++re]=j;
				inq[j]=1;
			}
			}
			if(h<=(N-1)*M*2){
				for(int i=1;i<=M;i++){
					int e=eid(a,b,a+1,i),j=(a*M+i)*2-1;
					if(f[e]==0&&d[h]+cost(e)<d[j]){
					d[j]=d[h]+cost(e);
					p[j]=h;
					q[j]=e;
					if(!inq[j]){
						Q[++re]=j;
						inq[j]=1;
					}
				}
				}
			}
			else{
				int e=eid(a,b,T,0),j=T,z;
				if(f[e]==0&&(z=d[h]+cost(e))<d[j]){
					d[j]=z;
					p[j]=h;
					q[j]=e;
					if(!inq[j]){
						Q[++re]=j;
						inq[j]=1;
					}
				}
			}
		}
	}
	if(d[T]>1000000000)return 0;
	int pos=T;
	while(pos!=S){
		int x=abs(q[pos]);
		f[x]^=1;
		ans+=x/q[pos]*cost(x);
		pos=p[pos];
	}
	return 1;
}
int main(){
	freopen("hero.in","r",stdin);
	freopen("hero.out","w",stdout);
	scanf("%d%d%d",&N,&M,&K);
	int x;
	for(int i=1;i<=N;i++)
	for(int j=1;j<=M;j++)
	scanf("%d",&t[i][j]);
	n=2*N*M+2,S=n-1,T=n,smg=N*M*M+M+1;
	flow();flow();
	printf("%lld\n",ans);
	return 0;
}
