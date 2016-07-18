#include<bits/stdc++.h>
#include"MXPOINT.h" 
using namespace std;
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define re(i,a,b) for(int i=(a);i<(b);i++)
#define repd(i,a,b) for(int i=(a);i>=(b);i--)
#define w1 first
#define w2 second
typedef pair<int,int> pa;
const int N=2e3+5,INF=2e9;
int f[N][N];
int ask(int x,int y){
	if(!f[x][y])f[x][y]=ASK(x,y);;
	return f[x][y];
}
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
pa st[N];
int tmp=3;
pair<int,int>FINDMXPOINT(){
	 memset(f,0,sizeof(f));int len=2e3;srand(487448^(tmp*tmp)); 
	 int nx,ny,mx=-INF;
	 rep(i,1,(int)len*1.3){
	 	int x=rand()%len+1,y=rand()%len+1;
	 	while(x>400&&x<1600&&y>400&&y<1600){
		 x=rand()%len+1,y=rand()%len+1;
		 	if(rand()&1)break;
		 } 
	 	if(ask(x,y)>mx)mx=ask(x,y),nx=x,ny=y;
	 }
	 rep(i,0,2001)f[i][0]=f[i][2001]=f[0][i]=f[2001][i]=-INF;
	
	 if(ask(nx+1,ny)<mx&&ask(nx,ny+1)<mx&&ask(nx-1,ny)<mx&&ask(nx,ny-1)<mx)return pa(nx,ny);
	 while(1){
	 	swap(dx[0],dx[3]);swap(dy[0],dy[3]);
	 	swap(dx[2],dx[1]);swap(dy[2],dy[1]);
	 	swap(dx[1],dx[3]);swap(dy[1],dy[3]);
	 	int top=0;
	 	rep(i,0,3){
	 		int x=nx+dx[i],y=ny+dy[i];
	 		if(x<1||y<1||x>len||y>len)continue;
	 		if(ask(x,y)>ask(nx,ny))st[++top]=pa(x,y);
	 		if(top==2)break; 
		}
		if(top==0)return pa(nx,ny);
		if(top==1){
			rep(i,1,4){
				int x=nx,y=ny;
				x=nx+(((rand()%71)&1)?1:-1)*rand()%10;
				y=ny+(((rand()%71)&1)?1:-1)*rand()%10;
				while(x<1||y<1||x>len||y>len){
				//	x=nx+((rand()&1)?1:-1)*((rand()&1)*2);
				//	y=ny+((rand()&1)?1:-1)*((rand()&1)*2);
					
				x=nx+(((rand()%71)&1)?1:-1)*rand()%10;
				y=ny+(((rand()%71)&1)?1:-1)*rand()%10;
				}
	 			if(ask(x,y)>ask(nx,ny))st[++top]=pa(x,y);
	 			if(top==3)break;
			}
		}
		rep(i,1,top){
			int x=st[i].w1,y=st[i].w2;
	 		if(ask(x,y)>mx)mx=ask(x,y),nx=x,ny=y;	
		}continue;
	 }
}
