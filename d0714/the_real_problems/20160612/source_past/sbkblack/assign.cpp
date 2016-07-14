#include<cstdio>
#include<cctype>
#include<algorithm>

using namespace std;

typedef long long ll;

template<typename T> void read(T& v) {
	v = 0; static char ch;
	while(!isdigit(ch = getchar()));
	do { v = v*10+ch-'0'; } while(isdigit(ch = getchar()));
}

const int N = 25+5;

int n, K, L[N], R[N];

namespace ALGO1 {
	int mark[N], tmp[N], MX;
	
	int A[N], B[N];
	
	bool cmp(int x, int y) {
		return x>y;
	}
	
	void dfs(int x) {
		if(x==n) {
			for(int i = 0; i<n; ++i) tmp[i] = mark[i]*100+n-i;
			sort(tmp, tmp+n, cmp);
			for(int i = 0; i<K; ++i) tmp[i] = n-tmp[i]%100;
			sort(tmp, tmp+K);
			for(int i = 0; i<K; ++i) {
				int v = tmp[i];
				if((i&3)==1 || (i&3)==2) ++B[v]; else ++A[v];
			}
			return;
		}
		int& i = mark[x];
		for(i = L[x]; i<=R[x]; ++i)
			dfs(x+1);
	}
	
	void algo1(int m) {
		MX = m;
		dfs(0);
		for(int i = 0; i<n; ++i) {
			printf("%.6f %.6f\n", A[i]*1.0/m, B[i]*1.0/m);
		}
	}
}

namespace ALGO2 {
	
	int C[N];
	
	int cur, eq;
	
	long double dfs(int x, int y, int z) {
		if(z<0 || y<0) return 0;
		if(x==n) return y==0&&z>=0?1:0;
		if(x==cur) return dfs(x+1, y, z-1);
		if(x<cur) {
			if(R[x]<eq) return (C[x])*dfs(x+1, y, z);
			if(L[x]>=eq) return (C[x])*dfs(x+1, y-1, z-1);
			return (R[x]-eq+1)*dfs(x+1, y-1, z-1) + (eq-L[x])*dfs(x+1, y, z);
		} else {
			if(R[x]<=eq) return (C[x])*dfs(x+1, y, z);
			if(L[x]>eq) return (C[x])*dfs(x+1, y, z-1);
			return (R[x]-eq)*dfs(x+1, y, z-1) + (eq-L[x]+1)*dfs(x+1, y, z);
		}
	}
	
	void algo2() {
		long double m = 1;
		for(int i = 0; i<n; ++i) {
			m *= C[i] = (R[i]-L[i]+1);
		}
		for(int i = 0; i<n; ++i) {
			long double A = 0, B = 0;
			cur = i;
			for(int j = 0; j<=i; ++j) {
				long double v = 0;
				for(int k = L[i]; k<=R[i]; ++k){
					eq = k;
					v+=dfs(0, j, K);
				}
				if((j&3)==1 || (j&3)==2) B+=v; else A+=v;
			}
			printf("%.6llf %.6llf\n", A/m, B/m);
		}
	}
}


int main() {
	freopen("assign.in", "r", stdin);
	freopen("assign.out", "w", stdout);
	read(n);
	for(int i = 0; i<n; ++i) read(L[i]);
	for(int i = 0; i<n; ++i) read(R[i]);
	read(K);
	
	{
		bool flag = true;
		ll m = 1;
		for(int i = 0; i<n; ++i) {
			m *= (R[i]-L[i]+1);
			if(m>1e6) {
				flag = false;
				break;
			}
		}
		//if(flag) {
			ALGO1::algo1(m);
			return 0;
		//}
	}
	
	ALGO2::algo2();
	return 0;
}
