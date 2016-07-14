#include<cstdio>
#include<algorithm>

struct vec{
	long long dx,dy;
	long long operator *(const vec &b)const{
		return dx*b.dy-b.dx*dy;
	}
};

struct point{
	long long x,y;
	vec operator -(const point &b) const{
		vec t;
		t.dx=b.x-x;
		t.dy=b.y-y;
		return t;
	}
}d[110000];

int n;
long long ans;

/*bool operator <(const 

int n;


void init(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
*/

long long abs(long long a){
	if (a<0) return -a;
	return a;
}



long long calc(point A,point B,point C,point D){
	long long s1=(A-B)*(A-C);
	long long s2=(A-B)*(A-D);
	if ((s1>0) ^ (s2>0)) return abs(s1-s2);
	std::swap(B,C);
	s1=(A-B)*(A-C);
	s2=(A-B)*(A-D);
	if ((s1>0) ^ (s2>0)) return abs(s1-s2);
	std::swap(B,D);
	s1=(A-B)*(A-C);
	s2=(A-B)*(A-D);
	if ((s1>0) ^ (s2>0)) return abs(s1-s2);
	return 0;
}

void init(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld%lld",&(d[i].x),&(d[i].y));
}



int main(){
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	init();
	ans=0;
	for (int i=1;i<=n;i++) for (int j=i+1;j<=n;j++) for (int k=j+1;k<=n;k++){
		ans=std::max(ans,abs( (d[i]-d[j])*(d[i]-d[k]) ) );
		for (int h=k+1;h<=n;h++) ans=std::max(ans,calc(d[i],d[j],d[h],d[k]) );
	}
	printf("%lld.",ans>>1);
	printf("%d\n",ans & 1 ? 5 : 0);
	return 0;
}

