#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=1E5+77;
typedef long double LD;
inline LD my_abs(const LD &v){return v>0?v:-v;}

struct Point{
	LD x,y;
	void read(){
		scanf("%Lf%Lf",&x,&y);
	}
}P[maxn*4],T1[maxn],T2[maxn];int ct1=0,ct2=0;
inline bool by_x(const Point &a,const Point &b){
	if(a.x!=b.x) return a.x<b.x;
	else return a.y<b.y;
}
inline LD getK(const Point &a,const Point &b){
	return (b.y-a.y)/(b.x-a.x);
}
inline Point operator -(const Point &a,const Point &b){
	return (Point){a.x-b.x,a.y-b.y};
}
inline LD operator *(const Point &a,const Point &b){
	return a.x*b.y-b.x*a.y;
}

inline LD area(const Point &a,const Point &b,const Point &c){
	return my_abs((b-a)*(c-a));
}

int N;
int main(){
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	scanf("%d",&N);
	for(int i=0;i<N;++i) P[i].read();
	sort(P,P+N,by_x);
	for(int i=0;i<N;++i){
		while(ct1>1 && getK(T1[ct1-2],T1[ct1-1])<getK(T1[ct1-1],P[i])) --ct1;
		T1[ct1++]=P[i];
	}
	for(int i=0;i<N;++i){
		while(ct2>1 && getK(T2[ct2-2],T2[ct2-1])>getK(T2[ct2-1],P[i])) --ct2;
		T2[ct2++]=P[i];
	}
	N=0;
	for(int i=0;i<ct2;++i) P[N++]=T2[i];
	for(int i=ct1-1;i>=0;--i) P[N++]=T1[i];

	/*
	cerr<<"TB:"<<endl;
	for(int i=0;i<N;++i){
		cerr<<P[i].x<<","<<P[i].y<<endl;
	}
	*/

	for(int i=0;i<N;++i) P[N+i]=P[i];


	LD ans=0.0;
	int p1=0,p2=0;
	for(int i=0;i<N;++i){
		//cerr<<"i:"<<i<<" p:"<<p<<endl;
		p1=0;p2=0;
		for(int j=i;j<N;++j){
			if(p1<j) p1=j;
			LD cur1=area(P[i],P[j],P[p1]),t;
			while((t=area(P[i],P[j],P[p1+1]))>cur1){
				cur1=t;++p1;
			}
			if(p2<i) p2=i;
			LD cur2=area(P[i],P[p2],P[j]);
			while(p2<j && (t=area(P[i],P[p2+1],P[j]))>cur2){
				cur2=t;++p2;
			}
			/*
			if(cur1+cur2>ans){
				cerr<<"----"<<endl<<i<<":"<<P[i].x<<","<<P[i].y<<endl
					<<p2<<":"<<P[p2].x<<","<<P[p2].y<<endl
					<<j<<":"<<P[j].x<<","<<P[j].y<<endl
					<<p1<<":"<<P[p1].x<<","<<P[p1].y<<endl
					<<" size:"<<cur1+cur2<<endl;
			}
			*/
			ans=max(ans,cur1+cur2);
		}
	}
/*
	N=0;
	for(int i=0;i<ct1;++i) P[N++]=T1[i];
	for(int i=ct2-1;i>=0;--i) P[N++]=T2[i];
	for(int i=0;i<N;++i) P[N+i]=P[i];
	p=0,p1=0,p2=0;
	for(int i=0;i<N;++i){
		LD ar1=area(P[i],P[p],P[p1]),ar2=area(P[i],P[p2],P[p]);
		//cerr<<"i:"<<i<<" p:"<<p<<endl;
		while(true){
			int op=p,op1=p1,op2=p2;
			++p;
			if(p1<p) p1=p;
			LD cur1=area(P[i],P[p],P[p1]),t;
			while((t=area(P[i],P[p],P[p1+1]))>cur1){
				cur1=t;++p1;
			}
			if(p2<i) p2=i;
			LD cur2=area(P[i],P[p2],P[p]);
			while(p2<p && (t=area(P[i],P[p2+1],P[p]))>cur2){
				cur2=t;++p2;
			}
			if(cur1+cur2<ar1+ar2){
				p=op;p1=op1;p2=op2;
				break;
			}
			ar1=cur1;ar2=cur2;
			if(cur1+cur2>ans){
				cerr<<"----"<<endl<<i<<":"<<P[i].x<<","<<P[i].y<<endl
					<<p2<<":"<<P[p2].x<<","<<P[p2].y<<endl
					<<p<<":"<<P[p].x<<","<<P[p].y<<endl
					<<p1<<":"<<P[p1].x<<","<<P[p1].y<<endl
					<<" size:"<<cur1+cur2<<endl;
			}
			ans=max(ans,cur1+cur2);
		}
	}
*/
	printf("%.1Lf\n",ans/2);
}
