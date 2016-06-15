#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[1007];
int qqsolve(int p, int q, int k) {
    int l = p, r = q, mid;
    while (l + 1 < r) {
        mid = l + ((r - l) >> 1);
        if (a[mid] < k) l = mid;
        else r = mid;
    }
    return l - p + 1;
}
int main() {
    FILE *f = fopen("qq.in", "r");
    for (int i = 0; i < 100; ++i) {
        fscanf(f, "%d", a + i);
    }
    sort(a, a + 100);
    while (true) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        printf("%d\n", qqsolve(a, b, c));
    }
    return 0;
}