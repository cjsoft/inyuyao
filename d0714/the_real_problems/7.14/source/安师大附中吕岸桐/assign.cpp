#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int N=30,Tab[]={0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1};

int n,k,cnt;

struct DfN{
int pos,x;
friend bool operator<(const DfN &A,const DfN &B){return A.x>B.x;}
}dfn[N],dfx[N];

bool cmp(const DfN &A,const DfN &B){return A.pos<B.pos;}

struct Node{
int l,r;
int A,B;
}peo[N];

void Read(int &x){
char ch;
while((ch=getchar())<'0' || ch>'9');
x=ch-'0';
while((ch=getchar())>='0' && ch<='9')x=x*10+ch-'0';
}

void Calc(){
for(int i=0;i<n;i++)dfx[i]=dfn[i];
sort(dfx,dfx+n);
sort(dfx,dfx+k,cmp);
for(int i=0;i<k;i++){
	if(!Tab[i])peo[dfx[i].pos].A++;
	else peo[dfx[i].pos].B++;
}
}

void dfs(int ix){
if(ix>=n){Calc();cnt++;return;}
for(int i=peo[ix].l;i<=peo[ix].r;i++){dfn[ix].x=i;dfn[ix].pos=ix;dfs(ix+1);}
}

int main(){
freopen("assign.in","r",stdin);
freopen("assign.out","w",stdout);
Read(n);
for(int i=0;i<n;i++)Read(peo[i].l);
for(int i=0;i<n;i++)Read(peo[i].r);
Read(k);
dfs(0);
for(int i=0;i<n;i++)printf("%lf %lf\n",(double)peo[i].A/cnt,(double)peo[i].B/cnt);
return 0;
}

