#include<cstdio>
const int N=300005,M=N*20*3;
int n,m,type,ans,i,x,y,z,d[N],nxt,T[N],v[M],l[M],r[M],tot;
int change(int x,int a,int b,int c,int p){
  int y=++tot;
  if(a==b){
    v[y]=p;
    return y;
  }
  int mid=(a+b)>>1;
  if(c<=mid)l[y]=change(l[x],a,mid,c,p),r[y]=r[x];else l[y]=l[x],r[y]=change(r[x],mid+1,b,c,p);
  return y;
}
int ask(int x,int a,int b,int c){
  if(a==b)return v[x];
  int mid=(a+b)>>1;
  return c<=mid?ask(l[x],a,mid,c):ask(r[x],mid+1,b,c);
}
int main(){
  freopen("string.in","r",stdin);freopen("string.out","w",stdout);
  scanf("%d%d%d",&n,&m,&type);
  for(i=1;i<=n;i++){
    scanf("%d%d",&x,&y);
    if(type)x^=ans,y^=ans;
    d[i]=d[x]+1;
    z=ask(T[x],0,n,x);
    nxt=ask(z,1,m,y);
    printf("%d\n",ans=d[i]-d[nxt]);
    T[i]=change(T[x],0,n,x,change(z,1,m,y,i));
    T[i]=change(T[i],0,n,i,ask(T[i],0,n,nxt));
  }
  fclose(stdin);fclose(stdout);
  return 0;
}