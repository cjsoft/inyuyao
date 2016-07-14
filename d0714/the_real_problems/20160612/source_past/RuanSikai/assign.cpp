#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef double DB;

const int maxn = 30;

int n, k;
LL A[maxn], B[maxn], sum;

struct _seg {
	int l, r;
} seg[maxn];

struct _data {
	int sco, id;
} data[maxn], tmp[maxn];

inline bool cmp1(_data a, _data b) {
	return a.sco != b.sco ? a.sco > b.sco : a.id < b.id;
}

inline bool cmp2(_data a, _data b) {
	return a.id < b.id;
}

inline int iread() {
	int f = 1, x = 0; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) f = ch == '-' ? -1 : 1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
	return f * x;
}

inline void dfs(int x) {
	if(x == n) {
		sum++;
		for(int i = 0; i < n; i++) tmp[i] = data[i];
		sort(tmp, tmp + n, cmp1);
		sort(tmp, tmp + k, cmp2);
		for(int i = 0; i < k; i++)
			if((i + 1 >> 1) & 1) B[tmp[i].id]++;
			else A[tmp[i].id]++;
		return;
	}
	for(int i = seg[x].l; i <= seg[x].r; i++) {
		data[x] = (_data){i, x};
		dfs(x + 1);
	}
}

int main() {
	freopen("assign.in", "r", stdin);
	freopen("assign.out", "w", stdout);
	n = iread();
	for(int i = 0; i < n; i++) seg[i].l = iread();
	for(int i = 0; i < n; i++) seg[i].r = iread();
	k = iread();

	dfs(0);
	for(int i = 0; i < n; i++) printf("%.6f %.6f\n", A[i] /(DB) sum, B[i] / (DB)sum);
	return 0;
}

