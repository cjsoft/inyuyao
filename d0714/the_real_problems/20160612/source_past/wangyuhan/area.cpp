#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define red(i, a, b) for(int i = (a); i >= (b); i--)
#define ll long long
#define abs ABS
#define sqr SQR
#define PII pair<int, int>
#define MP make_pair
#define PB push_back
#define FI first
#define SE second

template<typename tn> void read(tn& a) {
	tn x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) {
		if (c == '-') f = -1;
		c = getchar();
	}
	while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
	a = x * f;
}
template<typename tn> void cmax(tn& a, tn b) { if (b > a) a = b; }
template<typename tn> void cmin(tn& a, tn b) { if (b < a) a = b; }
template<typename tn> tn abs(tn a) { return a < 0 ? -a : a; }
template<typename tn> tn sqr(tn a) { return a * a; }

const int maxn = 5000;
struct point {
    ll x, y;
    point(ll x = 0,ll y = 0): x(x), y(y) {}
}p[maxn], ch[maxn];
int n, m;
  
typedef point vec;
vec operator + (vec a, vec b) { return vec(a.x + b.x, a.y + b.y); }
vec operator - (point a, point b) { return vec(a.x - b.x, a.y - b.y); }
vec operator * (vec a, ll p) { return vec(a.x * p, a.y * p); }
vec operator / (vec a, ll p) { return vec(a.x / p, a.y / p); }
bool operator < (const point& a, const point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
bool operator == (const point& a, const point& b) {
    return a.x == b.x && a.y == b.y;
}
ll dot(vec a, vec b) { return a.x * b.x + a.y * b.y; }
ll length(vec a) { return sqrt(dot(a, a)); }
ll cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }
ll area2(point a, point b, point c) { return abs(cross(b - a, c - a)); }
  
int convexhull(){
    sort(p + 1, p + n + 1);
    int m = 0;
    rep(i, 1, n){
        while (m > 1 && cross(ch[m] - ch[m - 1], p[i] - ch[m - 1]) <= 0) m--;
        ch[++m] = p[i];
    }
    int k = m;
    red(i, n, 1){
        while(m > k && cross(ch[m] - ch[m - 1], p[i] - ch[m - 1]) <= 0) m--;
        ch[++m] = p[i];
    }
    if (n > 1) m--;
    return m;
}
  
ll RC() {
    if (m <= 2) return 0;
    if (m == 3) return abs(cross(ch[1] - ch[2], ch[1] - ch[3]));
    int l = 2, j = 3, k = 4;
    ll ans = 0;
    rep(i, 1, m) {
        int j2 = --j, k2 = k, k3, l2 = l, l3;
        ll last = 0, cur = 0;
        while(last <= cur) {
            last = cur; k = k2; l = l2;
            j = j2++; if (j2 > m) j2 = 1;
            k2 = k, k3 = k;
            l2 = l, l3 = l;
            do {
                k2 = k3++; if (k3 > m) k3 = 1;
            }while(area2(ch[k2], ch[j2], ch[i]) < area2(ch[k3], ch[j2], ch[i]));
            do {
                l2 = l3++; if (l3 > m) l3 = 1;
            }while(area2(ch[l2], ch[i], ch[j2]) < area2(ch[l3], ch[i], ch[j2]));
            cur = area2(ch[k2], ch[j2], ch[i]) + area2(ch[l2], ch[i], ch[j2]);  
        }
        cmax(ans, last);
    }
    return ans;
}
  
int main() {
	freopen("area.in", "r", stdin);
	freopen("area.out", "w", stdout);
    scanf("%d", &n);
    rep(i, 1, n) read(p[i].x), read(p[i].y);
    m = convexhull();
    ll ans = RC();
    printf("%lld", ans >> 1ll);
    printf((ans & 1ll) ? ".5\n" : ".0\n");
    return 0;
}