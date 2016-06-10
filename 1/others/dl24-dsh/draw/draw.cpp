#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int n,m;
struct pt{
	int xseg,yseg;
};
int ta,tb,tc,td,jj,kk;
int ctx,cty,len,sum;
pt paper[2001][2001];
vector<int>xypt[2001];

int main(){
	freopen ("draw.in","r",stdin);
	freopen ("draw.out","w",stdout);
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=m;i++){
		cin>>ta>>tb>>tc>>td;
		if (ta==tc){
			if (tb>td) swap(tb,td);
			cty++;
			for (int j=tb;j<=td;j++){
				paper[ta][j].yseg=cty;
				
			}
		}
		if (tb==td){
			if (ta>tc) swap(ta,tc);
			ctx++;
			for (int j=ta;j<=tc;j++){
				paper[j][tb].xseg=ctx;
				
			}
		}
	}	
	
	for (int i=0;i<=n;i++){
		for (int j=0;j<=n;j++){
			if (paper[i][j].xseg&&paper[i][j].yseg){
				xypt[i].push_back(j);
			}
		}
	}
	
	for (int i=0;i<=n;i++){
		for (int j=0;j<xypt[i].size();j++){
			for (int k=j+1;k<xypt[i].size();k++){
				jj=xypt[i][j];
				kk=xypt[i][k];
				len=kk-jj;
				if (n-i<len) break;
				if (paper[i][jj].yseg==paper[i][kk].yseg){
					if (paper[i+len][jj].xseg==paper[i][jj].xseg){
						if (paper[i+len][kk].xseg==paper[i][kk].xseg){
							if (paper[i+len][jj].yseg==paper[i+len][kk].yseg&&paper[i+len][kk].yseg){
								sum++;
							}
						}
					}
				}
			}
		}
	}

	cout<<sum<<endl;

	return 0;
} 












