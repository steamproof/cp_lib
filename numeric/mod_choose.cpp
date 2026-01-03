struct mod_choose {
    int n;
    int mod;
    vector<int> fact;
    vector<int> ifact;

    mod_choose(int _n, int _mod) : n(_n), mod(_mod) {
        fact.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            fact[i] = (long long) fact[i - 1] * i % mod;
        }
        ifact.assign(n + 1, 1);
        ifact[n] = (int) binpow(fact[n], mod - 2, mod);
        for (int i = n; i > 0; i--) {
            ifact[i - 1] = (long long) ifact[i] * i % mod;
        }
    }

    inline int c(int nn, int kk) const {
        if (kk < 0 || kk > nn) {
            return 0;
        }
        return (long long) fact[nn] * ifact[kk] % mod * ifact[nn - kk] % mod;
    }
};
