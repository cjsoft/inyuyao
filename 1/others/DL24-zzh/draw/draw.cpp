#include<cstdio>
#include<algorithm>

int n,m;
bool mup[2001][2001][2];
int mp[2001][2001][4];
int main(){
	freopen("draw.in","r",stdin);
	freopen("draw.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int tat=0;tat<m;tat++){
		int t1,t2,t3,t4;
		scanf("%d%d%d%d",&t1,&t2,&t3,&t4);
		if (t1>t3) std::swap(t1,t3);
		if (t2>t4) std::swap(t2,t4);
		if (t1==t3) for (int i=t2;i<t4;i++) mup[t1][i][0]=true;
		else for (int i=t1;i<t3;i++) mup[i][t2][1]=true;
	}
	for (int j=0;j<=n;j++){
		int now=0;
		for (int i=0;i<=n;i++){
			mp[i][j][0]=now;
			if (!mup[i][j][1]) now=0;
			else ++now;
		}
	}
	for (int j=0;j<=n;j++){
		int now=0;
		for (int i=n;i>0;i--){
			mp[i][j][2]=now;
			if (!mup[i-1][j][1]) now=0;
			else ++now;
		}
		mp[0][j][2]=now;
	}
	for (int i=0;i<=n;i++){
		int now=0;
		for (int j=0;j<=n;j++){
			mp[i][j][3]=now;
			if (!mup[i][j][0]) now=0;
			else ++now;
		}
	}
	for (int i=0;i<=n;i++){
		int now=0;
		for (int j=n;j>0;j--){
			mp[i][j][1]=now;
			if (!mup[i][j-1][0]) now=0;
			else ++now;
		}
		mp[i][0][1]=now;
	}
	int ans=0;
	for (int k=1;k<=n;k++){
		for (int i=0;i<=n-k;i++) for (int j=0;j<=n-k;j++){
			ans+=(mp[i][j][1]>=k)&&(mp[i][j][2]>=k)&&(mp[i+k][j+k][0]>=k)&&(mp[i+k][j+k][3]>=k);
		}
	}/*
	for (int i=0;i<=n;i++){
		for (int j=0;j<=n;j++) printf("%d,%d,%d,%d ",mp[i][j][0],mp[i][j][1],mp[i][j][2],mp[i][j][3]);
		printf("\n");
	}*/
	printf("%d",ans);
	return 0;
}

