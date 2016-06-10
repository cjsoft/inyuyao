#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

long long N;
int M,C,D;

long long Mod=1e9+7;

struct Matrix
{
	long long fxxk[11][11];
}A={{{0}}};

struct Pot
{
	long long x;
	int y;
	int type;
}pot[40]={{0,0,0}};
int pp=0;

long long F[100][20]={{0}};
int isC[8]={0};
int isD[8]={0};

int L[20]={0};
int R[20]={0};
int is2[20]={0};
int vis[20]={0};

struct Matrix operator * (Matrix a1,Matrix a2)
{
	Matrix b={{{0}}};
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
			for(int k=1;k<=9;k++)
				(b.fxxk[i][j]+=a1.fxxk[i][k]*a2.fxxk[k][j])%=Mod;
	return b;
}

Matrix power(Matrix a,long long k)
{
	Matrix o={{{0}}};
	for(int i=1;i<=9;i++)
		o.fxxk[i][i]=1;
	for(;k>0;k>>=1)
	{
		if(k&1) o=o*a;
		a=a*a;
	}
	return o;
}

bool cmp(struct Pot a1,struct Pot a2)
{return a1.x<a2.x || (a1.x==a2.x && a1.y<a2.y);}

int main()
{
	freopen("eat.in","r",stdin);
	freopen("eat.out","w",stdout);
	cin>>N>>M>>C>>D;
	for(int i=1;i<=C;i++)
	{
		pp++;
		scanf("%lld%d",&pot[pp].x,&pot[pp].y);
		pot[pp].type=1;
	}
	for(int i=1;i<=D;i++)
	{
		pp++;
		scanf("%lld%d",&pot[pp].x,&pot[pp].y);
		pot[pp].type=2;
	}
	sort(pot+1,pot+pp+1,cmp);
	if(M==1)
	{
		if(D==0)
			puts("1");
		else puts("0");
		return 0;
	}
	if(M==2)
	{
		//1:1 1
		//2:0 0
		A.fxxk[1][1]=1;A.fxxk[1][2]=1;
		A.fxxk[2][1]=1;A.fxxk[2][2]=1;
		
		F[0][2]=1;
		
		long long place=0;
		int cnt=1;
		int g=0;
		long long help[20]={0};
		for(;cnt<=pp;)
		{
			int last=cnt;
			for(;last<=pp && pot[last].x==pot[cnt].x;last++);
			last--;
			Matrix mult=power(A,pot[cnt].x-place-1);
			memset(help,0,sizeof(help));
			memset(isC,0,sizeof(isC));
			memset(isD,0,sizeof(isD));
			for(int i=1;i<=2;i++)
				for(int j=1;j<=2;j++)
					(help[j]+=F[g][i]*mult.fxxk[i][j])%=Mod;
			for(int i=cnt;i<=last;i++)
			{
				if(pot[i].type==1)
					isC[pot[i].y]=1;
				else isD[pot[i].y]=1;
			}
			for(int i=1;i<=2;i++)
				if(isD[i]==1) isC[i]=0;
			
			g++;
			
			if(isC[1]==0 && isC[2]==0)
				(F[g][2]+=help[1])%=Mod,(F[g][1]+=help[2])%=Mod,(F[g][1]+=help[1])%=Mod;
			
			if(isD[1]==0 && isD[2]==0)
				(F[g][2]+=help[2])%=Mod;
			
			place=pot[cnt].x;
			cnt=last+1;
		}
		
		if(place<N)
		{
			Matrix mult=power(A,N-place);
			g++;
			for(int i=1;i<=2;i++)
				for(int j=1;j<=2;j++)
					(F[g][j]+=F[g-1][i]*mult.fxxk[i][j])%=Mod;
		}
		cout<<F[g][2]<<endl;
	}
	if(M==3)
	{
		//1:1 2 0
		//2:0 1 2
		//3:1 0 2
		//4:0 0 0
		A.fxxk[1][1]=1;A.fxxk[1][3]=1;A.fxxk[1][4]=1;
		A.fxxk[2][2]=1;A.fxxk[2][3]=1;A.fxxk[2][4]=1;
		A.fxxk[3][1]=1;A.fxxk[3][2]=1;A.fxxk[3][3]=1;A.fxxk[3][4]=1;
		A.fxxk[4][1]=1;A.fxxk[4][2]=1;A.fxxk[4][3]=1;A.fxxk[4][4]=1;
		is2[1]=1,L[1]=1,R[1]=2;
		is2[2]=1,L[2]=2,R[2]=3;
		is2[3]=1,L[3]=1,R[3]=3;
		
		F[0][4]=1;
		
		long long place=0;
		int cnt=1;
		int g=0;
		long long help[20]={0};
		for(;cnt<=pp;)
		{
			int last=cnt;
			for(;last<=pp && pot[last].x==pot[cnt].x;last++);
			last--;
			Matrix mult=power(A,pot[cnt].x-place-1);
			memset(help,0,sizeof(help));
			memset(isC,0,sizeof(isC));
			memset(isD,0,sizeof(isD));
			for(int i=1;i<=4;i++)
				for(int j=1;j<=4;j++)
					(help[j]+=F[g][i]*mult.fxxk[i][j])%=Mod;
					
			for(int i=cnt;i<=last;i++)
			{
				if(pot[i].type==1)
					isC[pot[i].y]=1;
				else isD[pot[i].y]=1;
			}
			for(int i=1;i<=3;i++)
				if(isD[i]==1) isC[i]=0;
			
			g++;
			for(int i=1;i<=3;i++)
			{
				for(int j=1;j<=3;j++)
				{
					if(is2[i]==1 && is2[j]==1 && A.fxxk[i][j]==1)
					{
						memset(vis,0,sizeof(vis));
						int l=min(L[i],L[j]),r=max(L[i],L[j]);
						for(int p=l;p<=r;p++)
							vis[p]=1;
						l=min(R[i],R[j]),r=max(R[i],R[j]);
						for(int p=l;p<=r;p++)
							vis[p]=1;
						int flag=1;
						for(int p=1;p<=3;p++)
						{
							if(vis[p]==1 && isC[p]==1)
								flag=0;
							if(vis[p]==0 && isD[p]==1)
								flag=0;
						}
						if(flag==1)
							(F[g][j]+=help[i])%=Mod;
					}
				}
			}
			
			if(isC[1]==0 && isC[2]==0 && isD[3]==0 )
				(F[g][4]+=help[1])%=Mod,(F[g][1]+=help[4])%=Mod;
			
			if(isD[1]==0 && isC[2]==0 && isC[3]==0)
				(F[g][4]+=help[2])%=Mod,(F[g][2]+=help[4])%=Mod;
			
			if(isC[1]==0 && isC[2]==0 && isC[3]==0 && isD[4]==0)
				(F[g][4]+=help[3])%=Mod,(F[g][3]+=help[4])%=Mod;
			
			if(isD[1]==0 && isD[2]==0 && isD[3]==0)
				(F[g][4]+=help[4])%=Mod;
			
			place=pot[cnt].x;
			cnt=last+1;
		}
		if(place<N)
		{
			Matrix mult=power(A,N-place);
			g++;
			for(int i=1;i<=4;i++)
				for(int j=1;j<=4;j++)
					(F[g][j]+=F[g-1][i]*mult.fxxk[i][j])%=Mod;
		}
		cout<<F[g][4]<<endl;
	}
	if(M==4)
	{
		//1:1 2 0 0
		//2:0 1 2 0
		//3:0 0 1 2
		//4:1 0 2 0
		//5:0 1 0 2
		//6:1 0 0 2
		//7:1 2 1 2
		//8:1 1 2 2
		//9:0 0 0 0
		A.fxxk[1][1]=1;A.fxxk[1][3]=1;A.fxxk[1][4]=1;A.fxxk[1][6]=1;A.fxxk[1][7]=1;A.fxxk[1][9]=1;
		A.fxxk[2][2]=1;A.fxxk[2][4]=1;A.fxxk[2][5]=1;A.fxxk[2][6]=1;A.fxxk[2][9]=1;
		A.fxxk[3][1]=1;A.fxxk[3][3]=1;A.fxxk[3][5]=1;A.fxxk[3][6]=1;A.fxxk[3][7]=1;A.fxxk[3][9]=1;
		A.fxxk[4][1]=1;A.fxxk[4][2]=1;A.fxxk[4][4]=1;A.fxxk[4][5]=1;A.fxxk[4][6]=1;A.fxxk[4][9]=1;
		A.fxxk[5][2]=1;A.fxxk[5][3]=1;A.fxxk[5][4]=1;A.fxxk[5][5]=1;A.fxxk[5][6]=1;A.fxxk[5][9]=1;
		A.fxxk[6][1]=1;A.fxxk[6][2]=1;A.fxxk[6][3]=1;A.fxxk[6][4]=1;A.fxxk[6][5]=1;A.fxxk[6][6]=1;A.fxxk[6][8]=1;A.fxxk[6][9]=1;
		A.fxxk[7][1]=1;A.fxxk[7][3]=1;A.fxxk[7][6]=1;A.fxxk[7][7]=1;A.fxxk[7][9]=1;
		A.fxxk[8][1]=1;A.fxxk[8][3]=1;A.fxxk[8][6]=1;A.fxxk[8][8]=1;A.fxxk[8][9]=1;
		A.fxxk[9][1]=1;A.fxxk[9][2]=1;A.fxxk[9][3]=1;A.fxxk[9][4]=1;A.fxxk[9][5]=1;A.fxxk[9][6]=1;A.fxxk[9][7]=1;A.fxxk[9][9]=1;
		is2[1]=1,L[1]=1,R[1]=2;
		is2[2]=1,L[2]=2,R[2]=3;
		is2[3]=1,L[3]=3,R[3]=4;
		is2[4]=1,L[4]=1,R[4]=3;
		is2[5]=1,L[5]=2,R[5]=4;
		is2[6]=1,L[6]=1,R[6]=4;
		
		F[0][9]=1;
		long long place=0;
		int cnt=1;
		int g=0;
		long long help[20]={0};
		for(;cnt<=pp;)
		{
			int last=cnt;
			for(;last<=pp && pot[last].x==pot[cnt].x;last++);
			last--;
			Matrix mult=power(A,pot[cnt].x-place-1);
			memset(help,0,sizeof(help));
			memset(isC,0,sizeof(isC));
			memset(isD,0,sizeof(isD));
			for(int i=1;i<=9;i++)
				for(int j=1;j<=9;j++)
					(help[j]+=F[g][i]*mult.fxxk[i][j])%=Mod;
			for(int i=cnt;i<=last;i++)
			{
				if(pot[i].type==1)
					isC[pot[i].y]=1;
				else isD[pot[i].y]=1;
			}
			for(int i=1;i<=4;i++)
				if(isD[i]==1) isC[i]=0;
			g++;
			for(int i=1;i<=8;i++)
			{
				for(int j=1;j<=8;j++)
				{
					if(is2[i]==1 && is2[j]==1 && A.fxxk[i][j]==1)
					{
						memset(vis,0,sizeof(vis));
						int l=min(L[i],L[j]),r=max(L[i],L[j]);
						for(int p=l;p<=r;p++)
							vis[p]=1;
						l=min(R[i],R[j]),r=max(R[i],R[j]);
						for(int p=l;p<=r;p++)
							vis[p]=1;
						int flag=1;
						for(int p=1;p<=4;p++)
						{
							if(vis[p]==1 && isC[p]==1)
								flag=0;
							if(vis[p]==0 && isD[p]==1)
								flag=0;
						}
						if(flag==1)
							(F[g][j]+=help[i])%=Mod;
					}
					else if((i==7 || i==8 || j==7 || j==8) && A.fxxk[i][j]==1 && isC[1]==0 && isC[2]==0 && isC[3]==0 && isC[4]==0)
					{
						(F[g][j]+=help[i])%=Mod;
					}
				}
			}
			
			if(isC[1]==0 && isC[2]==0 && isD[3]==0 && isD[4]==0)
				(F[g][9]+=help[1])%=Mod,(F[g][1]+=help[9])%=Mod;
			
			if(isD[1]==0 && isC[2]==0 && isC[3]==0 && isD[4]==0)
				(F[g][9]+=help[2])%=Mod,(F[g][2]+=help[9])%=Mod;
			
			if(isD[1]==0 && isD[2]==0 && isC[3]==0 && isC[4]==0)
				(F[g][9]+=help[3])%=Mod,(F[g][3]+=help[9])%=Mod;
			
			if(isC[1]==0 && isC[2]==0 && isC[3]==0 && isD[4]==0)
				(F[g][9]+=help[4])%=Mod,(F[g][4]+=help[9])%=Mod;
			
			if(isD[1]==0 && isC[2]==0 && isC[3]==0 && isC[4]==0)
				(F[g][9]+=help[5])%=Mod,(F[g][5]+=help[9])%=Mod;
			
			if(isC[1]==0 && isC[2]==0 && isC[3]==0 && isC[4]==0)
				(F[g][9]+=help[6])%=Mod,(F[g][6]+=help[9])%=Mod;
			
			if(isC[1]==0 && isC[2]==0 && isC[3]==0 && isC[4]==0)
				(F[g][9]+=help[7])%=Mod,(F[g][7]+=help[9])%=Mod;
			
			if(isC[1]==0 && isC[2]==0 && isC[3]==0 && isC[4]==0)
				(F[g][9]+=help[8])%=Mod;
			
			if(isD[1]==0 && isD[2]==0 && isD[3]==0 && isD[4]==0)
				(F[g][9]+=help[9])%=Mod;
			
			place=pot[cnt].x;
			cnt=last+1;
		}
		if(place<N)
		{
			Matrix mult=power(A,N-place);
			g++;
			for(int i=1;i<=9;i++)
				for(int j=1;j<=9;j++)
					(F[g][j]+=F[g-1][i]*mult.fxxk[i][j])%=Mod;
		}
		cout<<F[g][9]<<endl;
	}
	return 0;
}
