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
#include <ctime>
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

int l[N], r[N];
int n, m;

void Read( int &x )
{
	x = 0; char ch = '\0';
	while ( ch<'0' || ch>'9' ) ch = getchar();
	while ( ch>='0' && ch<='9' )
		x = x * 10 + ch - '0', ch = getchar();
}

void update( int &x, int v ) { if ( v > x ) x = v; }

int Rand() { return rand() * rand() + rand(); }

void preprocessing()
{
	n = 25;// m = 300;
	//int n = Rand() % 10 + 1, m = Rand() % n + 1;
	//m = Rand() % n + 1;
	m = 25;
	printf( "%d\n", n );
	fo ( i, 0, n ) l[i] = 1, r[i] = 1000;//Rand() % 1000 + 1, r[i] = Rand() % 1000 + 1;
	fo ( i, 0, n ) if ( l[i] > r[i] ) swap( l[i], r[i] );
	fo ( i, 0, n ) printf( "%d ", l[i] );
	printf( "\n" );
	fo ( i, 0, n ) printf( "%d ", r[i] );
	printf( "\n" );
	printf( "%d\n", m );
}

void solve()
{
}

int main()
{
	srand( time( 0 ) );
	freopen( "assign.in", "w", stdout );

	preprocessing();
	solve();

	fclose( stdin ), fclose( stdout );
	return 0;
}

