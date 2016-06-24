#include<bits/stdc++.h>
using namespace std;
typedef long long int64;
const int maxn=130010;
char s[maxn]; int n,m;

int64 manacher(char *s,int n){
    static int f[maxn],k; int64 ans=1;
    char u=s[-1],v=s[n]; s[-1]='$',s[n]=0;
    f[0]=0,k=0;
    for(int i=1;i<n;++i){
        if(k+f[k]>=i)
            f[i]=min(k+f[k]-i,f[2*k-i]);
        else f[i]=-1;
        while(s[i+f[i]+1]==s[i-f[i]-1]) ++f[i];
        if(i+f[i]>=k+f[k]) k=i; ans+=f[i]+1;
    }
    f[0]=-1,k=0;
    for(int i=1;i<n;++i){
        if(k+f[k]>=i)
            f[i]=min(k+f[k]-i,f[2*k-i]);
        else f[i]=-1;
        while(s[i+f[i]+1]==s[i-f[i]-2]) ++f[i];
        if(i+f[i]>=k+f[k]) k=i; ans+=f[i]+1;
    }
	s[-1]=u,s[n]=v; return ans;
}
int main(){
	scanf("%d%d%s",&n,&m,s+1);
	for(int i=1,l,r;i<=m;++i){
		scanf("%d%d",&l,&r);
		printf("%lld\n",manacher(s+l,r-l+1));
	}
	return 0;
}

