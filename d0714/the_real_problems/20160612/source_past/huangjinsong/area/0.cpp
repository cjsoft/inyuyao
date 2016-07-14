#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
typedef long long LL;
inline int read()
{
	int x=0;bool f=0;char c=getchar();
	for (;c<'0'||c>'9';c=getchar()) f=c=='-'?1:0;
	for (;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
	return f?-x:x;
}
