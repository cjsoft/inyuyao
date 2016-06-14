#include<iostream>
#include<stdio.h>
#include<vector>
#define mod 1000000007
using namespace std;
struct node{
	int t,w;
};
vector<node> G[2505];
int dis[2505],step[2505],vis[2505];
vector<int> d;
int dd[2505][2505];
vector<node> q;
int n,m,T;
int main(){
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	scanf("%d%d%d",&n,&m,&T);
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		G[u].push_back((node){v,w});
		G[v].push_back((node){u,w});
	}
	d.push_back(1);
	vis[1]=0;
	for(int i=2;i<=n;i++) vis[i]=2139062143;
	for(int i=0;i<d.size();i++){
		int now=d[i];
		for(int j=0;j<G[now].size();j++){
			int nex=G[now][j].t;
			if(vis[nex]==2139062143)
				vis[nex]=vis[now]+1,d.push_back(nex);
		}
	}
	//cout<<"ss"<<endl;
	d.clear();
	for(int i=2;i<=n;i++) dis[i]=2139062143;
	d.push_back(1);step[1]=0;
	for(int i=0;i<d.size();i++){
		int now=d[i];
		for(int j=0;j<G[now].size();j++){
			int nex=G[now][j].t,w=G[now][j].w;
			if(dis[nex]>dis[now]+w){
				dis[nex]=dis[now]+w;
				step[nex]=step[now]+1;
				d.push_back(nex);
			}
		}
	}
	for(int i=2;i<=n;i++)
		for(int j=vis[i];j<=step[i];j++)
			dd[i][j]=2139062143;
	dd[1][0]=0;
	q.push_back((node){1,0});
	for(int i=0;i<q.size();i++){
		node now=q[i];
		for(int j=0;j<G[now.t].size();j++){
			int nex=G[now.t][j].t,w=G[now.t][j].w;
			if(dd[nex][now.w+1]>dd[now.t][now.w]+w){
				dd[nex][now.w+1]=dd[now.t][now.w]+w;
				q.push_back((node){nex,now.w+1});
			}
		}
	}
		long long ans=0LL;
		for(int i=2;i<=n;i++)
			for(int j=vis[i];j<=step[i];j++){
				if(dd[i][j]==2139062143) continue;
				int l=-1,r=T;
				for(int k=vis[i];k<=step[i];k++){
					if(k==j||dd[i][k]==2139062143) continue;
					if(k<j) r=min(r,(dd[i][j]-dd[i][k])/(k-j));
					else l=max(l,(dd[i][j]-dd[i][k])/(k-j));
				}
				//cout<<l<<' '<<r<<' '<<dd[i][j]<<endl;
				if(l<r){
					long long shou=(long long)(l+1)*(long long)j+(long long)dd[i][j],mo=(long long)r*(long long)j+(long long)dd[i][j],shu=(long long)r-(long long)l;
				//	cout<<shou<<' '<<mo<<' '<<shu<<endl;
					ans=(ans+(shou+mo)%mod*shu%mod*500000004LL%mod)%mod;
				//	cout<<ans<<' '<<(shou+mo)%mod*shu%mod*500000004LL%mod<<endl;
				}
				}
		printf("%lld\n",ans);
}