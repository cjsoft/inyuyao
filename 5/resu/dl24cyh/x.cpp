/**
 * @author SCaffrey(sirius.caffrey@gmail.com)
 * @copyright MIT
 */
#include <cstdio>// NOLINT
#include <cstring>// NOLINT
#include <bits/stdc++.h>// NOLINT
#include <cmath>// NOLINT
#define x1 x11
#define y1 y11

#define f(x, y, z) for (int x = (y), __ = (z); x < __; ++x)
#define g(x, y, z) for (int x = (y), __ = (z); x <= __; ++x)
#define fd(x, y, z) for (int x = (y), __ = (z); x > __; --x)
#define gd(x, y, z) for (int x = (y), __ = (z); x >= __; --x)

#ifdef WIN32
    #define LLD "%I64d"
    #define LLU "%I64u"
#else
    #define LLD "%lld"
    #define LLU "%llu"
#endif

typedef long long LL;// NOLINT
typedef long double real;

const double INF = 1e100;
const int oo = ~0u >> 2;
const double pi = acos(-1.0);
const double EPS = 1e-8;
const int MAXN = 1000033;

inline void read(int &x) {
    x = 0;
    char c = getchar();
    while (c < '0'|| c > '9') c = getchar();
    while (c >= '0' && c <= '9') {
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
}
struct node {
    node *f, *ch[26];
    int l, r;
};
node pool[MAXN * 2];
node *tail;
node* newnode(int v) {
    node *p = tail++;
    f(i, 0, 26) p->ch[i] = NULL;
    p->f = 0; p->r = 0; p->l = v;
    return p;
}
node *root, *last;
inline void init() {
    tail = pool; root = last = newnode(0);
}
inline void add(int c) {
    node *p = last, *np = newnode(p->l + 1);
    while (p && !p->ch[c]) {
        p->ch[c] = np; p = p->f;
    }
    if (!p) np->f = root;
    else {
        node *q = p->ch[c];
        if (p->l + 1 == q->l) np->f = q;
        else {
            node *nq = newnode(p->l + 1);
            f(i, 0, 26) nq->ch[i] = q->ch[i];
            nq->f = q->f; q->f = np->f = nq;
            while (p && p->ch[c] == q) {
                p->ch[c] = nq; p = p->f;
            }
        }
    }
    last = np; np->r = 1;
}
char s[MAXN];
int d[MAXN * 2];
node *b[MAXN * 2];
int sz;
void topo() {
    sz = tail - pool;
    f(i, 0, sz) d[i] = 0;
    int mx = 0;
    f(i, 0, sz) {
        mx = std::max(mx, pool[i].l);
        ++d[pool[i].l];
    }
    g(i, 0, mx) d[i] += d[i - 1];
    f(i, 0, sz) b[--d[pool[i].l]] = &pool[i];
}
int f[MAXN * 2];
int n;
inline void update() {
    topo();
    gd(i, sz - 1, 1) b[i]->f->r += b[i]->r;
    f(i, 0, sz) f[b[i]->l] = std::max(f[b[i]->l], b[i]->r);
    gd(i, n - 1, 0) f[i] = std::max(f[i], f[i + 1]);
}
LL ans = 0;
int main() {
#ifndef LOCAL
    freopen("sub.in", "r", stdin);
    freopen("sub.out", "w", stdout);
#endif

    scanf("%s", s);
    init();
    f(i, 0, n = strlen(s)) add(s[i] - 'a');
    update();
    g(i, 1, n) if (f[i] > 1 && i * (LL)f[i] > ans) ans = LL(i) * f[i];
    printf(LLD"\n", ans);
    //  g(i, 1, n) printf("%d\n", f[i]);

#ifndef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}

