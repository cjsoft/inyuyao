#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <queue>
#include <tuple>
#include <vector>

const int N = 200000;
const int M = N + 11;
const int MOD = (int)1e9 + 7;

int result, n, c, edge_count, a[M], b[M], degree[N], head[N], to[M + M], next_edge[M + M], selected[N], same[N], diff[N], power[N], color[N];
bool used[M];
std::vector<int> selected_vertices;
std::vector<std::tuple<int, int, int>> edges;

void add_edge(int u, int v)
{
    to[edge_count] = v;
    next_edge[edge_count] = head[u];
    head[u] = edge_count ++;
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
    if (i < (int)selected_vertices.size()) {
        int v = selected_vertices[i];
        for (color[v] = 0; color[v] <= m; ++ color[v]) {
            generate(i + 1, std::max(color[v] + 1, m));
        }
    } else if (m <= c) {
        int base = 1;
        for (int i = 0; i < m; ++ i) {
            base = (long long)base * (c - i) % MOD;
        }
        for (auto&& tp : edges) {
            int a, b, c;
            std::tie(a, b, c) = tp;
            if (color[a] == color[b]) {
                base = (long long)base * same[c] % MOD;
            } else {
                base = (long long)base * diff[c] % MOD;
            }
        }
        update(result, base);
    }
}

int main()
{
    int m;
    scanf("%d%d%d", &n, &m, &c);
    edge_count = 0;
    memset(head, -1, sizeof(head));
    memset(degree, 0, sizeof(degree));
    for (int i = 0; i < m; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --;
        b --;
        add_edge(a, b);
        add_edge(b, a);
        degree[a] ++;
        degree[b] ++;
    }

    if (m == n - 1) {
        int result = c;
        for (int i = 1; i < n; ++ i) {
            result = (long long)result * (c - 1) % MOD;
        }
        printf("%d\n", result);
        return 0;
    }

    std::vector<int> queue;
    for (int i = 0; i < n; ++ i) {
        if (degree[i] == 1) {
            queue.push_back(i);
        }
    }
    for (int h = 0; h < (int)queue.size(); ++ h) {
        for (int iterator = head[queue[h]]; ~iterator; iterator = next_edge[iterator]) {
            int v = to[iterator];
            if (--degree[v] == 1) {
                queue.push_back(v);
            }
        }
    }

    for (int i = 0; i < n; ++ i) {
        if (degree[i] >= 3) {
            selected_vertices.push_back(i);
        }
    }
    if (selected_vertices.empty()) {
        int v = 0;
        while (degree[v] < 2) {
            v ++;
        }
        selected_vertices.push_back(v);
    }
    memset(selected, -1, sizeof(selected));
    int n2 = 0;
    for (auto&& v : selected_vertices) {
        selected[v] = n2 ++;
    }

    for (int i = 0; i < m; ++ i) {
        int a = to[i << 1];
        int b = to[i << 1 | 1];
        used[i] = degree[a] < 2 || degree[b] < 2;
    }
    for (int i = 0; i < n2; ++ i) {
        int u = selected_vertices.at(i);
        for (int iterator = head[u]; ~iterator; iterator = next_edge[iterator]) {
            if (!used[iterator >> 1]) {
                int count = 1;
                int e = iterator;
                used[e >> 1] = true;
                while (!~selected[to[e]]) {
                    count ++;
                    int v = to[e];
                    assert(degree[v] == 2);
                    int f = head[v];
                    while (used[f >> 1]) {
                        f = next_edge[f];
                    }
                    assert(~f && !used[f >> 1]);
                    used[f >> 1] = true;
                    e = f;
                }
                edges.emplace_back(u, to[e], count);
            }
        }
    }

    same[1] = 0;
    diff[1] = 1;
    power[1] = c - 1;
    for (int i = 2; i < n; ++ i) {
        same[i] = (long long)diff[i - 1] * (c - 1) % MOD;
        diff[i] = (power[i - 1] + MOD - diff[i - 1]) % MOD;
        power[i] = (long long)power[i - 1] * (c - 1) % MOD;
    }
    result = 0;
    generate(0, 0);
    for (int i = 0; i < (int)queue.size(); ++ i) {
        result = (long long)result * (c - 1) % MOD;
    }
    printf("%d\n", result);
}
