#include <cstdio>
#include <cstring>
typedef long long int64;
static const int INF32 = 0x3fffffffLL;
static const int64 INF64 = 0x7f7f7f7f7f7f7f7fLL;
static const int MAXN = 182;
static const int MAXM = 182;
static const int MAXV = MAXN * MAXM * 2 + 10;
static const int MAXE = MAXM * MAXM * MAXN * 2 + 15;
template <typename T> inline bool update_min(T &a, const T &b) { if (a > b) { a = b; return true; } else return false; }
template <typename T> inline T abs(const T x) { return x > 0 ? x : -x; }

static const int FIO_BUFSZ = 262144;
char fio_buf[FIO_BUFSZ];
int fio_bufptr = FIO_BUFSZ - 1;
inline void fio_flush() {
    fread(fio_buf, sizeof(char), FIO_BUFSZ, stdin);
    fio_bufptr = -1;
}
inline char fio_getchar() {
    if (fio_bufptr == FIO_BUFSZ - 1) fio_flush();
    return fio_buf[++fio_bufptr];
}
inline int fio_getint() {
    static int ret;
    static char ch;
    while ((ch = fio_getchar()) < '0' || ch > '9') ;
    ret = ch - '0';
    while ((ch = fio_getchar()) >= '0' && ch <= '9')
        ret = ret * 10 + ch - '0';
    return ret;
}

struct edge {
    int dest, cap; int64 cost;
    edge() : dest(-1), cap(0), cost(INF32) { }
    edge(int dest, int cap, int64 cost) : dest(dest), cap(cap), cost(cost) { }
};

int n, m, k;
int t[MAXN][MAXM];

int v, source, sink;
edge e[MAXE];
int head[MAXV], next[MAXE];

inline void add_edge(int u, int v, int cap, int64 cost) {
    static int e_ct = 0;
    e[e_ct] = edge(v, cap, cost);
    next[e_ct] = head[u]; head[u] = e_ct++;
    e[e_ct] = edge(u, 0, -cost);
    next[e_ct] = head[v]; head[v] = e_ct++;
    // e[i] and e[i ^ 1] would be a pair of reversed edges
}

int64 min_cost_flow(int flow)
{
    static int64 dist[MAXV];
    static int pred_u[MAXV], pred_e[MAXV];
    // Use custom queue instead of std::queue for a minor burst in speed
    static const int QSIZE = 262144;
    static int q[QSIZE];
    static bool in_queue[MAXV] = { false };
    int64 ans = 0;
    while (flow > 0) {
        for (int i = 0; i < v; ++i) dist[i] = INF64;
        dist[source] = 0;
        int qhead = 1, qtail = 0;
        q[0] = source; in_queue[source] = true;
        while (qhead != qtail) {
            int u = q[qtail]; qtail = (qtail + 1) % QSIZE; in_queue[u] = false;
            for (int w = head[u]; w != -1; w = next[w])
                if (e[w].cap > 0 && update_min(dist[e[w].dest], dist[u] + e[w].cost)) {
                    pred_u[e[w].dest] = u;
                    pred_e[e[w].dest] = w;
                    if (!in_queue[e[w].dest]) { q[qhead] = e[w].dest; qhead = (qhead + 1) % QSIZE; in_queue[e[w].dest] = true; }
                }
        }
        if (dist[sink] == INF64) return -1; // Such flow does not exist
        int augment = INF32;
        for (int u = sink; u != source; u = pred_u[u])
            update_min(augment, e[pred_e[u]].cap);
        flow -= augment;
        ans += dist[sink] * augment;
        for (int u = sink; u != source; u = pred_u[u]) {
            e[pred_e[u]].cap -= augment;
            e[pred_e[u] ^ 1].cap += augment;
        }
    }
    return ans;
}

int main()
{
    freopen("hero.in", "r", stdin);
    freopen("hero.out", "w", stdout);

    n = fio_getint();
    m = fio_getint();
    if (n > 180 || m > 180) {
        puts("MLE! > <");
        fclose(stdin); fclose(stdout); return 0;
    }
    k = fio_getint();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) t[i][j] = fio_getint();

    v = n * m * 2 + 4; for (int i = 0; i < v; ++i) head[i] = -1;
    source = v - 2; sink = v - 1;
    int aux_source = v - 4, aux_sink = v - 3;
    add_edge(source, aux_source, 2, 0);
    add_edge(aux_sink, sink, 2, 0);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            add_edge((i + i) * m + j, (i + i + 1) * m + j, 1, t[i][j]);
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < m; ++j)
            for (int w = 0; w < m; ++w)
                add_edge((i + i + 1) * m + j, (i + i + 2) * m + w, 1, (int64)abs(w - j) * k);
    for (int i = 0; i < m; ++i) {
        add_edge(aux_source, i, 1, 0);
        add_edge((n + n - 1) * m + i, aux_sink, 1, 0);
    }

    printf("%lld\n", min_cost_flow(2));
    fclose(stdin); fclose(stdout);
    return 0;
}

