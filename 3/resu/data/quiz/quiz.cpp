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

struct BigInt {
    int a[200], len;
    int& operator [] (const int &x) {return a[x];}
    BigInt() {}
    BigInt(int x) { a[len = 0] = x; }
    void add(int k) {
        a[k] = 1; len = k;
    }
    void div() {
        int d = 0;
        PER(i, len, 0) {
            int x = d * 10 + a[i];
            d = x % 2;
            a[i] = x / 2;
        }
        if (len && !a[len]) --len;
    }
    void print() {
        PER(i, len, 0) printf("%d", a[i]);
        puts("");
    }
};
bool get(BigInt a, int k) {
    while (k--) a.div();
    return a[0] & 1;
}
vector<BigInt> a, b, c;

int main() {
    int n;
    while(cin >> n) {
        c.clear();
        c.PB(BigInt(0));
        int k = 0;
        while (n) {
            a.clear(); b.clear();
            for (int i = 0; i < c.size(); ++i) {
                if (!get(c[i], k)) {
                    BigInt tmp = c[i];
                    a.PB(tmp);
                    tmp.add(k);
                    b.PB(tmp);
                    if (!(--n)) {
                        tmp.print();
                        break;
                    }
                }
            }
            c.clear();
            for (int i = 0; i < a.size(); ++i) c.PB(a[i]);
            for (int i = 0; i < b.size(); ++i) c.PB(b[i]);
            ++k;
        }
    }
    return 0;
}
