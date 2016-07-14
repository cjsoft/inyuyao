#include<cstdio>
#include<cctype>
#include<algorithm>

using namespace std;

typedef long long ll;
typedef long double dx;

template<typename T> void read(T& v) {
	v = 0; static char ch;
	while(!isdigit(ch = getchar()));
	do { v = v*10+ch-'0'; } while(isdigit(ch = getchar()));
}

const int N = 1e5;

int n;

struct Point {
	ll x, y;
} q[N], p[N];

ll ans = 0;

inline ll cross(const Point& x, const Point& y) {
	return x.x*y.y-x.y*y.x;
}

inline ll cross(int x, int y) {
	return cross(p[x], p[y]);
}

inline ll area(int i, int j, int k) {
	return cross(i, j)+cross(j, k)+cross(k, i);
}

bool cmp(const Point& x, const Point& y) {
	return x.x<y.x || (x.x==y.x && x.y<y.y);
}

int us[N], ut, ds[N], dt;

void makeshit() {
	sort(p, p+n, cmp);
	us[ut = 0] = 0;
	us[++ut] = 1;
	ds[dt = 0] = 0;
	ds[++dt] = 1;
	for(int i = 2; i<n; ++i) {
		while(ut>0 && area(us[ut-1], us[ut], i)>0) --ut;
		us[++ut] = i;
		while(dt>0 && area(ds[dt-1], ds[dt], i)<0) --dt;
		ds[++dt] = i;
	}
	int ct = 0;
	for(int i = 0; i<=ut; ++i) q[ct++] = p[us[i]];
	for(int i = dt-1; i>0; --i) q[ct++] = p[ds[i]];
	for(int i = 0; i<ct; ++i) p[i] = q[i];
	n = ct;
}

int main() {
	freopen("area.in", "r", stdin);
	freopen("area.out", "w", stdout);
	read(n);
	for(int i = 0; i<n; ++i) read(p[i].x), read(p[i].y);
	makeshit();
	for(int i = 0; i<n; ++i) {
		for(int j = i+1; j<n; ++j) {
			ll mp = 0, mn = 0;
			for(int k = 0; k<n; ++k) {
				dx a = area(i, j, k);
				if(a>mp) mp = a;
				if(a<mn) mn = a;
			}
			if(mp-mn>ans) ans = mp-mn;
		}
	}
	printf("%lld.%c\n", ans/2, (ans&1)==1?'5':'0');
	return 0;
}
