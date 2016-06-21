#include<cstdio>
#define N 256
int n,type,i,x,f[N][N],g[N][N],v[N],ans,cnt;char op[9];
inline int fun(int x,int y){
  if(op[0]=='a')return x&y;
  if(op[0]=='o')return x|y;
  return x^y;
}
inline void add(int x){
  int A=x>>8,B=x&255;
  v[A]=1;
  for(int i=0;i<N;i++){
    int k=fun(i,B);
    if(k>f[A][i])f[A][i]=k,g[A][i]=1;else if(k==f[A][i])g[A][i]++;
  }
}
inline void ask(int x){
  int A=x>>8,B=x&255;
  ans=cnt=0;
  for(int i=0;i<N;i++)if(v[i]){
    int k=fun(i,A)<<8|f[i][B];
    if(k>ans)ans=k,cnt=g[i][B];else if(k==ans)cnt+=g[i][B];
  }
}
int main(){
  freopen("binary.in","r",stdin);freopen("binary.out","w",stdout);
  scanf("%d%s%d",&n,op,&type);
  for(i=0;i<n;i++){
    scanf("%d",&x);
    if(i){
      ask(x);
      if(type)printf("%d %d\n",ans,cnt);else printf("%d\n",ans);
    }
    add(x);
  }
  fclose(stdin);fclose(stdout);
  return 0;
}