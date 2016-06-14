#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MXN 1000007
int len = 0;
char input[MXN];
struct sam {
    int mxstep;
    struct node {
        int step, sz;
        node *pre, *c[26];
    } buf[MXN << 1 | 1], *cur, *root, *last;
    int b[MXN << 1 | 1];
    node *rank[MXN << 1 | 1];
    sam() {
        memset(buf, 0, sizeof(node) * MXN);
        cur = buf + 1;
        root = last = buf;
    }
    sam(int n) {
        memset(buf, 0, sizeof(node) * n);
        cur = buf + 1;
        root = last = buf;
    }
    node *alloc(int st) {
        cur->step = st;
        memset(cur->c, 0, sizeof(cur->c));
        cur->pre = 0;
        cur->sz = 0;
        return cur++;
    }
    void extend(int chr) {
        node *p = last;
        node *np = alloc(p->step + 1);
        np->sz = 1;
        for (; p && !p->c[chr]; p = p->pre) p->c[chr] = np;
        if (!p) {
            np->pre = root;
        } else {
            node *q = p->c[chr];
            if (q->step == p->step + 1) {
                np->pre = q;
            } else {
                node *nq = alloc(p->step + 1);
                memcpy(nq->c, q->c, sizeof(nq->c));
                nq->pre = q->pre;
                q->pre = np->pre = nq;
                for (; p && p->c[chr] == q; p = p->pre) p->c[chr] = nq;
            }
        }
        last = np;
    }
    void topo(int n) {
        memset(rank, 0, sizeof(node*) * n);
        memset(b, 0, sizeof(int) * n);
        node *p = buf + 1;
        mxstep = 0;
        for (; p != cur; ++p) ++b[p->step], mxstep = std::max(mxstep, p->step);
        for (int i = 2; i <= mxstep; ++i) b[i] += b[i - 1];
        for (p = buf + 1; p != cur; ++p) rank[--b[p->step]] = p;
    }
} sss;
int dp[MXN];
int main() {
    freopen("sub.in", "r", stdin);
    freopen("sub.out", "w", stdout);
    scanf("%s", input);
    len = strlen(input);
    for (int i = 0; i < len; ++i) {
        sss.extend(input[i] - 'a');
    }
    sss.topo(MXN);
    int i;
    for (i = 0; sss.rank[i]; ++i);
    for (--i; i >= 0; --i) {
        sss.rank[i]->pre->sz += sss.rank[i]->sz;
    }
    for (sam::node *p = sss.buf + 1; p != sss.cur; ++p) {
        dp[p->step] = std::max(dp[p->step], p->sz);
    }
    // for (int i = 1; i <= sss.mxstep; ++i) {
        // printf("%d\n", dp[i]);
    // }
    typedef long long ll;
    ll resu = 0;
    for (int i = 1; i <= sss.mxstep; ++i) {
        if (dp[i] > 1)
            resu = std::max(resu, (ll)i * dp[i]);
    }
    printf("%lld\n", resu);
    // while (1);
    return 0;
}
