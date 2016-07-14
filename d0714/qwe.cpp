#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib> 
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define SZ 10
#define MXN 1000007
using namespace std;
typedef long long ll;
int mat[117][11][11];
int tag[MXN];
int seq[MXN + 100];
int n;

void multi(int a, int b, int c) {
    static int mm[2][11][11];
    for (int i = 0; i < SZ; ++i)
        for (int j = 0; j < SZ; ++j)
            mm[0][i][j] = mat[a][i][j], mm[1][i][j] = mat[b][i][j], mat[c][i][j] = 0;//, swap(mm[0][i][j], mm[1][i][j]);
    for (int i = 0; i < SZ; ++i) {
        for (int j = 0; j < SZ; ++j) {
            for (int k = 0; k < SZ; ++k) {
                mat[c][i][j] = (mat[c][i][j] + (ll)mm[0][i][k] * mm[1][k][j] % MOD) % MOD;
                if (mat[c][i][j] < 0) mat[c][i][j] += MOD;
            }
        }
    }
}
void print(int n) {
    for (int i = 0; i < SZ; ++i) {
        for (int j = 0; j < SZ; ++j) {
            printf("%d ", mat[n][i][j]);
        }
        putchar('\n');
    }
}

inline int getint();
int main() {
    srand(998244353);
    for (int k = 1; k <= 3; ++k) {
        for (int i = 0; i < SZ; ++i) {
            for (int j = 0; j < SZ; ++j) {
                mat[k][i][j] = rand();
            }
        }
    }
    multi(1, 3, 4);
    multi(4, 2, 5);
    multi(1, 2, 6);
    multi(6, 3, 7);
    print(5);
    putchar('\n');
    print(7);
    return 0;
}

int getint() {
    static int rtn, f;
    static char ch;
    rtn = 0; f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}