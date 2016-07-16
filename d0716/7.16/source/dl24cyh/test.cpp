#include <iostream>
#include <cstdio>
#include <cstring>
#define INF 0x3f3f3f3f
#define MXN 1007
using namespace std;
int a[MXN], b[MXN];
int n;
template<typename T>
inline void checkmin(T &a, T b) { if (a > b) a = b; }
int main() {
    scanf("%d", &n);
    int suma = 0, mb = INF;
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", a + i, b + i);
        suma += a[i];
        checkmin(mb, b[i]);
    }
    printf("%d\n", suma + mb);
}
