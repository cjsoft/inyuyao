#include<algorithm>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include  <stdio.h>
#include   <math.h>
#include   <time.h>
#include   <vector>
#include   <bitset>
#include    <queue>
#include      <set>
#include      <map>
using namespace std;

typedef long long LL;

const int N=65536,M=N+5,G=3,Mod=998244353;

int n,m,A[M],B[M],C[M],D[M],f[22][M],fac[M],ifac[M],g[20][M],Ng[20][M],LOG[M],Rev[M],s[50][50];

inline int Pow(int a,int b)
{
	int c=1;
	while(b)
	{
		if(b&1)
			c=c*(LL)a%Mod;
		a=a*(LL)a%Mod;b>>=1;
	}
	return c;
}

inline void Prepare()
{
	LOG[N]=16;
	for(int i=N-1;~i;i--)
	{
		LOG[i]=LOG[i+1];
		if(i&&i==(1<<LOG[i]-1))
			LOG[i]--;
	}
	for(int i=1;i<=19;i++)
	{
		g[i][1]=Pow(G,(Mod-1)>>i),Ng[i][1]=Pow(g[i][1],Mod-2);g[i][0]=Ng[i][0]=1;
		for(int j=2;j<M;j++)
			g[i][j]=g[i][j-1]*(LL)g[i][1]%Mod,Ng[i][j]=Ng[i][j-1]*(LL)Ng[i][1]%Mod;
	}
}

inline void NTT(int F[],int len,int flag)
{
	int n=1<<len;
	for(int i=1;i<n;i++)
	{
		Rev[i]=(Rev[i>>1]>>1)|((i&1)<<(len-1));
		if(i<Rev[i])
			swap(F[i],F[Rev[i]]);
	}
	for(int i=1,k=1;i<n;i<<=1,k++)
	{
		int *K=flag==1?g[k]:Ng[k];
		for(int j=0;j<n;j+=i<<1)
		{
			int W=0,x,y;
			for(int k=0;k<i;k++)
				x=F[j+k],y=F[j+k+i]*(LL)K[W]%Mod,F[j+k]=(x+y)%Mod,F[j+k+i]=(x-y+Mod)%Mod,W++;
		}
	}
	if(flag==-1)
	{
		LL Ny=Pow(n,Mod-2);
		for(int i=0;i<n;i++)
			F[i]=F[i]*(LL)Ny%Mod;
	}
}

inline void GetInv(int A[],int n,int B[])
{
	static int tmp[M]={};
	B[0]=Pow(A[0],Mod-2);
	for(int i=2;;i<<=1)
	{
		int N=i<<1;
		for(int j=i>>1;j<N;j++)
			B[j]=tmp[j]=0;
		for(int j=0;j<i;j++)
			tmp[j]=A[j];
		NTT(B,LOG[N],1);NTT(tmp,LOG[N],1);
		for(int j=0;j<N;j++)
			B[j]=B[j]*(2-(LL)B[j]*tmp[j]%Mod+Mod)%Mod;
		NTT(B,LOG[N],-1);
		if(i>=n)
			return;
	}
}

void init()
{
	n=32768;m=15;Prepare();
	fac[0]=1;
	for(int i=1;i<n+n;i++)
		fac[i]=fac[i-1]*(LL)i%Mod;
	ifac[n-1]=Pow(fac[n-1],Mod-2);
	for(int i=n-1;i;i--)
		ifac[i-1]=ifac[i]*(LL)i%Mod;
	for(int i=1;i<n;C[i]=B[i]*(LL)ifac[i]%Mod,D[i]=C[i],B[i]=C[i]*(LL)i%Mod,i++)
		if(i%2==0)
			B[i]=Pow(Pow(2,i/2),i-1);
		else
			B[i]=Pow(Pow(2,i),(i-1)/2);
	D[0]=C[0]=1;
	GetInv(C,n,A);
	for(int i=n;i<n+n;i++)
		A[i]=0;
	NTT(A,LOG[n+n],1);NTT(B,LOG[n+n],1);
	for(int i=0;i<n+n;i++)
		A[i]=A[i]*(LL)B[i]%Mod;
	NTT(A,LOG[n+n],-1);
	for(int i=n;i<n+n;i++)
		A[i]=0;
	for(int i=1;i<n;i++)
		A[i]=A[i]*(LL)ifac[i]%Mod*fac[i-1]%Mod;
	NTT(A,LOG[n+n],1);
	for(int j=0;j<n+n;j++)
		f[0][j]=D[j];
	for(int i=1;i<=m;i++)
	{
		for(int j=0;j<n+n;j++)
			C[j]=f[i-1][j];
		NTT(C,LOG[n+n],1);
		for(int j=0;j<n+n;j++)
			f[i][j]=C[j]*(LL)A[j]%Mod;
		NTT(f[i],LOG[n+n],-1);
		for(int j=n;j<n+n;j++)
			f[i][j]=0;
	}
	s[0][0]=1;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=m;j++)
			s[i][j]=(j*(LL)s[i-1][j]+s[i-1][j-1])%Mod;
}

void solve()
{
	cin>>n>>m;
	int Ans=0;
	for(int i=0;i<=m;i++)
		Ans=(Ans+f[i][n]*(LL)fac[n]%Mod*s[m][i])%Mod;
	cout<<Ans<<endl;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("dark.in","r",stdin);
	freopen("dark.out","w",stdout);
#endif
	init();
	int t;cin>>t;
	while(t--)
		solve();
	return 0;
}

