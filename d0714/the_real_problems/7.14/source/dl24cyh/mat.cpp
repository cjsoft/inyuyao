#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#define MOD 1000000007
#define SZ 10
#define MXN 1000007
using namespace std;
typedef long long ll;
int mat[117][11][11];
// int seq[MXN];
int tag[MXN];
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
map <int, int> seq;
inline int getint();
int main() {
    for (int i = 0; i < SZ; ++i) mat[0][i][i] = 1;
    for (int k = 1; k <= SZ; ++k) {
        for (int i = 0; i < SZ; ++i) {
            for (int j = 0; j < SZ; ++j) {
                mat[k][i][j] = getint();
            }
        }
    }
    n = getint();
    for (int i = 1; i <= n; ++i) seq.insert(make_pair(i * 101, getint())); 
    for (int k = 1; k <= 100; ++k) {
        seq.insert(make_pair(getint() * 101 + k, k + 10));
        for (int i = 0; i < SZ; ++i) {
            for (int j = 0; j < SZ; ++j) {
                mat[k + 10][i][j] = getint();
            }
        }
    }
    for (map<int, int>::iterator i = seq.begin(); i != seq.end(); i++)
        printf("%d\n", i->first);
        // multi(0, i->second, 0);
    print(0);
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