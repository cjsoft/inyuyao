#include<iostream>
#include<string.h>
#include<stdio.h>
#include<algorithm>
using namespace std;
int n,q;
int a[80005];
int b[80008];
void do1()
{
	int aa,bb,cc,dd;
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d%d%d",&dd,&aa,&bb,&cc);
		if(dd==1)
		{
			for(int j=aa;j<=bb;j++) a[j]+=cc;
		}
		else 
		{
			int tot=0;
			for(int j=aa;j<=bb;j++) b[++tot]=a[j];
			sort(b+1,b+1+tot);
			printf("%d\n",b[cc]);			
		}
	}
}

int tot=0;


int sa[80010];
int gg[80010];
int cmp(int x,int y)
{
    return x<y;
}
struct node{
    int ls,rs,val;
}tree[80010*20];
int build(int l,int r)
{
    int tmp=++tot;
    tree[tmp].val=0;
    if(l==r) return tmp;    
    int mid=(l+r)>>1;
    tree[tmp].ls=build(l,mid);
    tree[tmp].rs=build(mid+1,r);
    return tmp;
}
int add(int y,int l,int r,int pos,int V)
{
    int tmp=++tot;
    tree[tmp]=tree[y];
    tree[tmp].val+=V;   
    if(l==r) return tmp;
    int mid=(l+r)>>1;
    if(pos<=mid)   tree[tmp].ls=add(tree[y].ls,l,mid,pos,V);
        else tree[tmp].rs=add(tree[y].rs,mid+1,r,pos,V);
    return tmp;
}
int query(int x,int y,int l,int r,int pos)
{
    
    if(l==r) return  l;
    int mid=(l+r)>>1;
    int tmp=tree[tree[y].ls].val-tree[tree[x].ls].val;

    if(pos<=tmp)
    return query(tree[x].ls,tree[y].ls,l,mid,pos);
    else return query(tree[x].rs,tree[y].rs,mid+1,r,pos-tmp);
}


void do2()
{
    for(int i=1;i<=n;i++)
    {
        sa[i]=a[i];
    }   
    sort(sa+1,sa+1+n,cmp);    
    int nn=0;
    for(int i=1;i<=n;i++)
    {
        if(i==1||sa[i]!=sa[nn])
        sa[++nn]=sa[i];
    }   
    gg[0]=build(1,nn);
    for(int i=1;i<=n;i++)
    {
        int p=lower_bound(sa+1,sa+1+n,a[i])-sa;  
       // cout<<p<<endl;
        gg[i]=add(gg[i-1],1,nn,p,1);
    }
    for(int i=1;i<=q;i++)   
    {
        int aa,bb,cc,dd;
        scanf("%d%d%d%dd",&dd,&aa,&bb,&cc);
        
        printf("%d\n",sa[query(gg[aa-1],gg[bb],1,nn,cc)]);
    }

}
	
	

int main()
{
	freopen("kth.in","r",stdin);
	freopen("kth.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	scanf("%d",&q);
	if(n<=1000&&q<=1000)
	{
		do1();
		return 0;
	}
	do2();
}

