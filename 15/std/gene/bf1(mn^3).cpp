#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
char ch;
bool ok;
void read(int &x){
	for (ok=0,ch=getchar();!isdigit(ch);ch=getchar()) if (ch=='-') ok=1;
	for (x=0;isdigit(ch);x=x*10+ch-'0',ch=getchar());
	if (ok) x=-x;
}
const int maxn=130010;
char s[maxn];
int n,q,l,r;
bool check(int l,int r){
	while (l<r&&s[l]==s[r]) l++,r--;
	return l>=r;
}
int calc(int l,int r){
	int res=0;
	for (int i=l;i<=r;i++) for (int j=i;j<=r;j++) if (check(i,j)) res++;
	return res;
}
int main(){
	read(n),read(q);
	scanf("%s",s+1);
	while (q--) read(l),read(r),printf("%d\n",calc(l,r));
	return 0;
}

