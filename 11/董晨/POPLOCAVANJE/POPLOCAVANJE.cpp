#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define N 2000005
#define M 666233
#define ll unsigned long long
int n,m,k,l,t,ans,x,y,id;
ll h[N],a[N],s;
int f[N],g[N];
char st[N],ch[N];
int main(){
	freopen("POPLOCAVANJE.in","r",stdin);
	freopen("POPLOCAVANJE.out","w",stdout);
	scanf("%d",&n);
	scanf("%s",ch+1);
	h[0]=1;
	for (int i=1;i<=n;i++){
		h[i]=h[i-1]*M;
		a[i]=a[i-1]*M+ch[i]-'a';
	}
	scanf("%d",&m);
	while(m--){
		scanf("%s",st+1);
		l=strlen(st+1);
		s=0;
		for (int i=1;i<=l;i++)s=s*M+st[i]-'a';
		for (int i=l;i<=n;i++)if(f[i]<l)
			if(a[i]-a[i-l]*h[l]==s)f[i]=l;
	}
	for (int i=1;i<=n;i++)g[i-f[i]+1]++,g[i+1]--;
	for (int i=1;i<=n;i++){
		g[i]+=g[i-1];
		if(!g[i])ans++;
	}
	printf("%d\n",ans);
}
