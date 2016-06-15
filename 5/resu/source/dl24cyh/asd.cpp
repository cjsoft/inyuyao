#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
int a[] = {3, 4, 5, 6, 7};
int main() {
    printf("%d\n", upper_bound(a, a + 5, 7) - a);

}