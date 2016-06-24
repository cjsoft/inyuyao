#include<bits/stdc++.h>
using namespace std;
const int maxc=30,maxlen=2010;
char s[maxc]; int ans[maxlen];
int c,l,anslen;

bitset<maxlen> f; int now[maxlen];
void dfs(int nowlen,int laststr){
	int rest=f.count();
	if(nowlen+rest>=anslen)
		return;
	if(!rest){
		memcpy(ans,now,sizeof(now));
		anslen=nowlen; return;
	}
	static const int z=pow(c,l-1);
	int newstr=(laststr%z)*c;
	if(nowlen<l-1){
		for(int k=0;k<c;++k,++newstr)
			now[nowlen]=k,dfs(nowlen+1,newstr);
		return;
	}
	for(int k=0;k<c;++k,++newstr)	
		if(f.test(newstr)){
			now[nowlen]=k;	
			f.reset(newstr);
			dfs(nowlen+1,newstr);
			f.set(newstr);
		}
	newstr=(laststr%z)*c;
	for(int k=0;k<c;++k,++newstr)
		if(!f.test(newstr))
			now[nowlen]=k,dfs(nowlen+1,newstr);
}

int main(){
	scanf("%d%d%s",&c,&l,s);
	anslen=pow(c,l)*l+1;
	for(int i=pow(c,l)-1;i>=0;--i)
		f.set(i);
	dfs(0,0);
	printf("%d\n",anslen);
	for(int i=0;i<anslen;++i)
		putchar(s[ans[i]]);
	putchar('\n');
	return 0;
}
