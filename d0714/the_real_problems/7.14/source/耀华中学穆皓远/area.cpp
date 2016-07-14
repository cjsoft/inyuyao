#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
template <typename T> inline void relax(T &a, const T &b){if (a<b) a=b;}
inline unsigned int getuint(){
	char w=getchar();
	while (w<'0'||'9'<w) w=getchar();
	unsigned int ans=0;
	for (;'0'<=w&&w<='9';w=getchar()) ans=ans*10+w-'0';
	return ans;
}
inline int ran(){return rand()<<16|rand();}
int n0, n;
struct rec{
	long double x, y;
	rec(){}
	rec(const long double &x, const long double &y):x(x), y(y){}
	friend inline rec operator -(const rec &a, const rec &b){return rec(a.x-b.x, a.y-b.y);}
	friend inline long double operator *(const rec &a, const rec &b){return a.x*b.y-a.y*b.x;}
} a0[100005], hull[100005], a[100005];
inline bool operator <(const rec &i, const rec &j){return i.x!=j.x?i.x<j.x:i.y<j.y;}
inline long double slope(const rec &i, const rec &j){return i.x!=j.x?(i.y-j.y)/(i.x-j.x):j.y>i.y?1e18:-1e18;}
inline long double area(const rec &a, const rec &b, const rec &c){return (b-a)*(c-a);}
int main(){
	freopen("area.in", "r", stdin);
	freopen("area.out", "w", stdout);
	n0=getuint();
	for (int i=1;i<=n0;i++) a0[i].x=getuint(), a0[i].y=getuint();
	std::sort(a0+1, a0+n0+1);
	int now=0;
	for (int i=1;i<=n0;hull[++now]=a0[i++]) for (;now>=2&&slope(hull[now-1], hull[now])<slope(hull[now], a0[i]);now--);
	for (int i=1;i<=now;i++) a[++n]=hull[i];
	now=0;
	for (int i=n0;i;hull[++now]=a0[i--]) for (;now>=2&&slope(a0[i], hull[now])>slope(hull[now], hull[now-1]);now--);
	for (int i=2;i<now;i++) a[++n]=hull[i];
	if (n<=4000){
		long double ans=0;
		//for (int i=1;i<=n;i++) for (int j=i<n?i+1:1;j!=i;j<n?j++:j=1) for (int k=i;k!=j;k<n?k++:k=1) for (int l=j;l!=i;l<n?l++:l=1) relax(ans, area(a[i], a[j], a[k])+area(a[j], a[i], a[l]));
		for (int i=1;i<=n;i++) for (int j=i<n?i+1:1, k=i, l=j;j!=i;j<n?j++:j=1){
			for (;area(a[i], a[j], a[k<n?k+1:1])>area(a[i], a[j], a[k]);k<n?k++:k=1);
			for (;area(a[j], a[i], a[l<n?l+1:1])>area(a[j], a[i], a[l]);l<n?l++:l=1);
			relax(ans, area(a[i], a[j], a[k])+area(a[j], a[i], a[l]));
		}
		printf("%.1Lf\n", ans/2);
		return 0;
	}
	long double ans=0;
	for (;clock()<0.95*CLOCKS_PER_SEC;){
		int i=ran()%n+1, j=ran()%n+1;
		if (i>j) std::swap(i, j);
		int k=i, l=j;
		for (;area(a[i], a[j], a[k<n?k+1:1])>area(a[i], a[j], a[k]);k<n?k++:k=1);
		for (;area(a[j], a[i], a[l<n?l+1:1])>area(a[j], a[i], a[l]);l<n?l++:l=1);
		relax(ans, area(a[i], a[j], a[k])+area(a[j], a[i], a[l]));
	}
	printf("%.1Lf\n", ans/2);
	return 0;
}
