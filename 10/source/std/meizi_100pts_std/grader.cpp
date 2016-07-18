#include<bits/stdc++.h>
#include"MXPOINT.h" 
using namespace std;
static int a[2010][2010];
static int js;
const string chg[21]={"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20"};
static char gh[100];
char* change(string x)
{
	for (int i=0;i<x.length();i++) gh[i]=x[i];
	gh[x.length()]='\0';
	return gh;
}
int ASK(int x,int y)
{
	js++;if (js>10000000) {printf("-2\n");exit(0);}
	if ((x<1)||(x>2000)||(y<1)||(y>2000)) return -1;
	return a[x][y];
}
int ASK2(int x,int y)
{
	if ((x<1)||(x>2000)||(y<1)||(y>2000)) return -1;
	return a[x][y];
}
bool check(pair<int,int> d)
{
	int x=d.first,y=d.second; 
	if (ASK2(x,y)<=ASK2(x-1,y)) return false;
	if (ASK2(x,y)<=ASK2(x+1,y)) return false;
	if (ASK2(x,y)<=ASK2(x,y-1)) return false;
	if (ASK2(x,y)<=ASK2(x,y+1)) return false;
	return true;
}
template<class T>inline void read(T&num){
	num=0;T f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')num=num*10+ch-'0',ch=getchar();
	num*=f;
}

int main()
{
	for (int t=1;t<=20;t++)
	{
		js=0;
		freopen(change("MXPOINT"+chg[t]+".in"),"r",stdin);
		for (int i=1;i<=2000;i++)
		for (int j=1;j<=2000;j++)
		read(a[i][j]);
		fclose(stdin);
		pair<int,int> p=FINDMXPOINT();//cout<<p.first<<' '<<p.second<<endl; 
		if (check(p)) printf("%d\n",js);
		else {printf("-1\n");return 0;}
	}
}
