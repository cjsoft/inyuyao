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
#include <cmath>
#include <map>
#include <set>
using namespace std;

typedef long double db;
typedef long long LL;
typedef pair< int, int > PII;
typedef pair< LL, LL > PLL;
typedef pair< db, db > PDD;

const db dInf = 1E90;
const LL lInf = ( LL ) 1E16;
const int Inf = 0x23333333;
const int N = 100005;

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

PII a[N], f[ N+N ];
int n, m;

void Read( int &x )
{
	x = 0; char ch = '\0';
	while ( ch<'0' || ch>'9' ) ch = getchar();
	while ( ch>='0' && ch<='9' )
		x = x * 10 + ch - '0', ch = getchar();
}

void update( int &x, int v ) { if ( v > x ) x = v; }

PII operator-( const PII &A, const PII &B ) { return PII( A.fi-B.fi, A.se-B.se ); }
PII operator+( const PII &A, const PII &B ) { return PII( A.fi+B.fi, A.se+B.se ); }
LL cross( const PII &A, const PII &B ) { return LL( A.fi )*B.se - LL( A.se )*B.fi; }

/*void convex()
{	
	sort( a, a + n );
	int tl = 0;
	fo ( i, 0, n )
	{
		while ( tl>1 && cross( f[ tl-1 ]-f[ tl-2 ], a[i]-f[ tl-2 ] )<=0 ) --tl;
		f[ tl++ ] = a[i];
	}
	m = tl;
	fd ( i, n-1, 0 )
	{
		while ( tl>m && cross( f[ tl-1 ]-f[ tl-2 ], a[i]-f[ tl-2 ] )<=0 ) --tl;
		if ( i ) f[ tl++ ] = a[i];
	}
	m = tl;
	fo ( i, 0, m ) f[ i+m ] = f[i];
}*/

void preprocessing()
{
	scanf( "%d", &n );
	fo ( i, 0, n ) scanf( "%d%d", &a[i].fi, &a[i].se );
	//convex();
}

LL getS( const PII &A, const PII &B, const PII &C )
{
	return cross( A, B ) + cross( B, C ) + cross( C, A );
}

void solve()
{
	LL ret = 0;
	/*fo ( i, 0, m )
	{
		int lcur = i, rcur = i + 1;
		fo ( j, i+1, i+m )
		{
			while ( lcur+1<j && getS( f[i], f[ lcur+1 ], f[j] )>=getS( f[i], f[lcur], f[j] ) ) ++lcur;
			while ( rcur+1<i+m && getS( f[j], f[ rcur+1 ], f[i] )>=getS( f[j], f[rcur], f[i] ) ) ++rcur;
			ret = max( ret, getS( f[i], f[lcur], f[j] ) + getS( f[j], f[rcur], f[i] ) );
		}
	}*/
	fo ( i, 0, n ) fo ( j, 0, n ) fo ( k, 0, n ) fo ( l, 0, n )
		ret = max( ret, getS( a[i], a[k], a[j] )+getS( a[j], a[l], a[i] ) );
	if ( ret & 1 ) printf( "%lld.5\n", ret >> 1 );
	else printf( "%lld.0\n", ret >> 1 );
}

int main()
{
	freopen( "area.in", "r", stdin );
	freopen( "area1.out", "w", stdout );

	preprocessing();
	solve();

	fclose( stdin ), fclose( stdout );
	return 0;
}

