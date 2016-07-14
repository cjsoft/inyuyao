#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <vector>
#include <string>
#define memcle(a) memset(a, 0, sizeof(a))
#define fo(i, a, b) for (i = a; i <= b; i++)
#define fd(i, a, b) for (i = a; i >= b; i--)
#define sqr(x) ((x) * (x))
typedef long long LL;
typedef double LD;
using namespace std;

const int N = 30;
vector<int> worst, best;
vector<LD> ans;
int n, k;
LD lf[N][N], lg[N][N], rf[N][N], rg[N][N], p[N];

class SemifinalAssignment
{
	public:
	
	LD len(int l, int r) {return (r < l) ? 0 : (r - l + 1);}
	vector<double> getProbability(vector<int> worst, vector<int> best, int k)
	{
		int i, j, cur, lim, l;
		n = worst.size();
		vector<LD> ans; 
		ans.resize(2 * n); 
		fo(i, 0, 2 * n - 1) ans[i] = 0;
		
		fo(cur, 0, n - 1)
			fo(lim, worst[cur], best[cur])
			{
				fo(i, 0, cur - 1) p[i] = len(max(worst[i], lim), best[i]) / len(worst[i], best[i]);
				p[cur] = 1;
				fo(i, cur + 1, n - 1) p[i] = len(max(worst[i], lim + 1), best[i]) / len(worst[i], best[i]);
				
				//注意标号是往后移了1
				
				lf[0][0] = 1;
				lg[0][0] = 0;
				fo(i, 1, n)
					fo(j, 0, i)
					{
						LD P = p[i - 1];
						lg[i][j] = (j > 0) ? lf[i - 1][j - 1] * P : 0;
						lf[i][j] = lg[i][j] + lf[i - 1][j] * (1 - P);
					}
					
				rf[n + 1][0] = 1;
				rg[n + 1][0] = 0;
				fd(i, n, 1)
					fo(j, 0, n - i + 1)
					{
						LD P = p[i - 1];
						rg[i][j] = (j > 0) ? rf[i + 1][j - 1] * P : 0;
						rf[i][j] = rg[i][j] + rf[i + 1][j] * (1 - P);			
					}
				
				LD P = 1 / len(worst[cur], best[cur]);
				fo(i, 0, n - 1)
					fo(l, 1, min(k, i + 1))
					{
						int r = k - l;
						ans[2 * i + (l / 2) % 2] += P * lg[i + 1][l] * rf[i + 2][k - l];
					}
			}
		
		return ans;
	}
} T;

char temp[2];
string fi, ft;

int main()
{
		fi = "assign";
		fi += ".in";
		
		ft = "assign";
		ft += ".out";
		
		freopen(fi.c_str(), "r", stdin);
		freopen(ft.c_str(), "w", stdout);
		
		worst.clear();
		best.clear();
		ans.clear();
		memcle(lf); memcle(rf); memcle(lg); memcle(rg);
		
		scanf("%d", &n);
		worst.resize(n);
		best.resize(n);
		for (int i = 0; i < n; i++) scanf("%d", &worst[i]);
		for (int i = 0; i < n; i++) scanf("%d", &best[i]);
		scanf("%d", &k);
		ans = T.getProbability(worst, best, k);
		for (int i = 0; i < 2 * n; i++) printf("%.6f%c", ans[i], (i % 2) ? '\n' : ' ');
	return 0;
}
