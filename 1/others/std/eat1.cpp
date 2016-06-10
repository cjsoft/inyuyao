#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#define MASK 1000000007
#define MAXC 16
#define MAXD 16
#define MAXS 101
#define MAXN 1000000000000000000ll
#define MAXM 4
struct ev{long long x;int y,type;} cl[MAXC],dl[MAXD],el[MAXC+MAXD];
inline bool cmp(const ev &lhs,const ev &rhs){return lhs.x<rhs.x;}
int m,c,d,st[MAXS][MAXM],sn=0,tst[MAXM],tb[MAXM];
long long n;
struct mat
{
	int sz,a[MAXS][MAXS];
	mat(){sz=0,memset(a,0,sizeof(a));}
};
mat operator*(mat lhs,mat rhs)
{
	mat ret;ret.sz=lhs.sz;
	for(int i=0;i<ret.sz;i++) for(int j=0;j<ret.sz;j++) for(int k=0;k<ret.sz;k++) ret.a[i][k]=(ret.a[i][k]+1ll*lhs.a[i][j]*rhs.a[j][k])%MASK;
	return ret;
}
void dfs(int depth)
{
	if(depth==m)
	{
		for(int i=0;i<m;i++) st[sn][i]=tst[i];
		sn++;return;
	}
	if(!depth||tst[depth-1]==0||tst[depth-1]==3||tst[depth-1]==4||tst[depth-1]==6)
	{
		tst[depth]=0,dfs(depth+1);
		if(depth!=m-1) tst[depth]=1,dfs(depth+1);
		if(depth!=m-1) tst[depth]=2,dfs(depth+1);
		tst[depth]=6,dfs(depth+1);
	}
	else
	{
		tst[depth]=3,dfs(depth+1);
		tst[depth]=4,dfs(depth+1);
		if(depth!=m-1) tst[depth]=5,dfs(depth+1);
	}
}
inline bool checkbeg(int x)
{
	for(int i=0;i<m;i++) if(st[x][i]==1||st[x][i]==4||st[x][i]==6) return false;
	return true;
}
inline bool checkend(int x)
{
	for(int i=0;i<m;i++) if(st[x][i]==2||st[x][i]==3||st[x][i]==6) return false;
	return true;
}
inline bool checktr(int x1,int x2)
{
	for(int i=0;i<m;i++)
	{
		bool e1=(st[x1][i]==2||st[x1][i]==3||st[x1][i]==6),e2=(st[x2][i]==1||st[x2][i]==4||st[x2][i]==6);
		if(e1^e2) return false;
	}
	return true;
}
mat calc()
{
	mat ret;ret.sz=sn;
	for(int i=0;i<sn;i++) for(int j=0;j<sn;j++)
	{
		bool can=checktr(i,j);
		for(int k=0;k<m;k++) if(tb[k]==1&&st[j][k]) can=false;
		for(int k=0;k<m;k++) if(tb[k]==2&&!st[j][k]) can=false;
		ret.a[i][j]=can;
	}
	return ret;
}
mat powtable[64];
mat operator^(mat lhs,long long rhs)
{
	mat ret;ret.sz=lhs.sz;
	for(int i=0;i<ret.sz;i++) ret.a[i][i]=1;
	for(int cur=0;rhs;cur++,rhs>>=1) if(rhs&1) ret=ret*powtable[cur];
	return ret;
}
int main()
{
	freopen("eat.in","r",stdin);
	freopen("eat.out","w",stdout);
	scanf("%lld%d%d%d",&n,&m,&c,&d);
	for(int i=0;i<c;i++) scanf("%lld%d",&cl[i].x,&cl[i].y),el[i]=cl[i],el[i].y--,el[i].type=0;
	for(int i=0;i<d;i++) scanf("%lld%d",&dl[i].x,&dl[i].y),el[c+i]=dl[i],el[c+i].y--,el[c+i].type=1;
	std::stable_sort(el,el+c+d,cmp);
	dfs(0);
	mat g,ans;g.sz=ans.sz=sn;
	for(int i=0;i<sn;i++) ans.a[i][i]=1;
	for(int i=0;i<sn;i++) for(int j=0;j<sn;j++) if(checktr(i,j)) g.a[i][j]=1;
	powtable[0]=g;
	for(int i=1;i<64;i++) powtable[i]=powtable[i-1]*powtable[i-1];
	if(!(c+d)) ans=g^(n+1);
	else
	{
		int cur=0;
		long long last=0;
		while(cur<c+d)
		{
			long long cx=el[cur].x;
			memset(tb,0,sizeof(tb));
			while(cur<c+d&&el[cur].x==cx) tb[el[cur].y]=el[cur].type+1,cur++;
			ans=ans*(g^(cx-last-1))*calc(),last=cx;
		}
		ans=ans*(g^(n-last+1));
	}
	printf("%d\n",ans.a[0][0]);
	return 0;
}

