#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <random>

using namespace std;

int main(int argc,char **argv) {
    if(argc!=3){
        printf("Bad usage\n");
        return EXIT_FAILURE;
    }

    int n=atoi(argv[1]),Q=n-1,type=atoi(argv[2]);
    random_device RD;
    mt19937 eng(RD());
    uniform_int_distribution<int> gen(-5000,10000);
    uniform_int_distribution<int> dif(-40,40);
    uniform_int_distribution<int> getid(1,n);
    printf("%d\n",n);
    for(int i=0;i<n;++i) printf(i==n-1?"%d\n":"%d ",gen(eng));
    printf("%d\n",Q);
    while(Q--){
        int t,a,b,k;
        t=2;
        if(2==type){ if(0==eng()%20)t=1; }
        a=getid(eng);
        b=getid(eng);
        if(a>b)swap(a,b);
        if(t==1){
            k=dif(eng);
        }else{
            uniform_int_distribution<int> kth(1,b-a+1);
            k=kth(eng);
        }
        printf("%d %d %d %d\n",t,a,b,k);
    }

    return 0;
}
