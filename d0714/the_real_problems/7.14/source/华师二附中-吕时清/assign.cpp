#include <cstdio>
#include <algorithm>
#include <functional>
#include <utility>
static const int MAXN = 21;

int n, k;
int l[MAXN], r[MAXN];
int ct[MAXN][2] = {{ 0 }};

inline bool pair_first_cmp(const std::pair<int, int> &a, const std::pair<int, int> &b) {
    return (a.first == b.first) ? (a.second < b.second) : (a.first > b.first);
}
inline bool pair_second_cmp(const std::pair<int, int> &a, const std::pair<int, int> &b) {
    return (a.second < b.second);
}

int s[MAXN];
void dfs(int d)
{
    if (d == n) {
        static std::pair<int, int> p[MAXN];
        for (int i = 0; i < n; ++i) p[i] = std::make_pair(s[i], i);
        std::sort(p, p + n, pair_first_cmp);
        std::sort(p, p + k, pair_second_cmp);
        for (int i = 0; i < k; ++i)
            ++ct[p[i].second][(i & 3) == 1 || (i & 3) == 2];
    } else {
        for (s[d] = l[d]; s[d] <= r[d]; ++s[d]) dfs(d + 1);
    }
}

int main()
{
    freopen("assign.in", "r", stdin);
    freopen("assign.out", "w", stdout);

    scanf("%d", &n);
    if (n > 20) { puts("> <"); fclose(stdin); fclose(stdout); return 0; }
    for (int i = 0; i < n; ++i) scanf("%d", &l[i]);
    for (int i = 0; i < n; ++i) scanf("%d", &r[i]);
    scanf("%d", &k);

    int prod = 1;
    for (int i = 0; i < n; ++i) prod *= (r[i] - l[i] + 1);
    if (prod < 0) { puts("> <"); fclose(stdin); fclose(stdout); return 0; }
    dfs(0);
    for (int i = 0; i < n; ++i)
        printf("%.6lf %.6lf\n", (double)ct[i][0] / prod, (double)ct[i][1] / prod);

    fclose(stdin); fclose(stdout);
    return 0;
}

