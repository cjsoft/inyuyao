#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>

#define sqr(x) ((x) * (x))
#define minn(x,y) (x=(y)<(x)?(y):(x))
#define maxx(x,y) (x=(y)>(x)?(y):(x))
#define pluss(x,y) (x+=(y),x%=mod)

using namespace std;

typedef	long long	int64;


FILE	*Finn, *Fout, *Fstd, *Fres;

const	int	maxn = 100005;

int	n,m,K,first[100001],where[2000001],l,v[2000001],next[2000001],type[2000001],c[2000001],dist[100001];
bool b[100001],B[100001];

void	Return(double p, char* s)
{
	fprintf(Fres, "%.7lf\n%s\n", p+1e-6, s);
	exit(0);
}

int	main(int args, char** argv)
{
	Finn = fopen(argv[1], "r");
	Fstd = fopen(argv[2], "r");
	Fout = fopen(argv[3], "r");
	Fres = fopen(argv[4], "w");
	
	double std; 
	fscanf(Fstd,"%lf", &std);
	double player;
	fscanf(Fout,"%lf", &player);
	if (abs(player - std) / max(1.0, std) < 1e-4) Return(1.0,"ÕýÈ·");
	else Return(0,"´íÎó");
} 
