
typedef long long ll;

ll det(const mat &b) {
    static mat a;
    a = b;
    int i, j, k;
    ll ans = 1;
    for (i = 0; i < a.n; ++i)
        for (j = 0; j < a.n; ++j)
            a.d[i][j] = (a.d[i][j] + MOD) % MOD;
    for (i = 0; i < a.n; ++i) {
        for (j = i + 1; j < a.n; ++j) {
            while (a.d[i][j]) {
                ll t = a.d[i][i] / a.d[j][i];
                for (k = i; k < a.n; ++k)
                    a.d[i][k] = (a.d[i][k] + MOD - t * a.d[j][i] % MOD) % MOD;
                for (k = i; k < a.n; ++k)
                    swap(a.d[i][k], a.d[j][k]);
                ans = -ans;
            }
        }
        ans = ans * a.d[i][i] % MOD;
        if (ans == 0) return 0;
    }
    return ans;
}