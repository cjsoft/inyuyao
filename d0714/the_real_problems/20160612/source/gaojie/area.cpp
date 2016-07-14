#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define MEM(x, y) memset(x, y, sizeof(x))
#define cmin(x, y) ((x) = min((x), (y)))
#define cmax(x, y) ((x) = max((x), (y)))
#define X first
#define Y second

using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned int UI;
typedef unsigned long long ULL;
typedef pair<int, int> PI;

const int INF = 0x7fffffff;
const LL INF_LL = 0x7fffffffffffffffLL;
const LL MOD = 1000000007;
const LD eps = 1e-8;

template<typename T> void read(T& a){
	a = 0; char c; bool f = 0;
	while (!isdigit(c = getchar())) if (c == '-') f = 1;
	do a = a * 10 + c - '0'; while (isdigit(c = getchar()));
	if (f) a = -a;
}

const int MAXN = 100100;

struct Point{
	LL x, y;
	Point(){}
	Point(LL _x, LL _y):x(_x), y(_y){}
}A[MAXN];
inline Point operator -(const Point &a, const Point &b){return Point(a.x - b.x, a.y - b.y);}
inline LL dot(const Point &a, const Point &b){return a.x * b.x + a.y * b.y;}
inline LL cross(const Point &a, const Point &b){return a.x * b.y - a.y * b.x;}
inline LL cross(const Point &a, const Point &b, const Point &O){return cross(a - O, b - O);}
bool cmp(const Point &a, const Point &b){
	LL t = cross(a, b);
	return t != 0 ? t < 0 : dot(a, a) < dot(b, b);
}
Point tmp;
int Graham(Point *A, int N){
	int id0 = 1;
	rep(i, 2, N) if (A[i].x < A[id0].x) id0 = i;
	swap(A[id0], A[1]);
	tmp = A[id0];
	rep(i, 1, N) A[i] = A[i] - tmp;
	sort(A + 2, A + N + 1, cmp);
	int top = 1;
	rep(i, 2, N){
		while (top > 1 && cross(A[i], A[top], A[top - 1]) <= 0)
			--top;
		A[++top] = A[i];
	}
	return top;
}
int N;
int main(int argc, char *argv[]){
#define PROB "area"
#ifndef ONLINE_JUDGE
	freopen(PROB".in", "r", stdin);
	freopen(PROB".out", "w", stdout);
#endif
	read(N);
	rep(i, 1, N){
		read(A[i].x);
		read(A[i].y);
	}
	int M = Graham(A, N);
	//rep(i, 1, N) debug("%lld, %lld\n", A[i].x + tmp.x, A[i].y + tmp.y);
	if (M < 4){
		LL ans = cross(A[2], A[3]);
		printf("%lld.%c\n", ans / 2, ans & 1 ? '5' : '0');
		return 0;
	}
	int j = 3, k = 4, l = 2;
	LL ans = 0;
	rep(i, 1, N){
		int nj = --j, nk = k, nnk, nl = l, nnl;
		LL lst = 0, ne = 0;
		do{
			lst = ne; k = nk; l = nl; 
			j = nj++; if (nj > M) nj = 1;
			nk = k, nnk = k, nl = l, nnl = l;
			do{
				nk = nnk++; if (nnk > M) nnk = 1;
			}while (cross(A[nk], A[nj], A[i]) < cross(A[nnk], A[nj], A[i]));
			do{
				nl = nnl++; if (nnl > M) nnl = 1;
			}while (cross(A[nl], A[i], A[nj]) < cross(A[nnl], A[i], A[nj]));
			ne = cross(A[nk], A[nj], A[i]) + cross(A[nl], A[i], A[nj]);
		}while (lst <= ne);
		//debug("%d %d %d %d: %lld\n", i, j, k, l, lst);
		cmax(ans, lst);
	}
	printf("%lld.%c\n", ans / 2, ans & 1 ? '5' : '0');
	return 0;
}
