#include <stdio.h>
#include <string.h>
const int N = 1000000 + 10;
char str[N];
int next[N];
void makeNext(char *str)
{
    int i=0,j=-1;
    next[0] = -1;
    while(str[i])
    {
        if(j==-1||str[i]==str[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
            j = next[j];
    }
}
int main()
{
    
    int n;
    int tCase = 1;
    while(true)
    {
        scanf("%d",&n);
        if(n==0)
            break;
        scanf("%s",str);
        makeNext(str);
        printf("Test case #%d\n",tCase++);
        for(int i=2; i<=n; ++i)
        {
            if(i%(i-next[i])==0)//next[i]!=0,如果为0，循环节是本身
                printf("%d %d\n",i,i - next[i]);
            
        }
        puts("");
        
    }
    return 0;
}
