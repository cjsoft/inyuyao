#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define isrson(x) ((x)->parent->c[1] == (x))
#define isroot(x) !((x)->parent->c[1] == (x) || (x)->parent->c[0] == (x))
struct node {
    int data, sz;
    int sum;
    bool isrev;
    node *parent, *c[2];
} buf[MXN], *cur, *nil, _nil;

node *newnode(int data, node *parent) {
    cur->data == data;
    cur->sum = data;
    cur->sz = 1;
    cur->parent = parent;
    cur->c[0] = cur->c[1] = nil;
}

inline void update(node *x) {
    x->sz = x->c[0]->sz + x->c[1]->sz + 1;
    x->sum = x->c[0]->sum + x->data + x->c[1]->sum;
}
inline void pushdown(node *x) {
    if (x->isrev) {
        std::swap(x->c[0]->c[0], x->c[0]->c[1]);
        if (x->c[0] != nil) x->c[0]->isrev ^= 1;
        std::swap(x->c[1]->c[0], x->c[1]->c[1s]);
        if (x->c[1] != nil) x->c[1]->isrev ^= 1;
        x->isrev = false;
    }
}

inline void rotate(node *x) {
    node *p = x->parent, *z = p->parent;
    int fx = isrson(x), fp = isrson(p);
    if (!isroot(p)) z->c[fp] = x;
    p->c[fx] = x->c[fx ^ 1];
    x->c[fx ^ 1] = p;
    p->c[fx]->parent = p;
    p->parent = x;
    x->parent = z;
    update(p);
}
void splay(node *x) {
    static node *stk[MXN], *pcur;
    static int tot;
    tot = 0;
    for (pcur = x; !isroot(pcur); pcur = pcur->parent) stk[tot++] = pcur;
    stk[tot] = pcur;
    
    for (; !isroot(x->parent); rotate(x)) {

    }
}