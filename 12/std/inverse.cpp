#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int N=50010,M=65555;
int n,m,i,x,y,a[N],ans[N];
int g[N],v[N<<1],nxt[N<<1],ok[N<<1],ed,son[N],f[N],all,now;
inline void addedge(int x,int y){v[++ed]=y;nxt[ed]=g[x];ok[ed]=1;g[x]=ed;}
void findroot(int x,int y){
  son[x]=1;f[x]=0;
  for(int i=g[x];i;i=nxt[i])if(ok[i]&&v[i]!=y){
    findroot(v[i],x);
    son[x]+=son[v[i]];
    if(son[v[i]]>f[x])f[x]=son[v[i]];
  }
  if(all-son[x]>f[x])f[x]=all-son[x];
  if(f[x]<f[now])now=x;
}
namespace FFT{
struct comp{
  double r,i;comp(double _r=0,double _i=0){r=_r;i=_i;}
  comp operator+(const comp&x){return comp(r+x.r,i+x.i);}
  comp operator-(const comp&x){return comp(r-x.r,i-x.i);}
  comp operator*(const comp&x){return comp(r*x.r-i*x.i,r*x.i+i*x.r);}
  comp conj(){return comp(r,-i);}
}A[M],B[M];
int pos[M];
const double pi=acos(-1.0);
inline void FFT(comp a[],int n,int t){
  for(int i=1;i<n;i++)if(i<pos[i])swap(a[i],a[pos[i]]);
  for(int d=0;(1<<d)<n;d++){
    int m=1<<d,m2=m<<1;
    double o=pi*2/m2*t;comp _w(cos(o),sin(o));
    for(int i=0;i<n;i+=m2){
      comp w(1,0);
      for(int j=0;j<m;j++){
        comp&A=a[i+j+m],&B=a[i+j],t=w*A;
        A=B-t;B=B+t;w=w*_w;
      }
    }
  }
  if(t==-1)for(int i=0;i<n;i++)a[i].r/=n;
}
inline void mul(int n,int*a,int*b,int*c){
  int i,j,k;
  for(k=1;k<=n;k<<=1);k<<=1;
  j=__builtin_ctz(k)-1;
  for(i=0;i<k;i++)pos[i]=pos[i>>1]>>1|((i&1)<<j);
  for(i=0;i<k;i++)A[i]=i<=n?comp(a[i],b[i]):comp();
  FFT(A,k,1);
  for(i=0;i<k;i++){
    j=(k-i)&(k-1);
    B[i]=(A[i]*A[i]-(A[j]*A[j]).conj())*comp(0,-0.25);
  }
  FFT(B,k,-1);
  for(i=0;i<=n+n;i++)c[i]=(int)(B[i].r+0.5);
}
}
int dep,h[N],ga[N],gb[N],V[N<<1],NXT[N<<1],A[N],B[N],C[N];
inline void add(int&x,int y){V[++ed]=y;NXT[ed]=x;x=ed;}
void dfsa(int x,int y,int s,int ma,int ap){
  s+=a[x];
  if(ma<s)ma=s,ap=0;
  if(s==ma)ap++;
  if(s==ma&&s>=0){
    if(s>dep)dep=s;
    if(ap>h[s])h[s]=ap;
    add(ga[s],ap);
  }
  for(int i=g[x];i;i=nxt[i])if(ok[i]&&v[i]!=y)dfsa(v[i],x,s,ma,ap);
}
void dfsb(int x,int y,int s,int mi,int ap){
  s+=a[x];
  if(mi>s)mi=s,ap=0;
  if(s==mi)ap++;
  if(s==mi&&s<=0){
    if(-s>dep)dep=-s;
    if(ap>h[-s])h[-s]=ap;
    if(s==0)add(gb[0],ap);else add(gb[-s],ap-1);
  }
  for(int i=g[x];i;i=nxt[i])if(ok[i]&&v[i]!=y)dfsb(v[i],x,s,mi,ap);
}
inline void calc(int t){
  int i,j,m;
  for(i=0;i<=dep;i++){
    if(ga[i]&&gb[i]){
      m=h[i];
      for(j=0;j<=m;j++)A[j]=B[j]=0;
      for(j=ga[i];j;j=NXT[j])A[V[j]]++;
      for(j=gb[i];j;j=NXT[j])B[V[j]]++;
      FFT::mul(m,A,B,C);
      for(j=0;j<=m+m;j++)if(t>0)ans[j]+=C[j];else ans[j]-=C[j];
    }
    ga[i]=gb[i]=h[i]=0;
  }
}
void solve(int x){
  int i;
  dep=ed=0;
  dfsb(x,0,0,N,0);
  for(i=g[x];i;i=nxt[i])if(ok[i])dfsa(v[i],x,0,-N,0);
  if(gb[0])for(i=gb[0];i;i=NXT[i])ans[V[i]]++;
  calc(1);
  for(i=g[x];i;i=nxt[i])if(ok[i]){
    dep=ed=0;
    dfsa(v[i],x,0,-N,0);
    dfsb(v[i],x,a[x],a[x],1);
    calc(-1);
  }
  for(i=g[x];i;i=nxt[i])if(ok[i]){
    ok[i^1]=0;
    f[0]=all=son[v[i]];
    findroot(v[i],now=0);
    solve(now);
  }
}
int main(){
  freopen("inverse.in","r",stdin);freopen("inverse.out","w",stdout);
  scanf("%d",&n);
  for(ed=i=1;i<n;i++)scanf("%d%d",&x,&y),addedge(x,y),addedge(y,x);
  for(i=1;i<=n;i++){
    char s[5];
    scanf("%s",s);
    a[i]=s[0]=='('?1:-1;
  }
  f[0]=all=n;findroot(1,now=0);solve(now);
  scanf("%d",&m);
  while(m--)scanf("%d",&i),printf("%d\n",ans[i]);
  fclose(stdin);fclose(stdout);
  return 0;
}