#include<bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define rep(i,a,n) for(int i=(a);i<=(n);++i)
#define SZ(x) ((int)(x).size())
typedef pair<int,int> pii;
const int DX[]={-1,1,0,0},DY[]={0,0,1,-1};
const int N=55,M=111111;
int l,m,n,t,C,x,y,z;
int a[N][N],tmp[N][N],sv[N][N];
enum MODENUM{Full,Score}MODE;
FILE *msg; 
void get(int &p){
	int x;for(x=getchar();(x<'0'||x>'9')&&x!='|'&&x!='-'&&x!='.'&&x!=' ';x=getchar());
	if(x=='|'||x=='-')p=1;else if(x=='.'||x==' ')p=0;else if(x=='0')p=-1;else p=x-'0';
}
queue<pii>Q;
int bo,err;
void dfs1(int x,int y,int z){
	if(x<1||x>2*n-1||y<1||y>2*m-1)return;if(!a[x][y])return;
	if(a[x][y]==-1)bo=0;
	tmp[x+DX[z]*2][y]=a[x][y];a[x][y]=0;
	rep(i,0,3)dfs1(x+DX[i],y+DY[i],z);
	if(a[x+DX[z]*2][y])Q.push(mp(x+DX[z]*2,y));
}
void dfs2(int x,int y){
	if(x<1||x>2*n-1||y<1||y>2*m-1)return;if(!a[x][y])return;
	if(tmp[x][y])return;tmp[x][y]=1;
	rep(i,0,3)dfs2(x+DX[i],y+DY[i]);
	dfs2(x,y+2);
}
void move(int x,int y,int z){
	if(!a[2*x-1][2*y-1]){puts("No block in this place!");err=1;return;}
	bo=1;
	rep(i,1,2*n-1)rep(j,1,2*m-1)tmp[i][j]=0,sv[i][j]=a[i][j];
	while(Q.size())Q.pop(); 
	dfs1(x*2-1,y*2-1,z);
	while(Q.size()){pii k=Q.front();Q.pop();dfs1(k.X,k.Y,z);}
	if(!bo){rep(i,1,2*n-1)rep(j,1,2*m-1)a[i][j]=sv[i][j];puts("Move Error!");err=1;return;}
	rep(i,1,2*n-1)rep(j,1,2*m-1)if(tmp[i][j])a[i][j]=tmp[i][j];
	
	while(1){
		rep(i,1,2*n-1)rep(j,1,2*m-1)tmp[i][j]=0;
		rep(i,1,2*n-1)rep(j,1,2*m-1)if(a[i][j]==-1)dfs2(i,j);
		int bo=0;
		rep(j,1,2*m-1)rep(i,1,2*n-1)if(a[i][j]&&!tmp[i][j])bo=1,a[i][j-1]=a[i][j],a[i][j]=0;
		if(!bo)break;
	}
	
	rep(i,1,2*n-1)rep(j,1,2*m-1)if((i&1)&&(j&1))
		rep(k,0,3)if(a[i][j]>=1&&a[i][j]<=5&&a[i][j]==a[i+DX[k]*2][j+DY[k]*2]){
			a[i+DX[k]][j+DY[k]]=1;
	}
	if(MODE!=Score)puts("Successs!");
}
void print(FILE *x=stdout){
	rep(i,1,2*m-1){
		rep(j,1,2*n-1)if((i&1)&&(j&1)){
			if(a[j][2*m-1-i+1]==0)fprintf(x,".");
			else if(a[j][2*m-1-i+1]==-1)fprintf(x,"0");
			else fprintf(x,"%c",a[j][2*m-1-i+1]+'0');
		}else{
			fprintf(x,"%c",a[j][2*m-1-i+1]?i&1?'-':'|':(i&1)&&(j&1)?'.':' ');
		}fprintf(x,"\n");
	}
}
set<int>S[9];
void dfs3(int x,int y,int z){
	if(x<1||x>2*n-1||y<1||y>2*m-1)return;if(a[x][y]<1||a[x][y]>5)return;
	if(tmp[x][y])return;tmp[x][y]=1;
	S[a[x][y]].insert(z);
	rep(i,0,3)if(a[x+DX[i]*2][y+DY[i]*2]==a[x][y])dfs3(x+DX[i]*2,y+DY[i]*2,z);
}
int par;
int check(){
	par=0;
	rep(i,1,5)S[i].clear();int cnt=0;
	rep(i,1,2*n-1)rep(j,1,2*m-1)tmp[i][j]=0;
	rep(i,1,2*n-1)rep(j,1,2*m-1)if((i&1)&&(j&1)&&a[i][j]>=1&&a[i][j]<=5)dfs3(i,j,++cnt);
	cnt=0;rep(i,1,5)if(SZ(S[i]))cnt+=SZ(S[i])-1;
	if(cnt==1)par=1;
	return cnt==0;
}
int work(string IN,string OUT){
	err=0;
	freopen(IN.c_str(),"r",stdin);
	scanf("%d%d",&m,&n);rep(i,1,2*m-1)rep(j,1,2*n-1)get(a[j][2*m-1-i+1]);
	rep(i,1,2*n-1)rep(j,1,2*m-1)if((i&1)&&(j&1))
		rep(k,0,3)if(a[i][j]>=1&&a[i][j]<=5&&a[i][j]==a[i+DX[k]*2][j+DY[k]*2]){
			a[i+DX[k]][j+DY[k]]=1;
	}
	freopen(OUT.c_str(),"r",stdin);
	C=0;
	fprintf(msg,"Testing %s %s\n",IN.c_str(),OUT.c_str());
	print(msg);
	while(scanf("%d%d%d",&x,&y,&z)==3){
		++C;if(MODE!=Score)printf("operation %d: ",C);
		fprintf(msg,"after operation %d:\n",C);
		if(x<1||x>n||y<1||y>m||z!=0&&z!=1){puts("Argument Error!");return 0;}
		move(x,y,z);
		if(err)return 0;
		print(msg);
		if(check())break;
	}
	rep(i,1,3)fprintf(msg,"\n");
	if(MODE!=Score){
		puts("");
		if(check()){printf("Congratulations!\nYou completed the game in %d steps.\n",C);return 0;}
		else if(par)printf("WA but you can get 1 score.\n");
		else printf("WA\n");
		puts("\nFinal State:");
		print();
	}else{
		if(check())printf("OK, step:%d\n",C);
		else if(par)puts("Scored 1pt");
		else printf("WA\n");
	}
}
int main(int argc,char **argv){
	msg=fopen("report.out","w");
	if(argc==1){
		MODE=Score;
		rep(i,1,20){
			stringstream sin,sout;sin<<"C"<<i<<".in";sout<<"C"<<i<<".out";
			printf("test %d: ",i);
			work(sin.str(),sout.str());
		}
	}
	if(argc==2){
		MODE=Full;
		stringstream sin,sout;sin<<"C"<<argv[1]<<".in";sout<<"C"<<argv[1]<<".out";
		work(sin.str(),sout.str());
	}
	if(argc==3){
		MODE=Full;
		work(argv[1],argv[2]);
	}
	return 0;
}
