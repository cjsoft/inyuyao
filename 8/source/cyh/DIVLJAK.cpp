#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <string>
#include <set>
#include <algorithm>
#define CSZ 26
#define MXN 200007
#define MXLEN 4000007
int q, n;
int lastcnt[MXN], nowcnt[MXN];
int locator[MXN];
int lenl[MXN];
struct listnode {
    int prev, id;
} buflist[MXN];
int ltot = 1;
struct node {
    node *c[CSZ], *fail, *suffix_link;
    int dep, id;
    node() {
        memset(c, 0, sizeof(c));
        fail = suffix_link = NULL;
        dep = id = 0;
    }
} buf[MXLEN], *root, _root, *cur;
inline void init() {
    root = &_root;
    root->id = root->dep = 0;
    memset(root->c, 0, sizeof(root->c));
    root->fail = root->suffix_link = root;
    cur = buf;
}
inline node *newnode(node *parent) {
    memset(cur->c, 0, sizeof(cur->c));
    cur->id = 0;
    cur->suffix_link = cur->fail = NULL;
    cur->dep = parent->dep + 1;
    return cur++;
}
int insert(char s[], int id) {
    node *p = root;
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        if (p->c[s[i] - 'a'] == NULL) p->c[s[i] - 'a'] = newnode(p);
        p = p->c[s[i] - 'a'];
    }
    if (!p->id) {
        p->id = id;
        return id;
    } else {
        return p->id;
    }
}
void construct_ACautomaton() {
    std::queue<node*> q;
    root->fail = root;
    root->suffix_link = root;
    q.push(root);
    while (!q.empty()) {
        for (int i = 0; i < CSZ; ++i) {
            if (q.front()->c[i] != NULL) {
                if (q.front() == root) q.front()->c[i]->fail = root;
                else {
                    node *p = q.front()->fail;
                    for (; p->c[i] == NULL && p != root; p = p->fail);
                    q.front()->c[i]->fail = p->c[i] ? p->c[i] : root;
                }
                q.front()->c[i]->suffix_link = q.front()->c[i]->fail->id ? q.front()->c[i]->fail : q.front()->c[i]->fail->suffix_link;
                q.push(q.front()->c[i]);
            } else {
                if (q.front() == root) q.front()->c[i] = root;    // 直接把fail指针接到c上，一视同仁
                else q.front()->c[i] = q.front()->fail->c[i];     //
            }
        }
        q.pop();
    }
}
int stk[MXN], top = 0;
char instk[MXN];
void print(node *p) {
    instk[p->id] = 1;
    stk[top++] = p->id;
    if (lenl[p->id] != p->dep)
        puts("WARN");
    if (p->suffix_link != root)
        print(p->suffix_link);
}
void find(char raw[]) {
    top = 0;
    int len = strlen(raw);
    node *p = root;
    for (int i = 0; i < len; ++i) {
        int s = raw[i] - 'a';
        p = p->c[s];
        if (p->id)
            print(p);
        else if (p->suffix_link != root)
            print(p->suffix_link);
    }
    for (int i = 0; i < top; ++i)
        nowcnt[stk[i]] = lastcnt[stk[i]] + 1;
    for (int i = 0; i < top; ++i)
        lastcnt[stk[i]] = nowcnt[stk[i]];
    // for (int i = 0; i < top; ++i)
        // instk[stk[i]] = 0;
    memset(instk, 0, sizeof(char) * n + 7);
}
char input[MXLEN];
inline int getint();
FILE *f1, *f2;
int main() {
    freopen("DIVLJAK.in", "r", stdin);
    freopen("DIVLJAK.out", "w", stdout);
    // f1 = fopen("DIVLJAK.in", "r");
    // f1 = stdin;
    // f2 = fopen("DIVLJAK.out", "w");
    init();
    memset(lastcnt, 0, sizeof(lastcnt));
    memset(nowcnt, 0, sizeof(nowcnt));
    n = getint();
    for (int i = 1; i <= n; ++i) {
        scanf("%s", input);
        locator[i] = insert(input, i);
        lenl[i] = strlen(input);
    }
    construct_ACautomaton();
    q = getint();
    for (int i = 0; i < q; ++i) {
        if (getint() == 1) {
            scanf("%s", input);
            find(input);
        } else {
            printf("%d\n", nowcnt[locator[getint()]]);
        }
    }
    return 0;
}
int _rtn, _f;
char _ch;
int getint() {
    // scanf("%d", &_rtn);
    _rtn = 0; _f = 1;
    while ((_ch = getchar()) < '0' || _ch > '9') if (_ch == '-') _f = -_f;
    _rtn = _ch - '0';
    while ((_ch = getchar()) >= '0' && _ch <= '9') _rtn = _rtn * 10 + _ch - '0';
    return _rtn * _f;
}
