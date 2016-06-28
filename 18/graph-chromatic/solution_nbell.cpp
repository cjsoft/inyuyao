#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 200000;
const int M = 10;
const int MOD = (int)1e9 + 7;

int c, result, mark[N], color[N], ways[N][M];
std::vector<int> graph[N], order, children[N], dependency[N], vertices;

void dfs(int p, int u)
{
    order.push_back(u);
    mark[u] = 1;
    for (int v : graph[u]) {
        if (v != p) {
            if (mark[v]) {
                if (~mark[v] >> 1 & 1) {
                    dependency[u].push_back(v);
                    mark[v] |= 4;
                }
            } else {
                children[u].push_back(v);
                dfs(u, v);
            }
        }
    }
    mark[u] |= 2;
}

void update(int &x, int a)
{
    x += a;
    if (x >= MOD) {
        x -= MOD;
    }
}

void generate(int i, int m)
{
    if (i < (int)vertices.size()) {
        int v = vertices[i];
        for (color[v] = 0; color[v] <= m; ++ color[v]) {
            generate(i + 1, std::max(color[v] + 1, m));
        }
    } else if (m <= c) {
        for (int u : order) {
            for (int j = 0; j <= m; ++ j) {
                bool found = ~color[u] && j != color[u];
                for (int v : dependency[u]) {
                    found |= j == color[v];
                }
                ways[u][j] = !found;
            }
            for (int v : children[u]) {
                int sum = (long long)ways[v][m] * (c - m) % MOD;
                for (int j = 0; j < m; ++ j) {
                    update(sum, ways[v][j]);
                }
                for (int j = 0; j <= m; ++ j) {
                    ways[u][j] = (long long)ways[u][j] * (sum + MOD - ways[v][j]) % MOD;
                }
            }
        }
        int base = 1;
        for (int i = 0; i < m; ++ i) {
            base = (long long)base * (c - i) % MOD;
        }
        for (int j = 0; j < m; ++ j) {
            update(result, (long long)base * ways[0][j] % MOD);
        }
        update(result, (long long)base * (c - m) % MOD * ways[0][m] % MOD);
    }
}

int main()
{
    int n, m;
    scanf("%d%d%d", &n, &m, &c);
    for (int i = 0; i < m; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --;
        b --;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    memset(mark, 0, sizeof(mark));
    dfs(-1, 0);
    for (int i = 0; i < n; ++ i) {
        if (mark[i] >> 2) {
            vertices.push_back(i);
        }
    }
    std::reverse(order.begin(), order.end());
    memset(color, -1, sizeof(color));
    result = 0;
    generate(0, 0);
    printf("%d\n", result);
}
