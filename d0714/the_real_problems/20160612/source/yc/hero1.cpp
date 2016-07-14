#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>
#include <bitset>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;

typedef double db;
typedef long long LL;
typedef pair< int, int > PII;
typedef pair< LL, LL > PLL;
typedef pair< db, db > PDD;

const db dInf = 1E90;
const LL lInf = ( LL ) 1E16;
const int Inf = 0x7FFFFFFF;
const int N = 25;

#define it iterator
#define rbg rbegin()
#define ren rend()
#define fdi( i, x ) for ( typeof( x.rbg ) i=x.rbg; i!=x.ren; ++i )
#define foi( i, x ) for ( typeof( x.begin() ) i=x.begin(); i!=x.end(); ++i )
#define fd( i, y, x ) for ( int i=( y )-1, LIM=x; i>=LIM; --i )
#define fo( i, x, y ) for ( int i=x, LIM=y; i<LIM; ++i )
#define mkp( A, B ) make_pair( A, B )
#define pub( x ) push_back( x )
#define pob( x ) pop_back( x )
#define puf( x ) push_front( x )
#define pof( x ) pop_front( x )
#define fi first
#define se second

int f[N][N][N];
int a[N][N];
int n, m, K;

void Read( int &x )
{
	x = 0; char ch = '\0';
	while ( ch<'0' || ch>'9' ) ch = getchar();
	while ( ch>='0' && ch<='9' )
		x = x * 10 + ch - '0', ch = getchar();
}

void update( int &x, LL v ) 
{ 
	if ( v > Inf ) return;
	if ( v < x ) x = v; 
}

void preprocessing()
{
	scanf( "%d%d%d", &n, &m, &K );
	fo ( i, 0, n ) fo ( j, 0, m )
		scanf( "%d", &a[i][j] );
	fill( f[0][0], f[n][0], Inf );
	fo ( i, 0, m ) fo ( j, i+1, m )
		f[0][i][j] = a[0][i] + a[0][j];
}

void solve()
{
	fo ( i, 0, n - 1 ) fo ( j, 0, m ) fo ( k, j + 1, m )
	{
		if ( f[i][j][k] == Inf ) continue;
		fo ( l, 0, m ) fo ( p, l+1, m )
			update( f[ i+1 ][l][p], LL( f[i][j][k] ) + a[ i+1 ][l] + a[ i+1 ][p] + K*abs( l-j ) + K*abs( p-k ) );
	}
	int ret = Inf;
	fo ( j, 0, m ) fo ( k, j + 1, m )
		update( ret, f[ n-1 ][j][k] );
	printf( "%d\n", ret );
}

int main()
{
	freopen( "hero.in", "r", stdin );
	freopen( "hero1.out", "w", stdout );

	preprocessing();
	solve();

	fclose( stdin ), fclose( stdout );
	return 0;
}

