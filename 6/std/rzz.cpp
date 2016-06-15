#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<ctime>
using namespace std;
const int M=0x20000035;

int n;
int value[256];
char str[55][55][111];
int A[55][55];

int random()
{
	int s=0;
	while((s^M)>s)
		s=s<<1|(rand()>>3&1);
	return s^M;
}

int mul(int a,int b)
{
	int s=0;
	while(b)
	{
		if(b&1)s=s^a;
		a<<=1;
		a=min(a,a^M);
		b>>=1;
	}
	return s;
}

void getpoly(char *s)
{
	char c;
	while(c=getchar(),c!='+'&&(c<'a'||c>'z')&&(c<'0'||c>'9'));
	*(s++)=c;
	while(c=getchar(),c=='+'||(c>='a'&&c<='z')||(c>='0'&&c<='9'))*(s++)=c;
	*(s++)='+';
	*s=0;
}

int getvalue(char *s)
{
	int r=0,t=1,len=strlen(s);
	for(int i=0;i<len;i++)
	{
		char c=s[i];
		if(c=='+')r^=t,t=1;
		else if(c>='a'&&c<='z')t=mul(t,value[c]);
		else t=c-'0';
	}
	return r;
}

bool Gauss()
{
	for(int i=1,j,k,x,y;i<=n;i++)
	{
		k=0;
		for(j=i;j<=n;j++)
			if(A[j][i]){k=j;break;}
		if(!k)return 1;
		for(j=1;j<=n;j++)
			swap(A[i][j],A[k][j]);
		x=A[i][i];
		for(j=i+1;j<=n;j++)
			if(y=A[j][i])
				for(k=i;k<=n;k++)
					A[j][k]=mul(A[j][k],x)^mul(A[i][k],y);
	}
	return 0;
}

bool check()
{
	for(char i='a';i<='z';i++)
		value[i]=random();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			A[i][j]=getvalue(str[i][j]);
	return Gauss();
}

int main()
{
	freopen("rzz.in","r",stdin);
	freopen("rzz.out","w",stdout);
	srand(time(0));
	int T;
	for(scanf("%d",&T);T--;)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				getpoly(str[i][j]);
		bool ans=1;
		for(int tim=20;tim--&&(ans=check());tim--);
		puts(ans?"Yes":"No");
	}
	return 0;
}

