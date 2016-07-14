#include <cstdio>
#include <cmath>
#include <algorithm>
typedef long long int64;
static const int MAXN = 1e5 + 6;

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

struct point {
    int x, y;
    point() : x(0), y(0) { }
    point(int x, int y) : x(x), y(y) { }
    inline point operator + (const point &rhs) const {
        return point(x + rhs.x, y + rhs.y);
    }
    inline point operator - (const point &rhs) const {
        return point(x - rhs.x, y - rhs.y);
    }
    inline point operator * (const int mul) const {
        return point(x * mul, y * mul);
    }
    inline bool operator < (const point &rhs) const {
        return (x == rhs.x) ? (y < rhs.y) : (x < rhs.x);
    }
    inline bool operator == (const point &rhs) const {
        return (x == rhs.x && y == rhs.y);
    }
    inline bool operator != (const point &rhs) const {
        return (x != rhs.x || y != rhs.y);
    }
    inline void print() { printf("(%d, %d)\n", x, y); }
    inline int64 det(const point &rhs) const {
        return (int64)x * rhs.y - (int64)y * rhs.x;
    }
};

// > 0 if ab to bc is clockwise
inline int64 direction(const point &a, const point &b, const point &c) {
    return (int64)(c.x - b.x) * (b.y - a.y) - (int64)(c.y - b.y) * (b.x - a.x);
}
// > 0 if ab to cd is clockwise
inline int64 direction(const point &a, const point &b, const point &c, const point &d) {
    return (int64)(d.x - c.x) * (b.y - a.y) - (int64)(d.y - c.y) * (b.x - a.x);
}
// Absolute value
inline int64 triangle_area(const point &a, const point &b, const point &c) {
    return std::abs((int64)(c.x - a.x) * (b.y - a.y) - (int64)(c.y - a.y) * (b.x - a.x));
}

int *convex_hull(int _n, point *p)
{
    point *_p = new point[_n];
    for (int i = 0; i < _n; ++i) _p[i] = p[i];
    std::sort(_p, _p + _n);
    int n = 0;
    for (int i = 0; i < _n; ++i)
        if (i == 0 || _p[i] != _p[i - 1]) p[n++] = _p[i];
    delete[] _p;
    int *s = new int[n + 2], top, btm;
    s[0] = 0; s[1] = 1;
    top = 2;
    for (int i = 2; i < n; ++i) {
        while (top > 1 && direction(p[s[top - 2]], p[s[top - 1]], p[i]) > 0) --top;
        s[top++] = i;
    }
    btm = --top;
    for (int i = n - 1; i >= 0; --i) {
        while (top > btm && direction(p[s[top - 2]], p[s[top - 1]], p[i]) > 0) --top;
        s[top++] = i;
    }
    s[--top] = -1;
    return s;
}

int n;
point p[MAXN], pp[MAXN];

int main()
{
    freopen("area.in", "r", stdin);
    freopen("area.out", "w", stdout);

    n = fio_getint();
    for (int i = 0; i < n; ++i) {
        p[i].x = fio_getint();
        p[i].y = fio_getint();
    }

    int *ch = convex_hull(n, p), nn = 0;
    for (int *i = ch; *i != -1; ++i) pp[nn++] = p[*i];
    // Rotating calipers
    int u, v, uu;
    uu = u = 0, v = 1;
    while (direction(pp[0], pp[1], pp[v], pp[(v + 1) % nn]) < 0) ++v;
    int64 ans = 0, cur;
    do {
        // Check
        int lo, hi, mid, t1, t2;
        lo = std::min(u, v); hi = std::max(u, v);
        while (lo < hi - 1) {
            mid = (lo + hi) >> 1;
            if (triangle_area(pp[u], pp[v], pp[mid]) < triangle_area(pp[u], pp[v], pp[mid + 1]))
                lo = mid;
            else hi = mid;
        }
        t1 = hi;
        lo = std::max(u, v); hi = std::min(u, v) + nn;
        while (lo < hi - 1) {
            mid = (lo + hi) >> 1;
            if (triangle_area(pp[u], pp[v], pp[mid % nn]) < triangle_area(pp[u], pp[v], pp[(mid + 1) % nn]))
                lo = mid;
            else hi = mid;
        }
        t2 = hi % nn;
        cur = triangle_area(pp[u], pp[v], pp[t1]) + triangle_area(pp[u], pp[v], pp[t2]);
        if (ans < cur) ans = cur;
        // Rotate, step forward
        if (direction(pp[u], pp[(u + 1) % n], pp[v], pp[(v + 1) % nn]) < 0) v = (v + 1) % nn;
        else { u = (u + 1) % nn; ++uu; }
    } while (uu < n + 4);

    printf("%lld.%d\n", ans / 2, (ans & 1) * 5);

    fclose(stdin); fclose(stdout);
    return 0;
}

