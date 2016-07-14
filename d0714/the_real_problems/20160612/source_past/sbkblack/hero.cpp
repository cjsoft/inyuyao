#include<cstdio>
#include<cctype>
#include<cstring>
#include<queue>

using namespace std;

typedef long long ll;

template<typename T> void read(T& v) {
	v = 0; static char ch;
	while(!isdigit(ch = getchar()));
	do { v = v*10+ch-'0'; } while(isdigit(ch = getchar()));
}

const int N = 3e2+5;
const int M = 1e5;
const int MS = M*8;

int n, m, K, t[N][N];

ll ans;

int d[M], iq[M], pre[M];

struct Edge {
	int t, w, c;
	Edge(){}
	Edge(int t, int w, int c):t(t),w(w),c(c) {}
} e[M];

int head[M], nx[MS], ct = 1;

void insert(int s, int t, int w, int c) {
	nx[++ct] = head[s]; head[s] = ct; e[ct] = Edge(t, w, c);
	nx[++ct] = head[t]; head[t] = ct; e[ct] = Edge(s, 0, -c);
}

ll mcf(int s, int t) {
	queue<int> q;
	long long ans = 0;
	while(1) {
		memset(d, 127, sizeof(d));
		int inf = d[t];
		d[s] = 0;
		q.push(s);
		while(q.size()>0) {
			int p = q.front(); q.pop();
			for(int r = head[p]; r; r = nx[r]) if(e[r].w>0) {
				if(d[p]+e[r].c<d[e[r].t]) {
					d[e[r].t] = d[p]+e[r].c;
					pre[e[r].t] = r;
					if(!iq[e[r].t]) {
						iq[e[r].t] = true;
						q.push(e[r].t);
					}
				}
			}
			iq[p] = false;
		}
		if(d[t] == inf) return ans;
		int f = 1;
		ans+=d[t];
		for(int p = t; p!=s; p = e[pre[p]^1].t) {
			--e[pre[p]].w;
			++e[pre[p]^1].w;
		}
	}
}


int main() {
	freopen("hero.in", "r", stdin);
	freopen("hero.out", "w", stdout);
	read(n); read(m); read(K);
	int S = (n+1)*m, SS = S+1, T = S+2;
	insert(S, SS, 2, 0);
	for(int i = 0; i<m; ++i) {
		insert(SS, i, 1, 0);
		insert(n*m+i, T, 1, 0);
	}
	for(int i = 1; i<n; ++i)
		for(int j = 1; j<m; ++j)
			insert(i*m+j-1, i*m+j, 2, K),
			insert(i*m+j, i*m+j-1, 2, K);
	for(int i = 0; i<n; ++i)
		for(int j = 0; j<m; ++j) {
			read(t[i][j]);
			insert(i*m+j, i*m+m+j, 1, t[i][j]);
		}
	printf("%lld\n", mcf(S, T));
	return 0;
}
