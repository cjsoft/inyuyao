#include<cstdio>
#include<iostream>
#include<cstring>
#include<stack>
#include<queue>
#include<algorithm>
using namespace std;

stack<unsigned long long>two;
queue<unsigned long long>twoo;
queue<unsigned long long>twooo;
unsigned long long ten,r;
unsigned long long ct,n;
bool flag;

void p(){
	ten++;
	unsigned long long t=ten,tt=ten;
	while (t){
		two.push(t%2);
		twooo.push(t%2);
		t/=2;
	}
	r=0;
	while (!two.empty()){
		r*=10;
		r+=two.top();
		two.pop();
	}
	unsigned long long rr=r;
	while (r){
		twoo.push(r%2);
		r/=2;
	}
	r=0;
	
	//cout<<endl;

	while (!twooo.empty()){
		if (twooo.front()!=twoo.front()){
			//ct++;
			//cout<<ct<<" : "<<rr<<" "<<tt<<" fail!"<<endl;
			break;
		}
		twoo.pop();
		twooo.pop();
		if (twooo.empty()){
			ct++;
			if (ct==n){
				cout<<rr<<endl;
				flag=1;
				//return;
			}
			while (!two.empty()){
				cout<<two.top();
				two.pop();
			}
			//cout<<endl;
		}
	}
	while (!twooo.empty()){
		twooo.pop();
	}
	while (!twoo.empty()){
		twoo.pop();
	}
	
	//cout<<"--------------------------------------"<<endl;
}

int main(){
	freopen ("quiz.in","r",stdin);
	freopen ("quiz.out","w",stdout);
	
	cin>>n;
	if (n>=238){
		ct=237;
		ten=98305;
	}
	if (n>=270){
		ct=269;
		ten=196609;
	}
	if (n>=290){
		ct=289;
		ten=292545;
	}
	if (n>=306){
		ct=305;
		ten=393217;
	}
	if (n>=320){
		ct=319;
		ten=489153;
	}
	if (n>=336){
		ct=335;
		ten=589825;
	}
	
	while (1){
		p();
		if (flag) break;
	}
	
	
	return 0;
}












