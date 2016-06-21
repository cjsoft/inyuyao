#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
int ch[2500050][26],fail[2500050],flag[2500050],tmp[300050],cnt=1;
char s1[300050],s[5050];
int n,m;
void init(int x){
	for(int i=0;i<26;i++) ch[x][i]=0;
	fail[x]=flag[x]=0;
}
void insert(int l){
	int now=1;
	for(int i=0;i<l;i++){
		if(!ch[now][s[i]-'a']) init(++cnt),ch[now][s[i]-'a']=cnt;
		now=ch[now][s[i]-'a'];
	}
	flag[now]=l;
}
int q[2500050];
void getfail(){
	int qin=0,qout=0;
	q[qout++]=1;
	for(int i=0;i<26;i++) ch[0][i]=1;
	while(qin<qout){
		int now=q[qin];qin++;
		for(int i=0;i<26;i++){
			if(!ch[now][i]) ch[now][i]=ch[fail[now]][i];
			else fail[ch[now][i]]=ch[fail[now]][i],q[qout++]=ch[now][i];
		}
	}
}
void AC(){
	int now=1;
	for(int i=0;i<n;i++){
		now=ch[now][s1[i]-'a'];
		//cout<<now<<endl;
		if(flag[now]) tmp[i-flag[now]+1]++,tmp[i+1]--;
	}
}
int main(){
	freopen("POPLOCAVANJE.in","r",stdin);
	freopen("POPLOCAVANJE.out","w",stdout);
	scanf("%d",&n);
	scanf("%s",s1);
	scanf("%d",&m);
	int tp=m/10;
	for(int i=1;i<=m;i++){
		scanf("%s",s);
		insert(strlen(s));
		if((tp&&i%tp==0)||i==m){
			getfail();
			//cout<<"ss"<<endl;
		//	for(int i=0;i<=cnt;i++) cout<<fail[i]<<endl;
			AC();
			cnt=1;
			init(1);
		}
	}
	int num=0,ans=0;
	for(int i=0;i<n;i++){
		//cout<<tmp[i]<<endl;
		num+=tmp[i];
		if(!num) ans++;
	}
	printf("%d\n",ans);
}
