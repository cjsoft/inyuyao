#include <stdio.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#define iterate(x, i, j) for (int i = head[x], j = buf[i].to; i; i = buf[i].prev, j = buf[i].to)
#define MXN 51527
#define INF 0x3f000000
using namespace std;
struct edge { int prev, to; } buf[MXN << 2 | 1];
int head[MXN], ctot = 1;
int dist[MXN];
char tag[MXN];
void addedge(int a, int b) {
    buf[ctot].to = b;
    buf[ctot].prev = head[a];
    head[a] = ctot++;
}
int n;
inline int inc(int a) {
    ++a;
    if (a > n) a = 1;
    return a;
}
inline int dec(int a) {
    --a;
    if (a < 1) a = n;
    return a;
}
int solve(int a, int b) {
    for (int i = 0; i <= n; ++i) {
        dist[i] = INF;
        tag[i] = 0;
    }
    int l = dec(a), r = inc(a);
    dist[a] = 0;
    tag[a] = 1;
    while (l != r) {
        dist[l] = dist[inc(l)] + 1;
        iterate(l, i, v) {
            if (tag[v])  {
                dist[l] = min(dist[l], dist[v] + 1);
            }
        }
        dist[r] = dist[dec(r)] + 1;
        iterate(r, i, v) {
            if (tag[v])  {
                dist[r] = min(dist[r], dist[v] + 1);
            }
        }
        if (dist[l] < dist[r])
            dist[r] = dist[l];
        else
            dist[l] = dist[r];
        l = dec(l);
        r = inc(r);
    }
    return dist[b];
}


int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        addedge(i, i + 1);
        addedge(i + 1, i);
    }
    addedge(n, 1);
    addedge(1, n);
    int a, b;
    for (int i = 0; i < n - 3; ++i) {
        scanf("%d %d", &a, &b);
        addedge(a, b);
        addedge(b, a);
    }
    int q;
    scanf("%d", &q);
    while (q--) {
        scanf("%d %d", &a, &b);
        printf("%d\n", solve(a, b));
    }
}
