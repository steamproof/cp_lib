struct line_hull {
    struct line {
        long long k;
        long long m;
        mutable long long p;

        bool operator<(const line& other) const {
            return k < other.k;
        }

        bool operator<(long long x) const {
            return p < x;
        }
    };

    static const long long inf = (1LL << 62);
    multiset<line, less<>> s;

    static inline long long div_floor(long long a, long long b) {
        assert(b != 0);
        if (b < 0) {
            a = -a;
            b = -b;
        }
        if (a >= 0) {
            return a / b;
        }
        return - ((-a + b - 1) / b);
    }

    static inline long long intersect_x(const line& a, const line& b) {
        if (a.k == b.k) {
            return (a.m >= b.m ? inf : -inf);
        }
        return div_floor(b.m - a.m, a.k - b.k);
    }

    bool isect(multiset<line>::iterator x, multiset<line>::iterator y) {
        if (y == s.end()) {
            x->p = inf;
            return false;
        }
        x->p = intersect_x(*x, *y);
        return x->p >= y->p;
    }

    // add line y = kx + m (max query)
    void add(long long k, long long m) {
        auto z = s.insert({k, m, 0});
        auto y = z;
        auto x = y;

        if (++y != s.end() && z->k == y->k) {
            if (z->m <= y->m) {
                s.erase(z);
                return;
            }
            s.erase(y);
        }

        y = z;
        while (isect(z, ++y)) {
            y = s.erase(y);
        }

        if (z != s.begin() && isect(--x, z)) {
            isect(x, z = s.erase(z));
        }

        while ((z = x) != s.begin() && (--x)->p >= z->p) {
            isect(x, s.erase(z));
        }
    }

    inline long long query(long long x) const {
        assert(!s.empty());
        auto l = *s.lower_bound(x);
        return l.k * x + l.m;
    }
};
