template <typename T>
vector<T> subset_convolution(const vector<T>& f, const vector<T>& g) {
    int n = 0;
    while ((1 << n) < (int) f.size()) {
        n++;
    }
    assert((int) f.size() == (1 << n));
    assert((int) g.size() == (1 << n));

    vector<vector<T>> F(n + 1, vector<T>(1 << n));
    vector<vector<T>> G(n + 1, vector<T>(1 << n));

    for (int m = 0; m < (1 << n); m++) {
        int pc = __builtin_popcount(m);
        F[pc][m] = f[m];
        G[pc][m] = g[m];
    }

    for (int k = 0; k <= n; k++) {
        for (int i = 0; i < n; i++) {
            for (int m = 0; m < (1 << n); m++) {
                if (m & (1 << i)) {
                    F[k][m] += F[k][m ^ (1 << i)];
                    G[k][m] += G[k][m ^ (1 << i)];
                }
            }
        }
    }

    vector<vector<T>> H(n + 1, vector<T>(1 << n));
    for (int m = 0; m < (1 << n); m++) {
        for (int k = 0; k <= n; k++) {
            T s = 0;
            for (int i = 0; i <= k; i++) {
                s += F[i][m] * G[k - i][m];
            }
            H[k][m] = s;
        }
    }

    for (int k = 0; k <= n; k++) {
        for (int i = 0; i < n; i++) {
            for (int m = 0; m < (1 << n); m++) {
                if (m & (1 << i)) {
                    H[k][m] -= H[k][m ^ (1 << i)];
                }
            }
        }
    }

    vector<T> h(1 << n);
    for (int m = 0; m < (1 << n); m++) {
        h[m] = H[__builtin_popcount(m)][m];
    }
    return h;
}
