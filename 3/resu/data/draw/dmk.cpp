/* Copyright 2016 AcrossTheSky */
#include <iostream>
#include <cstdio>
#include <utility>
#include <cassert>
#include <map>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#define REP(i, a, b) for (int i = (a); i <= (b); ++i)
#define PER(i, a, b) for (int i = (a); i >= (b); --i)
#define RVC(i, c) fot (int i = 0; i < (c).size(); ++i)
#define RED(k, u) for (int k = head[(u)]; k; k = edge[k].next)
#define lowbit(x) ((x) & (-(x)))
#define CL(x, v) memset(x, v, sizeof x)
#define MP std::make_pair
#define PB push_back
#define FR first
#define SC second
#define rank rankk
#define next nextt
#define link linkk
#define index indexx
#define abs(x) ((x) > 0 ? (x) : (-(x)))
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

template<class T> inline
bool getmin(T *a, const T &b) {
    if (b < *a) {
        *a = b;
        return true;
    }
    return false;
}

template<class T> inline
bool getmax(T *a, const T &b) {
    if (b > *a) {
        *a = b;
        return true;
    }
    return false;
}

template<class T> inline
void read(T *a) {
    char c;
    while (isspace(c = getchar())) {}
    bool flag = 0;
    if (c == '-') flag = 1, *a = 0;
    else
        *a = c - 48;
    while (isdigit(c = getchar())) *a = *a * 10 + c - 48;
    if (flag) *a = -*a;
}
const int mo = 1000000007;
template<class T>
T pow(T a, T b, int c = mo) {
    T res = 1;
    for (T i = 1; i <= b; i <<= 1, a = 1LL * a * a % c) if (b & i) res = 1LL * res * a % c;
    return res;
}
/*======================= TEMPLATE =======================*/
string str(int x) {
    string s;
    while (x) s = char('0' + x % 10) + s, x /= 10;
    return s;
}
#include <ctime>
int n;
int f[100000];
int get(int u) {
    if (u == f[u]) return u;
    else return f[u] = get(f[u]);
}
int main() {
    srand(time(0));
    REP(i, 1, 20) {
        ofstream fout("draw" + str(i) + ".in");
        n = pow(log(i) / log(1.1), 3);
        n = max(n, 10);
        fout << n << endl;
        REP(i, 1, n) f[i] = i;
        REP(i, 2, n) {
            int a = rand() % n + 1;
            int b = rand() % n + 1;
            while (get(a) == get(b)) {
                a = rand() % n + 1;
                b = rand() % n + 1;
            }
            f[get(a)] = get(b);
            int c = rand() % 1000000 + 1;
            fout << a <<' ' << b << ' ' << c << endl;
        }
    }
    return 0;
}
