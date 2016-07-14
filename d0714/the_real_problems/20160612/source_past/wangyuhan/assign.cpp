#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define red(i, a, b) for(int i = (a); i >= (b); i--)
#define ll long long
#define abs ABS
#define sqr SQR
#define PII pair<int, int>
#define MP make_pair
#define PB push_back
#define FI first
#define SE second

template<typename tn> void read(tn& a) {
	tn x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) {
		if (c == '-') f = -1;
		c = getchar();
	}
	while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
	a = x * f;
}
template<typename tn> void cmax(tn& a, tn b) { if (b > a) a = b; }
template<typename tn> void cmin(tn& a, tn b) { if (b < a) a = b; }
template<typename tn> tn abs(tn a) { return a < 0 ? -a : a; }
template<typename tn> tn sqr(tn a) { return a * a; }

const int N = 100;
struct node {
	int id, s;
}s[N];
int num[N][3], L[N], R[N];
int n, K;

bool cmp(node a, node b) {
	if (a.s != b.s) return a.s > b.s;
	else return a.id < b.id;
}
bool cmp1(node a, node b) {
	return a.id < b.id;
}
void check() {
	sort(s + 1, s + n + 1, cmp);
	sort(s + 1, s + K + 1, cmp1);
	rep(i, 1, K) {
		if (i % 4 == 1 || i % 4 == 0) num[s[i].id][0]++;
		else num[s[i].id][1]++;
	}
	rep(i, K + 1, n) num[s[i].id][2]++;
}
void dfs(int dep) {
	if (dep > n) check();
	else {
		rep(i, L[dep], R[dep]) {
			s[dep] = (node){dep, i};
			dfs(dep + 1);
		}
	}
}
void Print() {
	rep(i, 1, n) {
		double a = num[i][0], b = num[i][1], c = num[i][2];
		printf("%.6lf %.6lf\n", a / (a + b + c), b / (a + b + c));
	}
}
int main() {
	freopen("assign.in", "r", stdin);
	freopen("assign.out", "w", stdout);
	read(n);
	rep(i, 1, n) read(L[i]);
	rep(i, 1, n) read(R[i]);
	read(K);
	dfs(1);
	Print();
	return 0;
}