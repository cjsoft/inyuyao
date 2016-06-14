#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<stack>
using namespace std;
char s[1000050];int n,k;
int sa[1000050],rank[1000050],tmp[1000050],height[1000050];
int cmp(int x,int y){
	if(rank[x]!=rank[y]) return rank[x]<rank[y];
	int rx=x+k<=n?rank[x+k]:-1,ry=y+k<=n?rank[y+k]:-1;
	return rx<ry;
}
void getsa(){
	for(int i=0;i<=n;i++) sa[i]=i,rank[i]=i<n?s[i]-'a':-1;
	for(k=1;k<=n;k<<=1){
		sort(sa,sa+1+n,cmp);
		tmp[sa[0]]=0;
		for(int i=1;i<=n;i++)
			tmp[sa[i]]=tmp[sa[i-1]]+(cmp(sa[i-1],sa[i])?1:0);
		for(int i=0;i<=n;i++) rank[i]=tmp[i];
	}
}
void getheight(){
	int kk=0,j;
	for(int i=0;i<n;height[rank[i++]]=kk)
		for(kk?kk--:0,j=sa[rank[i]-1];s[i+kk]==s[j+kk];kk++);
}
stack<int> st;
int main(){
	freopen("sub.in","r",stdin);
	freopen("sub.out","w",stdout);
	scanf("%s",s);
	n=strlen(s);
	getsa();getheight();
	long long ans=0;height[n]=0;
	for(int i=0;i<=n;i++){
		while(!st.empty()&&height[st.top()]>height[i]){
			ans=max(ans,(long long)(i-st.top()+1)*(long long)height[st.top()]);
			st.pop();
		}
		st.push(i);
	}
	printf("%lld\n",ans);
}