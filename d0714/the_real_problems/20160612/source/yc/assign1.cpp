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

void Read( int &x )
{
	x = 0; char ch = '\0';
	while ( ch<'0' || ch>'9' ) ch = getchar();
	while ( ch>='0' && ch<='9' )
		x = x * 10 + ch - '0', ch = getchar();
}

void update( int &x, int v ) { if ( v > x ) x = v; }

int l[N], r[N], scr[N];
db f[2][N], per;
PII a[N];
int n, m;

void preprocessing()
{
	scanf( "%d", &n ), per = 1;
	fo ( i, 0, n ) scanf( "%d", &l[i] ), --l[i];
	fo ( i, 0, n ) scanf( "%d", &r[i] ), per *= 1.0/( r[i]-l[i] );
	scanf( "%d", &m );
}

bool cmp( const PII &A, const PII &B )
{
	return A.se < B.se;
}

void search( int x )
{
	if ( x==n )
	{
		fo ( i, 0, n ) a[i] = mkp( -scr[i], i );
		sort( a, a + n );
		sort( a, a + m, cmp );
		fo ( i, 0, m ) f[ ( ( i+1 )>>1 )&1 ][ a[i].se ] += per;
		return;
	}
	fo ( i, l[x], r[x] )
	{
		scr[x] = i;
		search( x + 1 );
	}
}

int main()
{
	freopen( "assign.in", "r", stdin );
	freopen( "assign1.out", "w", stdout );

	preprocessing();
	search( 0 );
	fo ( i, 0, n ) printf( "%.6lf %.6lf\n", ( double ) f[0][i], ( double ) f[1][i] );

	fclose( stdin ), fclose( stdout );
	return 0;
}

