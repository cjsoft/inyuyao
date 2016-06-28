#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 200000;
const int K = 10;
const int MOD = (int)1e9 + 7;

std::vector <int> graph[N];

int c, n2, multiple, id[N], depth[N];

void mark_act(int u)
{
    if (id[u] == -1) {
        id[u] = n2 ++;
    }
}

std::vector <std::pair <int, int> > graph2[K << 2];

void add_edge(int a, int b, int c)
{
    a = id[a];
    b = id[b];
    graph2[a].push_back(std::make_pair(b, c));
    graph2[b].push_back(std::make_pair(a, c));
}

int prepare(int u)
{
    std::vector<int> children;
    foreach (it, graph[u]) {
        int v = *it;
        if (depth[v] == -1) {
            depth[v] = depth[u] + 1;
            int ret = prepare(v);
            if (~ret) {
                children.push_back(ret);
            }
        } else if (depth[v] < depth[u] - 1) {
            mark_act(u);
            mark_act(v);
            add_edge(u, v, 1);
        }
    }
    if ((int)children.size() >= 2) {
        mark_act(u);
    }
    if (id[u] == -1 && children.empty()) {
        multiple = (long long)multiple * (c - 1) % MOD;
        return -1;
    }
    if (~id[u]) {
        foreach (it, children) {
            int v = *it;
            add_edge(u, v, depth[v] - depth[u]);
        }
        return u;
    }
    return children[0];
}

int parent[K << 2];
bool mark[K << 2];
std::vector <int> children[K << 2];

void prepare2(int u)
{
    foreach (it, graph2[u]) {
        int v = it->first;
        if (depth[v] == -1) {
            depth[v] = depth[u] + 1;
            parent[v] = u;
            children[u].push_back(v);
            prepare2(v);
        } else if (depth[v] < depth[u] - 1) {
            mark[v] = true;
        }
    }
}

int power[N], same[N], diff[N];

std::vector <std::vector <int> > states;
std::map <std::vector <int>, int> imap;
std::vector <std::vector <int> > trans;

int label[K << 2];
std::vector <int> ways[K << 2];

void multiply(int &x, int a)
{
    x = (long long)x * a % MOD;
}

int solve(int u, int s)
{
    if (ways[u][s] == -1) {
        int &result = ways[u][s];
        result = 0;
        const std::vector <int> &state = states[s];
        if (parent[u] == -1) {
            label[u] = 0;
        } else {
            label[u] = mark[parent[u]] ? label[parent[u]] + 1 : label[parent[u]];
        }
        int m = (state.empty() ? -1 : *std::max_element(state.begin(), state.end())) + 1;
        std::vector <int> cursame(m, 1), prediff(m + 1, 1), sufdiff(m + 1, 1);
        foreach (it, graph2[u]) {
            int v = it->first;
            if (depth[v] < depth[u]) {
                int l = it->second;
                int c = state[label[v]];
                multiply(prediff[c + 1], diff[l]);
                multiply(sufdiff[c], diff[l]);
                multiply(cursame[c], same[l]);
            }
        }
        for (int i = 1; i <= m; ++ i) {
            multiply(prediff[i], prediff[i - 1]);
        }
        for (int i = m - 1; i >= 0; -- i) {
            multiply(sufdiff[i], sufdiff[i + 1]);
        }
        for (int c = 0; c <= m; ++ c) {
            int coef = 1;
            if (c < m) {
                multiply(coef, cursame[c]);
            } else {
                multiply(coef, std::max((::c) - m, 0));
            }
            multiply(coef, prediff[c]);
            if (c + 1 <= m) {
                multiply(coef, sufdiff[c + 1]);
            }
            if (coef) {
                int ss = s;
                if (~parent[u] && !mark[parent[u]]) {
                    ss = trans[ss][0];
                }
                ss = trans[ss][std::min(c + 1, (int)trans[ss].size() - 1)];
                foreach (it, children[u]) {
                    int v = *it;
                    multiply(coef, solve(v, ss));
                }
            }
            result += coef;
            if (result >= MOD) {
                result -= MOD;
            }
        }
    }
    return ways[u][s];
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
    memset(id, -1, sizeof(id));
    memset(depth, -1, sizeof(depth));
    depth[0] = 0;
    n2 = 0;
    mark_act(0);
    multiple = 1;
    prepare(0);
    same[1] = 0;
    diff[1] = 1;
    power[1] = c - 1;
    for (int i = 2; i < n; ++ i) {
        same[i] = (long long)diff[i - 1] * (c - 1) % MOD;
        diff[i] = (power[i - 1] + MOD - diff[i - 1]) % MOD;
        power[i] = (long long)power[i - 1] * (c - 1) % MOD;
    }
    memset(depth, -1, sizeof(depth));
    depth[0] = 0;
    memset(mark, 0, sizeof(mark));
    parent[0] = -1;
    prepare2(0);
    int k = m - (n - 1) + 1;
    states.push_back(std::vector <int>());
    trans.push_back(std::vector <int>(1, 0));
    for (int head = 0; head < (int)states.size(); ++ head) {
        std::vector <int> state = states[head];
        imap[state] = head;
        if ((int)state.size() < k) {
            int m = state.empty() ? -1 : *std::max_element(state.begin(), state.end());
            std::vector <int> nstate(state);
            for (int i = 0; i <= m + 1; ++ i) {
                nstate.push_back(i);
                trans[head].push_back(states.size());
                states.push_back(nstate);
                trans.push_back(std::vector <int>(1, head));
                nstate.pop_back();
            }
        }
    }
    for (int i = 0; i < n2; ++ i) {
        ways[i] = std::vector <int>(states.size(), -1);
    }
    int result = multiple;
    multiply(result, solve(0, 0));
    printf("%d\n", result);
    return 0;
}
