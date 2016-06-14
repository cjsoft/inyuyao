#include<cstdio>

int a,b,c;

#define begin int main(){
#define if if (
#define then )
#define do )
#define for for (
#define while while (
#define end }
#define exit(n) return n;
#define read(n) scanf("%d",&n)
#define writeln(n) printf("%d\n",n)
#define readln c++

begin
	read(a);
	read(b);
	a=a+b;
	writeln(a);
	readln;
	readln;
	exit(0);
end;