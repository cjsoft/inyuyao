#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
using namespace std;
typedef long long LL;
inline int read()
{
	int x=0;bool f=0;char c=getchar();
	for (;c<'0'||c>'9';c=getchar()) f=c=='-'?1:0;
	for (;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	return f?-x:x;
}

int rd(int x)
{
	if (x<=0) return 0;
	return rand()%x+1;
}

int main()
{
	freopen("1.in","w",stdout);
	srand(time(0));
	int n=rd(30);
	if (n<4) n=4;
	n=6;
	cout<<n<<endl;
	for (int i=1;i<=n;i++) 
	{
		int x=rd(6),y=rd(6);
		cout<<x<<" "<<y<<endl;
	}
	return 0;
}
