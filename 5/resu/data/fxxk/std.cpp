#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
using namespace std;

const int maxn=1100;
int f[maxn],e[maxn],s[maxn];
bool chk[maxn];

int fa(int x){return f[x]==x?x:(f[x]=fa(f[x]));}
void cmb(int a,int b){
    if(a&&b&&a!=b) (s[a]>s[b])?(f[b]=a,s[a]+=s[b]):(f[a]=b,s[b]+=s[a]);
}
bool enem(int a,int b){
    a=fa(a);b=fa(b);
    if(a==b)return 0;
    cmb(e[a],b); cmb(e[b],a);
    a=fa(a);b=fa(b);
    e[a]=b; e[b]=a; return 1;
}
int s1[maxn],s2[maxn],s1x[maxn],s2x[maxn],sel[maxn],c;
bool kk[maxn][maxn],A[maxn][maxn];
int sc[maxn],sf[maxn],ans;

void dfs(int x,int p1,int p2){
    if(kk[p1][p2])return; kk[p1][p2]=1;
    if(x==c){
        if(p1*p2>ans){
            ans=p1*p2;
            for(int i=0;i<c;++i)sc[s1x[i]]=sel[i],sc[s2x[i]]=!sel[i];
        }
    }else{
        sel[x]=0; dfs(x+1,p1+s1[x],p2+s2[x]);
        sel[x]=1; dfs(x+1,p1+s2[x],p2+s1[x]);
    }
}

void dit(){
    int n;scanf("%d",&n);
    for(int i=1;i<=n;++i)f[i]=i,e[i]=0,chk[i]=0,s[i]=1;
    bool ok=1;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j){
            int t; scanf("%d",&t); A[i][j]=t;
            if(i<=j && t)ok=ok && enem(i,j);
        }
    if(!ok)printf("-1\n");
    else{
        c=0;
        for(int i=1;i<=n;++i){
            int x=fa(i);
            if(!chk[x]){
                int u=fa(e[x]);
                chk[x]=chk[u]=1;
                s1[c]=s[x];s2[c]=s[u];
                s1x[c]=x;s2x[c]=u;++c;
                //printf("DBG %d %d (%d %d)\n",s[x],s[u],x,u);
            }
        }
        for(int i=0;i<=n;++i)
            for(int j=0;j<=n;++j)kk[i][j]=0;
        ans=-100;dfs(0,0,0);
        //for(int i=1;i<=n;++i)printf(i==n?"%d\n":"%d ",sc[fa(i)]);
        for(int i=1;i<=n;++i)sf[i]=sc[fa(i)];
        int sumans=0;
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                sumans += ((sf[i]^sf[j]) && !A[i][j]);
        printf("%d\n",sumans);
    }
}
int main() {
    int T;scanf("%d",&T);while(T--)dit();
}
