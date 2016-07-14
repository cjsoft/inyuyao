#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <climits>
using namespace std;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') f = -1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
	return x * f;
}

const int maxn = 35;
int n, K;
int l[maxn], r[maxn];
int a[maxn], b[maxn];

bool cmp(int x, int y) {
	if (a[x] == a[y]) return x < y;
	return a[x] > a[y];
}

int cnt[maxn][2];
int tot;
void serch(int x) {
	if (x > n) {
		tot++;
		sort(b + 1, b + 1 + n, cmp);
		sort(b + 1, b + 1 + K);
		for (int i = 1; i <= K; i++) cnt[b[i]][(i >> 1) & 1]++;
		return;
	}
	for (int i = l[x]; i <= r[x]; i++) {
		a[x] = i;
		serch(x + 1);
	}
}

int main() {
	freopen("assign.in", "r", stdin);
	freopen("assign.out", "w", stdout);
	n = read();
	for (int i = 1; i <= n; i++) b[i] = i;
	for (int i = 1; i <= n; i++) l[i] = read();
	for (int i = 1; i <= n; i++) r[i] = read();
	K = read();
	serch(1);
	for (int i = 1; i <= n; i++) {
		printf("%.6lf %.6lf\n", 1. * cnt[i][0] / tot, 1. * cnt[i][1] / tot);
	}
	return 0;
}
