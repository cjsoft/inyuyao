/**
 * @author SCaffrey (sirius.caffrey@gmail.com)
 * @creation time : Mon 20 Jun 2016 10:01:34 AM CST
 * @last modified : Mon 20 Jun 2016 11:46:23 AM CST
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
const int MAXN = 100033;

inline void read(int &x) {
	char c = getchar();
	int f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	x = 0;
	while (c >= '0' && c <= '9') {
		x = (x << 1) + (x << 3) + c - 48;
		c = getchar();
	}
	x *= f;
}
int n, c, l[200003], t[200003];
int r, m;
LL res;
struct node {
  int v, s, r, c;
	LL cost, ss;
  node* ch[2];
  inline node(int v = 0):v(v) {
    ch[0] = ch[1] = NULL;
    r = rand(); s = c = 1;
		ss = cost = v;
  }
  inline int cmp(int x) const {
    if (x == v) return -1;
    if (x < v) return 0;
    return 1;
  }
  inline void maintain() {
    s = 1;
		ss = v;
		cost = ((ch[0]?ch[0]->ss:0) + v) * LL((ch[1]?ch[1]->s:0) + 1);
    f(i, 0, 2) if (ch[i]) {
			s += ch[i]->s;
			ss += ch[i]->ss;
			cost += ch[i]->cost;
		}
  }
  inline void print() {
    if (ch[0]) ch[0]->print();
    printf("(%d,%d)", v, s);
    if (ch[1]) ch[1]->print();
  }
};
void rotate(node* &o, int d) {
  node* k = o->ch[d ^ 1];
  o->ch[d ^ 1] = k->ch[d];
  k->ch[d] = o;
  o->maintain(); k->maintain(); o = k;
}
void insert(node* &o, int x) {
  if (o == NULL) {
    o = new node(x);
    return;
  }
  ++o->s;
    int d = x > o->v;
    insert(o->ch[d], x);
    if (o->ch[d]->r < o->r) rotate(o, d ^ 1);
  o->maintain();
}
void remove(node*& o, int x) {
  if (o->v == x) {
    node* u = o;
    if (o->ch[0] && o->ch[1]) {
      int d = (o->ch[0]->r < o->ch[1]->r);
      rotate(o, d); remove(o->ch[d], x);
    } else {
      if (o->ch[0] == NULL && o->ch[1] == NULL) o = NULL;
      else if (o->ch[0]) o = o->ch[0];
      else if (o->ch[1]) o = o->ch[1];
      delete u;
    }
  } else {
    remove(o->ch[x > o->v], x);
  }
  if (o) o->maintain();
}
node *root;
int x, p, q, rk, v;
int main() {
#ifndef LOCAL
  freopen("RASPORED.in", "r", stdin);
  freopen("RASPORED.out", "w", stdout);
#endif

	read(n); read(m);
	f(i, 0, n) {
		read(l[i]); read(t[i]);
		v = t[i];
		insert(root, v);
		res += l[i];
	}
	printf(LLD"\n", res - root->cost);
	while (m--) {
		read(x); read(p); read(q);
		--x;
		res -= l[x]; res += l[x] = p;
		v = t[x];
		remove(root, v); v = t[x] = q;
		insert(root, v);
		printf(LLD"\n", res - root->cost);
	}

#ifndef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}


