#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#define isrson(x) (x->fa->c[1] == x)
#define MXN 100007
#define MXQ 100007
using namespace std;
typedef pair<int, int> COMBINED;
struct node {
    node *fa, *c[2];
    COMBINED sum;
    int sz, data;
} buf[MXN + MXQ | 1], *cur, *nil, *root, _nil, _root;
inline void update(node *x) {
    x->sz = x->c[0]->sz + x->c[1]->sz + 1;
    if (x->c[0]->sz & 1) {
        x->sum->first = x->c[0]->sum->first + x->c[1]->first;
        x->sum->second = x->c[0]->second + x->data + x->c[1]->second;
    } else {
        x->sum->first = x->c[0]->sum->first + x->data + x->c[1]->second;
        x->sum->second = x->c[0]->second + x->c[1]->first;
    }
}
inline node *newnode(int data, node *parent) {
    cur->data = data;
    cur->sum->first = data;
    cur->sum->second = 0;
    cur->sz = 1;
    cur->fa = parent;
    cur->c[0] = cur->c[1] = nil;
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
}
inline void splay(node *x, node *y) {
    for (; x->fa != y; rotate(x)) {
        if (x->fa->fa != y) {
            if (isrson(x) == isrson(x->fa)) rotate(x->fa);
            else rotate(x);
        }
    }
}
int main() {

    return 0;
}
