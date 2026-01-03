struct monotone_cht {
    struct line {
        long long k;
        long long m;
    };

    deque<line> q;

    static inline long long f(const line& l, long long x) {
        return l.k * x + l.m;
    }

    static inline bool bad(const line& a, const line& b, const line& c) {
        return (__int128) (b.m - a.m) * (a.k - c.k) >= (__int128) (c.m - a.m) * (a.k - b.k);
    }

    // slopes must be added in non-decreasing order
    void add(long long k, long long m) {
        line l = {k, m};
        while (q.size() >= 2 && bad(q[q.size() - 2], q.back(), l)) {
            q.pop_back();
        }
        q.push_back(l);
    }

    // query x in non-decreasing order
    long long query(long long x) {
        while (q.size() >= 2 && f(q[0], x) <= f(q[1], x)) {
            q.pop_front();
        }
        return f(q[0], x);
    }
};
