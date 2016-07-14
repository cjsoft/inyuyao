#include<bits/stdc++.h>
using namespace std;
#define db double
#define MP make_pair
int read()
{
	int s=0,f=1;char ch=getchar();
	while(!('0'<=ch&&ch<='9')){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){s=(s<<3)+(s<<1)+ch-'0';ch=getchar();}
	return s*f;
}
int n,m,uu;
int l[30],r[30];
pair<int,int>s[30],a[30];
bool cmp(pair<int,int>a ,pair<int,int> b)
{
	return a.second<b.second;
}
double ana[30],anb[30];
void dfs(int k)
{
	if(k==n+1)
	   {
	   	for(int i=1;i<=n;i++)a[i]=s[i];
	   	sort(&a[1],&a[n+1]);
	   	sort(&a[1],&a[m+1],cmp);
	   	for(int i=0;i<m;i++)
	   	   {if((i&3)==1||(i&3)==2)
	   	       anb[a[i+1].second]++;
	   	    else
	   	       ana[a[i+1].second]++;
		   }
		return;
	   }
	for(int i=l[k];i<=r[k];i++)
	   {s[k]=MP(-i,k);
	    dfs(k+1);
	   }
}
int as[30],bs[30];
void dfs2(int k,int ss,db g)
{
	if(as[0]+bs[0]+n-k+1<m)return;
	if(as[0]>=m)return;
	if(k==n+1)
	   {if(bs[0]==0)return;
	    //for(int i=1;i<=n;i++)cout<<as[i]<<" ";cout<<endl;
	    //for(int i=1;i<=n;i++)cout<<bs[i]<<" ";cout<<endl;cout<<g<<endl;
	    int s1=0,s2=0;
		for(int i=1;i<=n;i++)
	       {s1+=as[i];
	        s2+=bs[i];
	        if(as[i])
	           {if(((s1+min(s2,m-as[0])-1)&3)==0||((s1+min(s2,m-as[0])-1)&3)==3)
			       ana[i]+=g;
			    else 
			       anb[i]+=g;
			   }
			else
			   if(s2<=m-as[0])
			      if(((s1+min(s2,m-as[0])-1)&3)==0||((s1+min(s2,m-as[0])-1)&3)==3)
			         ana[i]+=g;
			      else 
			         anb[i]+=g;
		   }
		return ;
	   }
	if(ss<l[k])
	   {dfs2(k+1,ss,g);
	    return;
	   }
	if(ss>r[k])
	   {as[0]++;as[k]=1;dfs2(k+1,ss,g);as[k]=0;as[0]--;
	    return;
	   }
	if(l[k]<=ss&&ss<=r[k])
	   {bs[0]++;bs[k]=1;dfs2(k+1,ss,g/(r[k]-l[k]+1));bs[k]=0;bs[0]--;
	    if(ss<r[k])
	       {as[0]++;as[k]=1;dfs2(k+1,ss,g*(r[k]-ss)/(r[k]-l[k]+1));as[k]=0;as[0]--;}
	   }
}
int main()
{
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)l[i]=read();
	double s=1;
	for(int i=1;i<=n;i++)r[i]=read(),uu=max(uu,r[i]),s*=(r[i]-l[i]+1);
	m=read();
	if(s<=2000000)
	   {dfs(1);
		for(int i=1;i<=n;i++)printf("%.6lf %.6lf\n",ana[i]/s,anb[i]/s);
	    return 0;
	   }
	for(int i=0;i<=uu;i++)
	   {//cout<<"ss"<<i<<endl;
	    dfs2(1,i,1);
	   }
	for(int i=1;i<=n;i++)printf("%.6lf %.6lf\n",ana[i],anb[i]);
	return 0;
}

