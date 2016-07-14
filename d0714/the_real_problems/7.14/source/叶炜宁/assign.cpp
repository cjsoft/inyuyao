#include<cstdio>
#include<algorithm>
using namespace std;
struct node{int x,y;}a[30];
int n,K,tot,Mx;
int L[30],R[30],suma[30],sumb[30],sc[30],sa[30],flag[30];
double f[30][1010],s[30][1010],ans1[30],ans2[30];
bool cmp(node x,node y){if (x.x==y.x) return x.y<y.y;return x.x>y.x;}
bool cmp1(node x,node y){return x.y<y.y;}
void calc()
{
	//for (int i=1;i<=n;i++) printf("%d ",sc[i]);printf("\n");
	for (int i=1;i<=n;i++){a[i].x=sc[i];a[i].y=i;}
	sort(a+1,a+n+1,cmp);
	sort(a+1,a+K+1,cmp1);
	//for (int i=1;i<=K;i++) printf("%d %d\n",a[i].x,a[i].y);
	for (int i=1;i<=K;i++) if (i%4<2)
		suma[a[i].y]++;else sumb[a[i].y]++;
}
void dfs(int t)
{
	if (t>n){calc();return;}
	for (int i=L[t];i<=R[t];i++)
	{
		sc[t]=i;
		dfs(t+1);
	}
}
void DP()
{
	for (int i=0;i<=n;i++)
		for (int j=0;j<=Mx;j++) f[i][j]=s[i][j]=0;
	for (int i=L[sa[1]];i<=R[sa[1]];i++)
		f[1][i]=(double)1/(R[sa[1]]-L[sa[1]]+1);
	s[1][0]=f[1][0];
	for (int i=1;i<=Mx;i++) s[1][i]=s[1][i-1]+f[1][i];
	for (int i=2;i<=n;i++)
	{
		for (int j=L[sa[i]];j<=R[sa[i]];j++)
		{
			if (sa[i]>sa[i-1])
			{
				   f[i][j]=s[i-1][Mx];
				   if (j) f[i][j]-=s[i-1][j-1];
			}else f[i][j]=s[i-1][Mx]-s[i-1][j];
			f[i][j]=f[i][j]/(R[sa[i]]-L[sa[i]]+1);
		}
		s[i][0]=f[i][0];
		for (int j=1;j<=Mx;j++) s[i][j]=s[i][j-1]+f[i][j];
	}
	for (int i=1;i<=K;i++) a[i].y=sa[i];
	sort(a+1,a+K+1,cmp1);
	for (int i=1;i<=K;i++) if (i%4<2)
		ans1[a[i].y]+=s[n][Mx];else ans2[a[i].y]+=s[n][Mx];
}
void Dfs(int t)
{
	if (t>n){DP();return;}
	for (int i=1;i<=n;i++) if (!flag[i])
	{
		sa[t]=i;
		flag[i]=1;
		Dfs(t+1);
		flag[i]=0;
	}
}
void Calc()
{
	double tot=0;
	//for (int i=1;i<=n;i++) if (flag[i]) printf("%d ",i);printf("\n");
	for (int i=1;i<=n;i++)if (flag[i])
	{
		for (int j=L[i];j<=R[i];j++)
		{
			//printf("#%d %d\n",i,j);
			double sum=(double)1/(R[i]-L[i]+1);
			int ok=1;
			for (int k=1;k<=n;k++) if (i!=k)
			{
				if (flag[k])
				{
					if (k<i)
					{
						//printf("%d %d %d\n",k,j,R[k]);
						if (j>R[k]){ok=0;break;}
						sum=sum*(R[k]-max(j,L[k])+1)/(R[k]-L[k]+1);
					}else
					{
						//printf("%d %d %d\n",k,k+1,R[k]);
						if (j+1>R[k]){ok=0;break;}
						sum=sum*(R[k]-max(j+1,L[k])+1)/(R[k]-L[k]+1);
					}
				}else
				{
					if (k<i)
					{
						//printf("%d %d %d\n",k,L[k],j-1);
						if (L[k]>j-1){ok=0;break;}
						sum=sum*(min(j-1,R[k])-L[k]+1)/(R[k]-L[k]+1);
					}else
					{
						//printf("%d %d %d\n",k,L[k],j);
						if (L[k]>j){ok=0;break;}
						sum=sum*(min(j,R[k])-L[k]+1)/(R[k]-L[k]+1);
					}
				}
			}
			if (ok) tot+=sum;
		}
	}
	int cnt=0;
	for (int i=1;i<=n;i++) if (flag[i])
	{
		cnt++;
		if (cnt%4<2) ans1[i]+=tot;else ans2[i]+=tot;
	}
}
void dfs(int t,int num)
{
	if (num>K) return;
	if (num+n-t+1<K) return;
	if (t>n){Calc();return;}
	dfs(t+1,num);
	flag[t]=1;
	dfs(t+1,num+1);
	flag[t]=0;
}
int main()
{
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	scanf("%d",&n);
	int ok=1;
	for (int i=1;i<=n;i++) scanf("%d",&L[i]);
	for (int i=1;i<=n;i++) scanf("%d",&R[i]);
	tot=1;
	for (int i=1;i<=n;i++)
	{
		tot*=(R[i]-L[i]+1);
		if (tot>2000000) ok=0;
	}
	scanf("%d",&K);
	if (ok)
	{
		dfs(1);
		for (int i=1;i<=n;i++)
			printf("%.6lf %.6lf\n",(double)suma[i]/tot,(double)sumb[i]/tot);
		return 0;
	}
	//for (int i=1;i<=n;i++) Mx=max(Mx,R[i]);
	//Dfs(1);
	//for (int i=1;i<=n;i++) printf("%.6lf %.6lf\n",ans1[i],ans2[i]);
	dfs(1,0);
	for (int i=1;i<=n;i++) printf("%.6lf %.6lf\n",ans1[i],ans2[i]);
}
