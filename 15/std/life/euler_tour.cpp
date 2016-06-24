#include<bits/stdc++.h>
using namespace std;
const int maxc=3010,maxn=6000010,maxm=12000010;
char s[maxc],ans[maxm]; int c,l;

int stk[maxm],from[maxm],cur[maxn],top;
int main(){
	scanf("%d%d%s",&c,&l,s);
	printf("%.0f\n",pow(c,l)+l-1);
	if(l>1){
		int tmp=pow(c,l-2),len=pow(c,l),now=len;
		memset(cur,0,sizeof(cur));
		for(stk[top=1]=0;top;){
			int x=stk[top],y,&i=cur[x];
			if(i<c){
				y=x%tmp*c+i,++top;
				stk[top]=y,from[top]=i;
				++i; continue;
			}
			if(top>1) ans[--now]=s[from[top]]; --top;
		}
		for(int i=0;i<l-1;++i)
			putchar(s[0]);
		for(int i=0;i<len;++i)
			putchar(ans[i]);
		putchar('\n');
	}
	else printf("%s\n",s);
	return 0;
}
