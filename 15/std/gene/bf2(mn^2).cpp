#include<bits/stdc++.h>
using namespace std;
const int maxn=130010;
char s[maxn]; int n,m;

int calc(int x,int y){
	int ans=0;
	for(int i=x;i<=y;++i){
		for(int l=i,r=i;l>=x && r<=y;--l,++r)
			if(s[l]==s[r]) ++ans; else break;
		for(int l=i-1,r=i;l>=x && r<=y;--l,++r)
			if(s[l]==s[r]) ++ans; else break;
	}
	return ans;
}
int main(){
	scanf("%d%d%s",&n,&m,s+1);
	for(int i=1,l,r;i<=m;++i){
		scanf("%d%d",&l,&r);
		printf("%d\n",calc(l,r));
	}
	return 0;
}

