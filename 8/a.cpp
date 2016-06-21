#include<cstdio>  
#define maxn 300100  
  
int n,l,f[maxn],a,b,use[maxn];  
  
int find(int a) {
    int t = a, tmp;
    for (; f[t] != t; t = f[t]);
    for (; f[a] != a; tmp = f[a], f[a] = t, a = tmp);
}
  
int main()  
{  
    scanf("%d%d",&n,&l);  
    for (int i=1;i<=l;i++) f[i]=i;  
    for (int i=1;i<=n;i++)  
    {  
        scanf("%d%d",&a,&b);  
        if (!use[find(a)])  
        {  
            use[f[a]]=1;  
            if (f[a]!=find(b)) f[f[a]]=f[b]; //避免出现环，环等价于根无法放   
            puts("LADICA");  
        }  
        else if (!use[find(b)])  
        {  
            use[f[b]]=1;  
            //a的并查集无法放，那么就没有合并的必要了   
            puts("LADICA");  
        }  
        else puts("SMECE");  
    }  
    return 0;  
}  