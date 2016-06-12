#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
int c[1005],w,i;
void solve(void)
{
    int x=0,p=0;
    LL sum=0LL,base=1LL;
    while(p<w)sum+=((LL)c[p++])*base,base*=10LL;
    //printf("%lld\n",sum);
    p=0;
    while(p<w)
    {
        if(sum%2!=c[p])return;
        sum/=2;
        p++;
    }
    for(int i = w-1; i >= 0; i--)
        printf("%d",c[i]);
    printf(",\n");
}
void change(void)
{
    int p = 0;
    while(p<w)
    {
    	//cout<<c[p];
        if(c[p])c[p]=0;
        else
        {
            c[p]=1;
            //cout<<endl;
            return;
        }
        p++;
    }
    c[w++]=1;
    //cout<<"1+"<<endl;
    return;
}
int main(void)
{
    freopen("dict.txt","w",stdout);
    //scanf("%d",&n);
    w=1;
    c[0]=1;
    while(w<=18)
    {
    	//printf("case:%d\n",++i);
        solve();
        change();
        //getchar();
    }
    return 0;
}
