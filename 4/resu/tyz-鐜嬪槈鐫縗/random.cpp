#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<utility>
#include<map>
using namespace std;
map<pair<int,int>,int> vis;
int main(){
	freopen("B.in","w",stdout);
	srand(time(NULL));
	printf("%d\n",100000);
	for(int i=1;i<=100000;i++){
		printf("%d%c",rand()%(1<<20),i==100000?'\n':' ');
	}
}