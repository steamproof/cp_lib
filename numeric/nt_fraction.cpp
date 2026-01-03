template <typename T>
struct fraction {
    T p;
    T q;

    fraction() : p(0), q(1) {}

    fraction(T p_) : p(p_), q(1) {}

    fraction(T p_, T q_) : p(p_), q(q_) {
        normalize();
    }

    inline void normalize() {
        assert(q != 0);
        if (q < 0) {
            p = -p;
            q = -q;
        }
        T g = gcd(abs(p), q);
        p /= g;
        q /= g;
    }

    inline fraction operator+(const fraction& rhs) const {
        return fraction(p * rhs.q + rhs.p * q, q * rhs.q);
    }

    inline fraction operator-(const fraction& rhs) const {
        return fraction(p * rhs.q - rhs.p * q, q * rhs.q);
    }

    inline fraction operator*(const fraction& rhs) const {
        return fraction(p * rhs.p, q * rhs.q);
    }

    inline fraction operator/(const fraction& rhs) const {
        return fraction(p * rhs.q, q * rhs.p);
    }

    inline bool operator<(const fraction& rhs) const {
        return (__int128) p * rhs.q < (__int128) rhs.p * q;
    }

    inline bool operator==(const fraction& rhs) const {
        return p == rhs.p && q == rhs.q;
    }
};
