#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
struct edge {
    int to;
    int weight;
    int prev;
}
inline int getint() {
    static int rtn, f;
    static char ch;
    rtn = 0; f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <=' 9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
int main() {
    
    return 0;
}