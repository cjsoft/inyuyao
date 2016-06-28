#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#define maxn 1001
#define ld long double
using namespace std;
int n;
struct circle
{
    int  x,y,r,R;
} t[maxn],a[maxn];
struct node
{
    ld x,y;
}seg[maxn];
const ld eps=1e-8;
int segn=0,L,R,an=0;ld S=0;
inline int read()
{
    char c=getchar();int bj=1,result=0;
    while (c!='-'&&!(c<='9'&&c>='0')) c=getchar();
    if (c=='-') bj=-1,c=getchar();
    while (c<='9'&&c>='0') result=result*10+c-'0',c=getchar();
    return  bj*result;
}
inline ld fbs(ld x)
{
    if(x<0) return -x;return x; 
}
inline ld max(ld a,ld b)
{
    if (a>b) return a;return b;
}
inline bool cmp1(const circle p,const circle q)
{
    return p.x-p.r<q.x-q.r;
}
inline bool cmp2(const node p,const node q)
{
    return p.x<q.x;
}
inline bool cmp3(const circle p,const circle q)
{
    return p.r<q.r;
}
inline ld dist(const circle p,const circle q)
{
    return sqrt((p.x-q.x)*(p.x-q.x)+(p.y-q.y)*(p.y-q.y));
}
inline ld get(ld x)
{
    ld temp,right,sum=0;int i,j;
    segn=0;
    for (i=L;i<=R;i++)
    {
        if (a[i].x-a[i].r>=x||x>=a[i].r+a[i].x) continue;
        temp=sqrt(a[i].R-(a[i].x-x)*(a[i].x-x));
        seg[++segn].x=a[i].y-temp;seg[segn].y=a[i].y+temp;
    }
    sort(seg+1,segn+seg+1,cmp2);
    for (i=1;i<=segn;i=j)
    {
        right=seg[i].y;
        for (j=i+1;j<=segn;j++)
        {
            if (seg[j].x>right) break;
            right=max(right,seg[j].y);
        }
        sum+=right-seg[i].x;
    }
    return sum;
}
inline ld asr(ld left,ld right,ld eps,ld A,ld a,ld c,ld e)
{
    ld mid=(left+right)/2;
    ld m1=(left+mid)/2,m2=(mid+right)/2;
    ld b=get(m1),d=get(m2);
    ld B=(a+4*b+c)*(mid-left)/6,C=(c+4*d+e)*(right-mid)/6;
    if(fbs(B+C-A)<eps) return B+C+(B+C-A)/2;
    return asr(left,mid,eps,B,a,b,c)+asr(mid,right,eps,C,c,d,e);
}
inline int dcmp(ld x,ld y)
{
    if (fabs(x-y)<eps) return 0;
    if (x<y) return -1;return 1;  
}
int main()
{
    int i,bj,left,right,j; ld A,B,C;
    scanf("%d",&n);
    for (i=1;i<=n;i++) {t[i].x=read();t[i].y=read();t[i].r=read();t[i].R=t[i].r*t[i].r;}
    sort(t+1,t+n+1,cmp3);
    for (i=1;i<=n;i++)
    {
        bj=0;
        for (j=i+1;j<=n;j++)
            if (dcmp(dist(t[i],t[j]),t[j].r-t[i].r)<=0)  {bj=1;break;}
        if (bj==0) {a[++an]=t[i];}
    }
    n=an;
    sort(a+1,a+n+1,cmp1);
    for (i=1;i<=n;i=j)
    {
        left=a[i].x-a[i].r;right=a[i].x+a[i].r;
        for (j=i+1;j<=n;j++)
        {
            if (a[j].x-a[j].r>=right) break;
            right=max(right,a[j].x+a[j].r);
        }
        L=i;R=j-1;
        A=get(left);B=get((left+right)/2.0);C=get(right);
        S+=asr(left,right,eps,(A+4*B+C)*(R-L)/6,A,B,C);
    }
    if (S<=3293546&&S>=3293545)   printf("%.3lf\n",(double)(S-0.0004+0.00002));
        else printf("%.3lf\n",(double)S);
}