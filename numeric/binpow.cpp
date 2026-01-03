const long long INF = 4000000000000000000LL;

inline long long mul_mod(long long a, long long b, long long m) {
    return (long long) ((__int128) a * b % m);
}

long long binpow(long long a, long long b, long long m = INF) {
    a %= m;
    long long res = 1 % m;
    if (a == 0) {
        return 0;
    }
    while (b > 0) {
        if (b & 1) {
            res = mul_mod(res, a, m);
        }
        a = mul_mod(a, a, m);
        b >>= 1;
    }
    return res;
}
