#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;

int N,i,j,K;
int L[25],R[25];
int list1[25];
int as[25][3],list3[25];
double s1,s2;

struct node
{
	int x,id;
	bool operator <(const node &o)const{if(x==o.x)return id<o.id;return x>o.x;}
}list2[25];

void work(int a)
{
	int i;
	if(a>N)
	{
		for(i=1;i<=N;i++)
		{
			list2[i].x=list1[i];
			list2[i].id=i;
		}
		sort(list2+1,list2+N+1);
		for(i=1;i<=K;i++)
			list3[i]=list2[i].id;
		for(i=K+1;i<=N;i++)
			as[list2[i].id][2]++;
		sort(list3+1,list3+K+1);
		for(i=1;i<=K;i++)
		{
			if(i%4==1)as[list3[i]][0]++;
			else if(i%4==2)as[list3[i]][1]++;
			else if(i%4==3)as[list3[i]][1]++;
			else as[list3[i]][0]++;
		}
		return;
	}
	for(i=L[a];i<=R[a];i++)
	{
		list1[a]=i;
		work(a+1);
	}
}

int main()
{
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	scanf("%d",&N);
	for(i=1;i<=N;i++)scanf("%d",&L[i]);
	for(i=1;i<=N;i++)scanf("%d",&R[i]);
	scanf("%d",&K);
	work(1);
	for(i=1;i<=N;i++)
	{
		s1=(1.0*as[i][0])/(1.0*(as[i][0]+as[i][1]+as[i][2]));
		s2=(1.0*as[i][1])/(1.0*(as[i][0]+as[i][1]+as[i][2]));
		printf("%.6lf %.6lf\n",s1,s2);
	}
	return 0;
}
