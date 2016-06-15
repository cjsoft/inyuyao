#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <random>
#include <string>

using namespace std;

int main(int argc,char **argv) {
    if(argc!=3){
        fprintf(stderr,"Bad usage.\n");
        return EXIT_FAILURE;
    }

    int n=atoi(argv[1]),cc=atoi(argv[2]);

    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<char> gen('a','a'+cc-1);
    uniform_int_distribution<int> sizegen(10,int(sqrt(n)));
    uniform_int_distribution<int> sizegap(1,10);
    string st1; int sl1=sizegen(eng);
    string st2; int sl2=sizegen(eng);
    for(int i=0;i<sl1;++i)st1.push_back(gen(eng));
    for(int i=0;i<sl2;++i)st2.push_back(gen(eng));

    while(n){
        int gap;
        gap=min(n,sizegap(eng)); n-=gap; while(gap--)putchar(gen(eng));
        if(n>=sl1){n-=sl1;printf("%s",st1.c_str());}
        gap=min(n,sizegap(eng)); n-=gap; while(gap--)putchar(gen(eng));
        if(n>=sl2){n-=sl2;printf("%s",st2.c_str());}
        gap=min(n,sizegap(eng)); n-=gap; while(gap--)putchar(gen(eng));
    }
    putchar('\n');
    return 0;
}
