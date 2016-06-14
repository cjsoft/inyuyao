#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;


int n; 
long long  a[5005];

int ff;
long long ans=0;

int main()
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	cin>>a[i];
	
//	int tmp=0;
//	for(int i=1;i<=n;i++) tmp+=a[i];
//	cout<<tmp<<endl;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		if(i!=j)
		{
		//	cout<<a[i]+a[j]<<"  ";
				long long tm=a[i]|a[j];
				long long tt=a[i]&a[j];
			
			
				a[i]=tt;
				a[j]=tm;	
			//	cout<<a[i]+a[j]<<endl;
		}
	
	}


	ans=0;
	for(int i=1;i<=n;i++)
	ans=ans+a[i]*a[i];
	
//	solve(a);	
	cout<<ans<<endl;
}
