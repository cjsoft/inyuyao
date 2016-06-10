#include <iostream>
#include <cstdio>
#include <cstring>
#define iterate(x, y, i) for (edge *i = head[x][y]; i; i = i->prev)
#define MXM 2000007
#define MXN 2003
int n, m;

struct edge {
    int tox,  toy;
    edge *prev;
} buf[MXM << 1 | 1], *head[MXN][MXN], *cur = buf;

void addedge(int ax, int ay, int bx, int by) {
    cur->tox = bx;
    cur->toy = by;
    cur->prev = head[ax][ay];
    head[ax][ay] = cur++;
}

// bool check(int

int solve() {
    int ans = 0;
    for (int x1 = 0; x1 <= n; ++x1) {
        for (int y1 = 0; y1 <= n; ++y1) {
            if (head[x1][y1]) {
                iterate(x1, y1, i) {
                    iterate(i->tox, i->toy, j) {
                        if ((i->tox - x1) * (i->tox - x1) + (i->toy - y1) * (i->toy - y1) != (j->tox - i->tox) * (j->tox - i->tox) + (j->toy - i->toy) * (j->toy - i->toy))
                            continue;
                        if ((i->tox - x1) * (j->tox - i->tox) + (i->toy - y1) * (j->toy - i->toy) != 0)
                            continue;
                        iterate(j->tox, j->toy, k) {
                            if (i->tox - x1 != j->tox - k->tox || i->toy - y1 != j->toy - k->toy)
                                continue;
                            iterate(k->tox, k->toy, l) {
                                if (l->tox != x1 || l->toy != y1)
                                    continue;
                                ++ans;
                            }
                        }
                    }
                }
            }
        }
    }
    return ans;
}


int main() {
    scanf("%d %d", &n, &m);
    int x1, x2, y1, y2;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        addedge(x1, y1, x2, y2);
        addedge(x2, y2, x1, y1);
    }
    printf("%d\n", solve());
    return 0;
}
