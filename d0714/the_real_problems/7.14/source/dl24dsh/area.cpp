#include<cstdio>
#include<iostream>
#include<climits>
#include<stack>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<iomanip>
#include<vector>
using namespace std;
long long a=LONG_LONG_MAX;
int o,n,nowtp,ct;

long double sum,t;

struct node{
	long long x,y;
}all[100001];
node al[100001];

stack<int>tb;
vector<int>rtb;
node bx;

void in(){
	cin>>n;
	for (int i=1;i<=n;i++) cin>>al[i].x>>al[i].y;
}

void geto(){
	o=1;
	for (int i=2;i<=n;i++){
		if (al[o].y>al[i].y){
			o=i;
		}
		else if (al[o].y==al[i].y&&all[o].x>al[i].x){
			o=i;
		}
	}
	swap(al[1],al[o]);
	bx.x=al[1].x+1;
	bx.y=al[1].y;
}

double jl(node a,node b){
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

double cs(node b){
	//cout<<jl(b,all[1])<<" "<<jl(b,bx)<<" "<<sqrt(jl(b,all[1]))<<" ";
	return (1+jl(b,all[1])-jl(b,bx))/(2*sqrt(jl(b,all[1])));
}

double cx(int a,int b,int c){
	long long x1=all[a].x-all[b].x;
	long long y1=all[a].y-all[b].y;
	long long x2=all[c].x-all[a].x;
	long long y2=all[c].y-all[a].y;
	return x1*y2-x2*y1;
}

bool cmp(node a,node b){
	return cs(a)>cs(b);
}

void gettb(){
	sort (al+2,al+n+1,cmp);
	for (int i=1;i<=n;i++){
		if (all[ct].x!=al[i].x||all[ct].y!=al[i].y){
			ct++;
			all[ct]=al[i];
		}
	}
	
	tb.push(1);
	tb.push(2);
	for (int i=3;i<=ct;i++){
		nowtp=tb.top();
		tb.pop();
		while (cx(nowtp,tb.top(),i)<0){
			nowtp=tb.top();
			tb.pop();
		}
		tb.push(nowtp);
		tb.push(i);
	}
}

long double gets(int a1,int a2,int a3,int a4){
	node a=all[rtb[a1]];
	node b=all[rtb[a2]];
	node c=all[rtb[a3]];
	node d=all[rtb[a4]];
	//cout<<rtb[a1]<<" "<<rtb[a2]<<" "<<rtb[a3]<<" "<<rtb[a4]<<" "<<endl;
	long double s=0;
	s+=a.x*d.y;
	s+=d.x*c.y;
	s+=c.x*b.y;
	s+=b.x*a.y;
	s-=a.x*b.y;
	s-=b.x*c.y;
	s-=c.x*d.y;
	s-=d.x*a.y;
	s/=2;
	return s;
}

int main(){
	ios::sync_with_stdio(false);
	freopen ("area.in","r",stdin);
	freopen ("area.out","w",stdout);
	
	in();
	geto();
	//cout<<o<<" "<<all[1].x<<" "<<all[1].y<<endl;
	
	
	gettb();
	//for (int i=2;i<=n;i++) cout<<all[i].x<<" "<<all[i].y<<endl;
	while (!tb.empty()){
		rtb.push_back(tb.top());
		tb.pop();
	}
	
	for (int i=0;i<rtb.size();i++){
		for (int j=i+1;j<rtb.size();j++){
			for (int k=j+1;k<rtb.size();k++){
				for (int p=k+1;p<rtb.size();p++){
					if (gets(i,j,k,p)>sum) sum=gets(i,j,k,p);
					//cout<<fixed<<setprecision(1)<<gets(i,j,k,p)<<endl;
					//cout<<gets(i,j,k,p)<<endl;
				}
			}
		}
	}
	
	cout<<fixed<<setprecision(1)<<sum<<endl;
	
	
	return 0;
}




















