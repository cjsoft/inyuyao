#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#define IABS(x) ((x) > 0 ? (x) : -(x))
#define isrson(x) (x->fa->c[1] == x)
#define mid(l, r) (l + ((r - l) >> 1))
#define INF 0x3f3f3f3f
#define MXN 100007
#define MXQ 100007
using namespace std;
typedef pair<int, int> COMBINED;
int nodeweight[MXN];
struct node {
    node *fa, *c[2];
    COMBINED sum;
    int sz, data;
    void print() {
        if (sz == 0) return;
        c[0]->print();
        printf("%d ", data);
        c[1]->print();
    }
} buf[MXN + (MXQ << 1) | 1], *cur, *nil, *root, _nil;
void asd() {
    root->print();
    puts("");
}
inline void update(node *x) {
    x->sz = x->c[0]->sz + x->c[1]->sz + 1;
    if (x->c[0]->sz & 1) {
        x->sum.first = x->c[0]->sum.first + x->c[1]->sum.first;
        x->sum.second = x->c[0]->sum.second + x->data + x->c[1]->sum.second;
    } else {
        x->sum.first = x->c[0]->sum.first + x->data + x->c[1]->sum.second;
        x->sum.second = x->c[0]->sum.second + x->c[1]->sum.first;
    }
}
inline node *newnode(int data, node *parent) {
    cur->data = data;
    cur->sum.first = data;
    cur->sum.second = 0;
    cur->sz = 1;
    cur->fa = parent;
    cur->c[0] = cur->c[1] = nil;
    return cur++;
}
inline void rotate(node *x) {
    node *p = x->fa, *z = p->fa;
    int fx = isrson(x), fp = isrson(p);
    if (p == root) {
        root = x;
    } else {
        z->c[fp] = x;
    }
    x->fa = z;
    p->c[fx] = x->c[fx ^ 1];
    x->c[fx ^ 1] = p;
    p->c[fx]->fa = p;
    p->fa = x;
    update(p);
}
inline void splay(node *x, node *y) {
    for (; x->fa != y; rotate(x)) {
        if (x->fa->fa != y) {
            if (isrson(x) == isrson(x->fa)) rotate(x->fa);
            else rotate(x);
        }
    }
    update(x);
}
int find(int data) {
    int k = 0;
    node *x = root;
    int dir = data < x->data;
    while (x->data != data) {
        // if (x->c[dir] == nil) return dir ? k + x->c[0]->sz + 1 : k;
        if (dir) k += x->c[0]->sz + 1;
        x = x->c[dir];
        dir = data < x->data;
    }
    return k + x->c[0]->sz + 1;
}
node *findk(int k) {
    node *x = root;
    int dir = k > x->c[0]->sz + 1;
    while (k != x->c[0]->sz + 1) {
        if (dir) k -= x->c[0]->sz + 1;
        x = x->c[dir];
        dir = k > x->c[0]->sz + 1;
    }
    return x;
}
void swim(int k, node *y) {
    splay(findk(k), y);
}
void DELETE(int data) {
    int x = find(data);
    // swim(x, nil);
    // if (root->data != data) throw 1;
    // if (x < 3) throw 1;
    swim(x - 1, nil);
    swim(x + 1, root);
    root->c[1]->c[0] = nil;
    update(root->c[1]);
    update(root);
}
void INSERT(int data) {
    node *x = root;
    int dir = data < x->data;
    while (x->c[dir] != nil) {
        if (x->c[dir] == nil) break;
        x = x->c[dir];
        dir = data < x->data;
    }
    x->c[dir] = newnode(data, x);
    update(x);
    splay(x, nil);
    return;
    // asd();
    // int x = find(data);
    // printf("  %d %d\n", x,data);
    // swim(x, nil);
    // swim(x + 1, root);
    // root->c[1]->c[0] = newnode(data, root->c[1]);
    // update(root->c[1]);
    // update(root);
}
void edit(int data, int newdata) {
    // root->print();
    // puts("");
    DELETE(data);
    INSERT(newdata);
}
node *build(int l, int r, int raw[], node *parent) {
    if (l > r) return nil;
    if (l == r) {
        return newnode(raw[l], parent);
    }
    node *tmp = newnode(raw[mid(l, r)], parent);
    tmp->c[0] = build(l, mid(l, r) - 1, raw, tmp);
    tmp->c[1] = build(mid(l, r) + 1, r, raw, tmp);
    update(tmp);
    return tmp;
}
int l[MXQ], r[MXQ], wei[MXQ], ptot = 1;
inline void init();
inline int getint();
int n, q, o;
int main() {
    init();
    n = getint(); q = getint(); o = getint();
    int op, u, v, w;
    nodeweight[0] = INF;
    nodeweight[1] = INF;
    nodeweight[n + 2] = -INF;
    nodeweight[n + 3] = -INF;
    root = build(0, n + 3, nodeweight, nil);
    nodeweight[1] = 0;
    int lastans = 0;
    for (int i = 0; i < q; ++i) {
        op = getint();
        if (op == 1) {
            u = getint(); v = getint(); w = getint();
            if (o) u ^= lastans, v ^= lastans;
            l[ptot] = u; r[ptot] = v; wei[ptot++] = w;
        } else {
            int k = getint();
            if (o) k ^= lastans;
            u = l[k];
            v = r[k];
            w = -wei[k];
        }
        edit(nodeweight[u], nodeweight[u] + w);
        nodeweight[u] += w;
        edit(nodeweight[v], nodeweight[v] + w);
        nodeweight[v] += w;
        printf("%d\n", IABS(root->sum.first - root->sum.second) >> 1);
        lastans = IABS(root->sum.first - root->sum.second) >> 1;
    }
    return 0;
}
int getint() {
    static int rtn, f;
    static char ch;
    rtn = 0; f = 1;
    while ((ch = getchar()) < '0' || ch > '9') if (ch == '-') f = -f;
    rtn = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') rtn = rtn * 10 + ch - '0';
    return rtn * f;
}
void init() {
    cur = buf;
    nil = &_nil;
    nil->fa = nil->c[0] = nil->c[1] = nil;
    nil->data = 0;
    nil->sum.first = nil->sum.second = 0;
    nil->sz = 0;
}
