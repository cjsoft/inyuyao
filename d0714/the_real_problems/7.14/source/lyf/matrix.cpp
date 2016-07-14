#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iostream>

#define f(x, y, z) for (int x = (y), _end_ = (z); x <= _end_; ++ x)
#define g(x, y, z) for (int x = (y), _end_ = (z); x >= _end_; -- x)
#define fe(x, y, z) for (int x = (y), _end_ = (z); x != _end_; ++ x)
#define ge(x, y, z) for (int x = (y), _end_ = (z); x != _end_; -- x)
#define ms(a, b) memset(a, b, sizeof a);
using namespace std;

const int Flower_Dance = 1e9 + 7;
typedef long long LL;

inline int Plus(const int &A, const int &B) {
    if (A + B >= Flower_Dance) return A + B - Flower_Dance;
    return A + B;
}
struct matrix
{
    int data[10][10];
    matrix() {
        ms(data, 0);
    }
    friend inline matrix operator *(const matrix &A, const matrix &B) {
        matrix rtn;
        fe(i, 0, 10) fe(j, 0, 10) fe(k, 0, 10) rtn.data[i][j] = Plus(rtn.data[i][j], ((LL)A.data[i][k] * B.data[k][j]) % Flower_Dance);
        return rtn;
    }
};

namespace brute_force {
    const int maxn = 2009;
    matrix T[200];
    matrix A[maxn], tmp, PI;
    int a[maxn];
    int n, x;
    inline void solve() {
        f(i, 1, 10) fe(j, 0, 10) fe(k, 0, 10) scanf("%d", &T[i].data[j][k]);
        scanf("%d", &n);
        f(i, 1, n) scanf("%d", &a[i]);
        f(i, 1, 100) {
            scanf("%d", &x);
            fe(j, 0, 10) fe(k, 0, 10) scanf("%d", &T[10 + i].data[j][k]);
            a[n + i] = 10 + i;
            ge(j, n + i - 1, x) swap(a[j], a[j + 1]);
        }
        PI = T[a[1]];
        f(i, 2, n + 100) PI = PI * T[a[i]];
        fe(i, 0, 10) {
            fe(j, 0, 10) printf("%d ", PI.data[i][j]);
            puts("");
        }
    }
}

int main() {
freopen("matrix.in", "r", stdin);
freopen("matrix.out", "w", stdout);
    brute_force::solve();
fclose(stdin);
fclose(stdout);
return 0;
}
