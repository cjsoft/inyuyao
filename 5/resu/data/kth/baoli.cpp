#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>

using namespace std;

const int maxn=100900;
const int MXV=100010;
int a[maxn];
int tmp[maxn],tc;
__attribute__((optimize("O2"))) int main() {
    int n; scanf("%d",&n);
    for(int i=0;i<n;++i){ scanf("%d",a+i); }
    int q;scanf("%d",&q);
    while(q--){
        int t,L,R,x;
        scanf("%d%d%d%d",&t,&L,&R,&x); --L; --R;
        if(t==1){
            for(int i=L;i<=R;++i)a[i]+=x;
        }else{
            tc=0;
            for(int i=L;i<=R;++i)tmp[tc++]=a[i];
            nth_element(tmp,tmp+x-1,tmp+tc);
            printf("%d\n",tmp[x-1]);
        }
    }
    return 0;
}
