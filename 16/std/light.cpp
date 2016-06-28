#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define forE(i,x) for(int i=head[x];i!=-1;i=ne[i])
using namespace std;
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef pair<int,int> pin;
#define mk(a,b) make_pair(a,b)
#define lowbit(x) ((x)&(-(x)))
#define sqr(a) ((a)*(a))
#define clr(a) (memset((a),0,sizeof(a)))
#define ls ((x)<<1)
#define rs (((x)<<1)|1)
#define pb push_back
#define w1 first
#define w2 second
inline void read(int &x){
	x=0;int f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	x*=f;
}
inline void judge(){
	freopen("light.in","r",stdin);
	freopen("light.out","w",stdout);
}
/*******************************head*******************************/
const int maxn=4505;
typedef double ld;
int n,k;
ld f[maxn][maxn],cost[maxn][maxn];
int trans[maxn][maxn];
inline void GoDP(ld prv[],ld cur[],int tr[],int lq,int rq,int l,int r,int base){
	if(l>r)return;
	int mid=(l+r)>>1;
	rep(i,lq,min(mid-1,rq))
		if(cur[mid]<prv[i]+cost[mid+base][i+base]){
			cur[mid]=prv[i]+cost[mid+base][i+base];
			tr[mid]=i;
		}
	GoDP(prv,cur,tr,lq,tr[mid],l,mid-1,base);GoDP(prv,cur,tr,tr[mid],rq,mid+1,r,base);
}
struct Answer{
	vector<int> used;
	ld area;
	friend inline bool operator < (const Answer &a,const Answer &b){
		return a.area<b.area;
	}
};const ld inf=1<<29;
const ld pi=acos(-1.0);
inline Answer Solve(int base){
	rep(i,0,k-1)rep(j,0,n-1){
		f[i][j]=-inf;trans[i][j]=0;
	}f[0][0]=0;
	rep(i,1,k-1)GoDP(f[i-1],f[i],trans[i],0,n-1,0,n-1,base);
	rep(j,1,n-1)f[k-1][j]+=cost[n+base][j+base];
	int best=0;
	rep(i,1,n-1){
		if(f[k-1][i]>f[k-1][best])best=i;
	}Answer res;
	res.area=f[k-1][best];
	per(i,k-1,1){
		res.used.pb(best+base);best=trans[i][best];
	}res.used.pb(base);reverse(res.used.begin(),res.used.end());
	return res;
}
struct info{
	ld Ang;
	int id;
	friend inline bool operator < (const info &a,const info &b){return mk(a.Ang,a.id)<mk(b.Ang,b.id);}
}p[maxn];
inline bool check(vector<int> vec){
	rep(i,1,(int)(vec.size())-1) {
		if(p[vec[i]].Ang-p[vec[i-1]].Ang>=pi)return true;
	}
	return p[vec[0]+n].Ang-p[vec.back()].Ang>=pi;
}
inline void solve(){
	read(n);read(k);
	rep(i,0,n-1){
		scanf("%lf",&p[i].Ang);
		p[i].id=i+1;
		p[i+n]=p[i];p[i+n].Ang+=2*pi;
	}sort(p,p+2*n);
	rep(i,0,2*n-1)rep(j,i+1,2*n-1)
		cost[j][i]=sin(p[j].Ang-p[i].Ang);
	Answer ans=Solve(0);
	int lt=0,rt=n-1;
	rep(i,1,(int)(ans.used.size())-1){
		if(ans.used[i]-ans.used[i-1]<rt-lt){rt=ans.used[i];lt=ans.used[i-1];}
	}
	rep(i,lt,rt){
		Answer tmp=Solve(i%n);
		if(tmp.area>ans.area)ans=tmp;
	}
	if(check(ans.used)){
		puts("-1");
	}else{
		vector<info> vec;vec.clear();
		for(u32 i=0;i<ans.used.size();i++){
			int it=ans.used[i];
			vec.pb(p[it]);
			if(vec.back().Ang>=2*pi)vec.back().Ang-=2*pi;
		}
		sort(vec.begin(),vec.end());
		for(u32 i=0;i<vec.size();i++){
			info it=vec[i];
			printf("%d ",it.id);
		}puts("");
	}
}
int main(){
	judge();
//	int T;read(T);
	int T=1;
	while(T--)solve();
	return 0;
}



