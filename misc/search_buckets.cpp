template <typename T>
class sqrt_buckets {
public:
    int n;
    int b;
    vector<T> a;
    vector<T> bucket;

    sqrt_buckets(const vector<T>& v) : n((int) v.size()), a(v) {
        b = max(1, (int) sqrt(n));
        int nb = (n + b - 1) / b;
        bucket.assign(nb, 0);
        for (int i = 0; i < n; i++) {
            bucket[i / b] += a[i];
        }
    }

    inline void set_value(int i, T x) {
        bucket[i / b] += x - a[i];
        a[i] = x;
    }

    inline T range_sum(int l, int r) {
        T res = 0;
        int bl = l / b;
        int br = r / b;
        if (bl == br) {
            for (int i = l; i <= r; i++) {
                res += a[i];
            }
            return res;
        }
        int end_l = (bl + 1) * b - 1;
        for (int i = l; i <= end_l; i++) {
            res += a[i];
        }
        for (int k = bl + 1; k < br; k++) {
            res += bucket[k];
        }
        for (int i = br * b; i <= r; i++) {
            res += a[i];
        }
        return res;
    }
};
