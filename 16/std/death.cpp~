# include <cstdio>
# include <cmath>
# include <algorithm>
using namespace std;

# define REP(i, n) for (int i = 1; i <= n; ++ i)
# define REP_G(i, x) for (int i = pos[x]; i; i = g[i].frt)
# define FOR(i, a, b) for (int i = a; i <= b; ++ i)

typedef unsigned long long ull;

typedef long long ll;

# define alp 0.75

# define NR 3010000
const ull WR = (1ull << 62) - 1;
# define u t[x]
# define lc ch[0]
# define rc ch[1]
# define ulfc t[u.lc]
# define urtc t[u.rc]

struct Edge { int y, frt; } g[NR << 1];
int pos[NR], gsz, bg[NR], ed[NR], wx[NR], p[NR], li[NR];
void AE (int x, int y) { g[++ gsz] = (Edge) { y, pos[x] }, pos[x] = gsz; }

struct FScap {
	int ch[2], sz, dep, tag, par, max, bel;
	ull de, lm, rm, add, val;
	inline void set (ull _de, int _d, ull _w, int _p, int _b) { de = lm = rm = _de, dep = _d, val = _w, par = _p, bel = max = _b, sz = 1; }
	inline void finc (int d) { tag += d, dep += d; }
	inline void fadd (ull d) { add += d, val += d; }
} t[NR];
int root, tsz, dsz, df[NR], n, m;


inline void dw (int x) {
	if (!x) return;
	if (u.tag) { if (u.lc) ulfc.finc (u.tag); if (u.rc) urtc.finc (u.tag); u.tag = 0; }
	if (u.add) { if (u.lc) ulfc.fadd (u.add); if (u.rc) urtc.fadd (u.add); u.add = 0; }
}

inline void upd (int x) {
	u.sz = ulfc.sz + urtc.sz + 1, u.max = u.bel, u.lm = u.rm = u.de;
	if (u.lc) { u.lm = ulfc.lm; if (t[ed[ulfc.max]].de > t[ed[u.max]].de) u.max = ulfc.max; }
	if (u.rc) { u.rm = urtc.rm; if (t[ed[urtc.max]].de > t[ed[u.max]].de) u.max = urtc.max; }
}

void fix (int x) { if (u.par) fix (u.par); dw (x); }
void dfs (int x) { if (!x) return; dw (x), dfs (u.lc), df[++ dsz] = x, dfs (u.rc); }
int build (int l, int r, ull lb, ull rb, int f) {
	if (l > r) return 0;
	int mid = (l + r) >> 1, x = df[mid]; ull mb = (lb + rb) >> 1; u.de = lb + rb, u.par = f;
	return u.lc = build (l, mid - 1, lb, mb, x), u.rc = build (mid + 1, r, mb, rb, x), x;
}


void update (int x) { if (!x) return; update (u.lc), update (u.rc), upd (x); }
bool ins (int &x, int d, int p, int dp, ull dt, int bl, ull lb, ull rb, int ff) {
	if (!x) return t[x = ++ tsz].set (lb + rb, dp, dt, ff, bl), d > -log (tsz + 1) / log (alp);
	dw (x); ull md = (lb + rb) >> 1; bool ty = (p >= ulfc.sz + 1), c; double f = (u.sz + 1) * alp;
	if (ty) c = ins (u.rc, d + 1, p - ulfc.sz - 1, dp, dt, bl, md, rb, x);
	else c = ins (u.lc, d + 1, p, dp, dt, bl, lb, md, x);
	upd (x);
	if (c && (ulfc.sz > f || urtc.sz > f)) { dsz = 0, dfs (x); x = build (1, dsz, lb, rb, ff); update (x); c = 0; }
	return c;
}
inline int get_rank (int x) { int k = ulfc.sz + 1; for (int z = 0; x; z = x, x = u.par) if (z && u.rc == z) k += ulfc.sz + 1; return k;}

int maxw (int x, ull r, ull rn) {
	//printf ("!!W%d %llu %llu\n", x, r, rn);
	if (!x || u.lm > r || t[ed[u.max]].de < rn) return 0;
	int s = maxw (u.rc, r, rn);
	if (s) return s;
	if (u.de <= r && t[ed[u.bel]].de >= rn) return u.bel;
	return maxw (u.lc, r, rn);
}

void inc (int x, ull l, ull r, int d) {
	if (l <= u.lm && u.rm <= r) { u.finc (1); u.fadd (d); return; }
	if (l <= u.de && u.de <= r) ++ u.dep, u.val += d;
	if (u.lc && l <= ulfc.rm) inc (u.lc, l, r, d);
	if (u.rc && urtc.lm <= r) inc (u.rc, l, r, d);
}
inline int insert (int p, int d, ull w, int b) { ins (root, 0, p, d, w, b, 1, WR, 0); return tsz; }

# define DEP(x) t[bg[x]].dep
# define DIS(x) t[bg[x]].val
# define DEN(x) t[bg[x]].de

bool cmpP (int i, int j) { return DEN (i) < DEN (j); }

int dep[NR], drs[NR], tf[NR], stk[NR];
ull dt[NR], ds[NR];
# define v g[i].y
void pre (int x, int fa) {
	//printf ("P %d %d\n", x, fa);
	drs[++ dsz] = x << 1, dt[x] += wx[x];
	REP_G (i, x) if (v != fa) dep[v] = dep[x] + 1, dt[v] = dt[x], pre (v, x);
	drs[++ dsz] = x << 1 | 1;
}
int init_build (int l, int r, ull lb, ull rb, int ff) {
	if (l > r) return 0;
	int mid = (l + r) >> 1, x = ++ tsz, id = drs[mid] >> 1; ull md = (lb + rb) >> 1; bool z = drs[mid] & 1;
	u.set (lb + rb, dep[id], dt[id], ff, z ? 0 : id);
	z ? ed[id] = x : bg[id] = x;
	u.lc = init_build (l, mid - 1, lb, md, x), u.rc = init_build (mid + 1, r, md, rb, x);
	return x;
}
void init () { pre (1, 0); root = init_build (1, dsz, 1, WR, 0); update (root); }
int lca (int x, int y) { if (DEN (x) > DEN (y)) swap (x, y); return maxw (root, DEN (x), DEN (y)); }
void slice (int x, int z) {
	fix (bg[x]);
	ed[z] = insert (get_rank (ed[x]), DEP (x), DIS (x) - wx[x] + wx[z], 0);
	bg[z] = insert (get_rank (bg[x]) - 1, DEP (x), DIS (x) - wx[x] + wx[z], z);
	inc (root, DEN (x), t[ed[x]].de, wx[z]);
}
void grow (int x, int z) {
	int rk = get_rank (bg[x]);
	fix (bg[x]);
	ed[z] = insert (rk, DEP (x) + 1, DIS (x) + wx[z], 0);
	bg[z] = insert (rk, DEP (x) + 1, DIS (x) + wx[z], z);
}
const int BUF_SIZE = (int) 1e4 + 10;
struct fastIO {
	char buf[BUF_SIZE];
	int cur;
	FILE *in;
	fastIO () {
		cur = BUF_SIZE;
		in = stdin;
	}
	inline char nextChar () {
		if (cur == BUF_SIZE) {
			fread (buf, BUF_SIZE, 1, in);
			cur = 0;
		}
		return buf[cur++];
	}
	inline int nextInt () {
		int x = 0;
		char c = nextChar ();
		while (!('0' <= c && c <= '9')) c = nextChar ();
		while ('0' <= c && c <= '9') {
			x = x * 10 + c - '0';
			c = nextChar ();
		}
		return x;
	}
} IO;

int main () {
	freopen ("death.in", "r", stdin);
	freopen ("death.out", "w", stdout);
	n = IO.nextInt (), m = IO.nextInt (); 
	REP (i, n) wx[i] = IO.nextInt (); int op, t1;
	FOR (i, 2, n) t1 = IO.nextInt (), AE (t1, i);
	init ();ll lastans=0;
	REP (id, m) {
		op = IO.nextInt (), t1 = IO.nextInt ();

		if (op == 3) {
			int psz = t1, len = t1, top = 0; bool one = false;
			REP (i, psz) {
				p[i] = IO.nextInt ();
				p[i] = (p[i] + lastans) % n + 1;
				fix (bg[li[i] = p[i]]);
				if (p[i] == 1) one = true;
			}
			if (!one) p[++ psz] = li[++ len] = 1, fix (bg[1]);
			sort (p + 1, p + psz + 1, cmpP);
			REP (i, psz) {
				
				if (!top) tf[stk[++ top] = p[i]] = 0;
				else {
					int x = p[i], z = lca (stk[top], x); fix (bg[z]);
					//printf ("lca %d %d %d\n", DEP(x), x, z);
					for (; DEP (stk[top]) > DEP (z); -- top) if (DEP (stk[top - 1]) <= DEP (z)) tf[stk[top]] = z;
					if (stk[top] != z) tf[li[++ len] = z] = stk[top], stk[++ top] = z;
					tf[stk[++ top] = x] = z;
				
				}
				//printf ("(!%d %d %d) ", p[i], top, tf[1]);
			}
			REP (i, len) ds[li[i]] = DIS (li[i]);//, printf ("[%d %d] ", li[i], tf[li[i]]);
			ull ans = 0;
			REP (i, len) ans += ds[li[i]] - ds[tf[li[i]]];
			printf ("%llu\n", ans);lastans=ans;
		} else if (op == 1) t1=(t1+lastans)%n+1,wx[++ n] = IO.nextInt (), grow (t1, n);
		else t1=(t1+lastans)%n+1,wx[++ n] = IO.nextInt (), slice (t1, n);
	}
	return 0;
}



