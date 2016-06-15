#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <random>

using namespace std;

const int maxn=1110;
int a[maxn][maxn];

int main(int argc,char **argv) {
    if(argc!=3){
        fprintf(stderr,"Bad usage.\n");
        return EXIT_FAILURE;
    }

    int T=atoi(argv[1]),n=atoi(argv[2]);
    random_device rd;
    mt19937 eng(rd());

    printf("%d\n",T);
    while(T--){
        printf("%d\n",n);
        for(int i=0;i<n;++i){
            for(int j=0;j<=i;++j)
                printf(j==n-1?"%d\n":"%d ",a[j][i]);
            for(int j=i+1;j<n;++j)
                printf(j==n-1?"%d\n":"%d ",a[i][j]=!(eng()%n));
        }
    }

    return 0;
}
