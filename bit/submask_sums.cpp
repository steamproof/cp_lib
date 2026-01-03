template <typename T>
void submask_sums(vector<T>& a) {
    int n = 0;
    while ((1 << n) < (int) a.size()) {
        n++;
    }
    assert((int) a.size() == (1 << n));
    for (int i = 0; i < n; i++) {
        for (int m = 0; m < (1 << n); m++) {
            if (m & (1 << i)) {
                a[m] += a[m ^ (1 << i)];
            }
        }
    }
}
