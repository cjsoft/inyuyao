#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
#include<time.h>
using namespace std;
int n,m,x[10];
long double p;
struct point
{
	int x,y;
	long double p;
}a[200010];
inline long double cha(point a,point b,point c)
{
	return (long double)(b.x-a.x)*(c.y-a.y)-(long double)(c.x-a.x)*(b.y-a.y);
}
inline double dis(point a,point b)
{
	return (long double)(a.x-b.x)*(a.x-b.x)+(long double)(a.y-b.y)*(a.y-b.y);
}
inline bool cmp(point b,point c)
{
	return b.p<c.p;
}
inline int sf(int l,int r,int x,int y)
{
	if(l==r)
	  return l;
	int m=(l+r>>1);
	if(cha(a[x],a[m],a[y])>cha(a[x],a[m+1],a[y]))
	  return sf(l,m,x,y);
	else
	  return sf(m+1,r,x,y);
}
int main()
{
	freopen("area.in","r",stdin);
	freopen("area.out","w",stdout);
	srand(time(0));
	int i,j,k,l;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	  scanf("%d%d",&a[i].x,&a[i].y);
    for(i=2;i<=n;i++)
      if(a[i].x<a[1].x || a[i].x==a[1].x && a[i].y<a[1].y)
        swap(a[1],a[i]);
    for(i=2;i<=n;i++)
      if(a[i].x==a[1].x)
        a[i].p=1e18;
      else
        a[i].p=(long double)(a[i].y-a[1].y)/(a[i].x-a[1].x);
    sort(a+2,a+n+1,cmp);
    a[n+1]=a[1];
    for(i=2,j=1;i<=n+1;i++)
      {
       a[++j]=a[i];
       if(fabs(cha(a[j-2],a[j-1],a[j]))<1e-9 && dis(a[j-2],a[j])<dis(a[j-2],a[j-1]))
         j--;
       else
         while(j>=3 && cha(a[j-2],a[j-1],a[j])<1e-9)
           {
            a[j-1]=a[j];
            j--;
           }
      }
    n=j-1;
    for(i=1;i<=n;i++)
      a[i+n]=a[i];
    if(n<=4)
      {
       for(i=2;i<n;i++)
         p+=cha(a[1],a[i],a[i+1]);
       printf("%.1Lf\n",p/2);
      }
    else if(n<=4000)
      {
       for(i=1;i<=n;i++)
         {
          for(l=i+3;l+1<i+n && cha(a[i],a[i+2],a[l])<cha(a[i],a[i+2],a[l+1]);l++);
          p=max(p,cha(a[i],a[i+1],a[i+2])+cha(a[i],a[i+2],a[l]));
          for(j=i+3,k=i+1;j<i+n-1;j++)
            {
             for(;k+1<j && cha(a[i],a[k],a[j])<cha(a[i],a[k+1],a[j]);k++);
             for(;l==j || l+1<i+n && cha(a[i],a[j],a[l])<cha(a[i],a[j],a[l+1]);l++);
             p=max(p,cha(a[i],a[k],a[j])+cha(a[i],a[j],a[l]));
            }
         }
       printf("%.1Lf\n",p/2);
      }
    else
      {
       while(clock()<500)
         {
          do
            {
             x[1]=((rand()<<15)+rand())%n+1;
             x[2]=((rand()<<15)+rand())%n+1;
             x[3]=((rand()<<15)+rand())%n+1;
             x[4]=((rand()<<15)+rand())%n+1;
             sort(x+1,x+5);
            }
          while(x[1]==x[2] || x[2]==x[3] || x[3]==x[4]);
          for(k=1,l=0;k<=n;k++)
            if(k&1)
              {
               i=sf(x[1],x[3],x[1],x[3]);
               j=sf(x[3],x[1]+n,x[3],x[1]+n);
               if(i==x[2] && (j-1)%n+1==x[4])
                 {
                  if(++l==2)
                    break;
                 }
               else
                 {
                  l=0;
                  x[2]=i;
                  x[4]=(j-1)%n+1;
                  sort(x+1,x+5);
                 }
              }
            else
              {
               i=sf(x[2],x[4],x[2],x[4]);
               j=sf(x[4],x[2]+n,x[4],x[2]+n);
               if(i==x[3] && (j-1)%n+1==x[1])
                 {
                  if(++l==2)
                    break;
                 }
               else
                 {
                  l=0;
                  x[3]=i;
                  x[1]=(j-1)%n+1;
                  sort(x+1,x+5);
                 }
              }
          p=max(p,cha(a[x[1]],a[x[2]],a[x[3]])+cha(a[x[1]],a[x[3]],a[x[4]]));
         }
       printf("%.1Lf\n",p/2);
      }
	return 0;
}

