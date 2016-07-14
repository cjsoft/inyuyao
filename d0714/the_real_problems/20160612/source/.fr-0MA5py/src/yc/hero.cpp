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
const int N = 305;

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

int n, m, K, ret;

int num( int x, int y ) { return x * m + y + 2; }
namespace nwf
{
	const int N = ::N * ::N;
	const int M = N << 4;

	struct edge
	{
		int x, y, w, v, next;
	} e[M];
	int T = 2, remain = 2;
	int a[N], que[M], dis[N], pre[N];
	bool inque[N];

	void mke( int x, int y, int w, int v )
	{
		e[T].x = x, e[T].y = y, e[T].w = w, e[T].v = v, e[T].next = a[x], a[x] = T++;
		e[T].x = y, e[T].y = x, e[T].w = 0, e[T].v = -v, e[T].next = a[y], a[y] = T++;
	}

	bool spfa()
	{
		fill( dis, dis + num( n, m ), Inf ), inque[0] = 1, dis[0] = 0;
		for ( int hd=0, tl=1, x=0; hd!=tl; hd=( hd+1 )%M, x=que[hd] )
		{
			for ( int j=a[x]; j; j=e[j].next ) 
				if ( e[j].w && dis[ e[j].y ]>dis[x]+e[j].v )
				{
					dis[ e[j].y ] = dis[x] + e[j].v, pre[ e[j].y ] = j;
					if ( !inque[ e[j].y ] ) inque[ que[tl]=e[j].y ], tl=( tl+1 )%M;
				}
			inque[x] = 0;
		}
		return dis[1] < Inf;
	}

	void flow()
	{
		--remain, ret += dis[1];
		for ( int x=1; x; x=e[ pre[x] ].x )
			--e[ pre[x] ].w, ++e[ pre[x]^1 ].w;
	}

	void solve()
	{
		while ( remain && spfa() ) flow();
		printf( "%d\n", ret );
	}
}

void preprocessing()
{
	int v;
	scanf( "%d%d%d", &n, &m, &K );
	fo ( i, 0, n ) fo ( j, 0, m )
	{
		scanf( "%d", &v );
		nwf :: mke( num( i, j ), num( i+1, j ), 1, v );
		if ( j ) 
		{
			nwf :: mke( num( i, j-1 ), num( i, j ), 2, K );
			nwf :: mke( num( i, j ), num( i, j-1 ), 2, K );
		}
	}
	fo ( j, 0, m ) nwf :: mke( 0, num( 0, j ), 1, 0 );
	fo ( j, 0, m ) nwf :: mke( num( n, j ), 1, 1, 0 );
}

int main()
{
	freopen( "hero.in", "r", stdin );
	freopen( "hero.out", "w", stdout );

	preprocessing();
	nwf :: solve();

	fclose( stdin ), fclose( stdout );
	return 0;
}

