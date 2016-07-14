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
const int Inf = 0x23333333;
const int N = 35;

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

void Read( int &x )
{
	x = 0; char ch = '\0';
	while ( ch<'0' || ch>'9' ) ch = getchar();
	while ( ch>='0' && ch<='9' )
		x = x * 10 + ch - '0', ch = getchar();
}

void update( int &x, int v ) { if ( v > x ) x = v; }

db f[N][N], g[N][N], ret[2][N];
int l[N], r[N];
int n, m;

void preprocessing()
{
	scanf( "%d", &n );
	fo ( i, 0, n ) scanf( "%d", &l[i] ), --l[i];
	fo ( i, 0, n ) scanf( "%d", &r[i] );
	scanf( "%d", &m );
}

void getres( int x, int scr )
{
	fill( f[0], f[n], 0 ), f[0][0] = 1;
	fo ( i, 0, n ) fo ( j, 0, m )
	{
		db pass = db( max( r[i]-max( ( i<x ? scr : scr+1 ), l[i] ), 0 ) )/( r[i]-l[i] );
		if ( i==x ) pass = 1;
		if ( !f[i][j] ) continue;
		f[ i+1 ][ j+1 ] += f[i][j] * pass;
		f[ i+1 ][j] += f[i][j] * ( 1-pass );
	}
	fill( g[0], g[n], 0 ), g[n][0] = 1;
	fd ( i, n, 0 ) fo ( j, 0, m )
	{
		db pass = db( max( r[i]-max( ( i<x ? scr : scr+1 ), l[i] ), 0 ) )/( r[i]-l[i] );
		if ( i==x ) pass = 1;
		g[i][ j+1 ] += g[ i+1 ][j] * pass;
		g[i][j] += g[ i+1 ][j] * ( 1-pass );
	}
	fo ( i, 0, n ) 
	{
		db pass = db( max( r[i]-max( ( i<x ? scr : scr+1 ), l[i] ), 0 ) )/( r[i]-l[i] );
		if ( i==x ) pass = 1;
		fo ( j, 0, m )
			ret[ ( ( j+1 )>>1 )&1 ][i] += f[i][j] * g[ i+1 ][ m-j-1 ] * pass / ( r[x]-l[x] );
	}
}

void solve()
{
	fo ( i, 0, n ) fo ( j, l[i], r[i] ) getres( i, j );
	fo ( i, 0, n ) printf( "%.6lf %.6lf\n", ret[0][i], ret[1][i] );
}

int main()
{
	freopen( "assign.in", "r", stdin );
	freopen( "assign.out", "w", stdout );

	preprocessing();
	solve();

	fclose( stdin ), fclose( stdout );
	return 0;
}

