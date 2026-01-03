inline void iterate_masks_with_popcount(int n, int k, const function<void(int)>& f) {
    if (k < 0 || k > n) {
        return;
    }
    if (k == 0) {
        f(0);
        return;
    }
    int x = (1 << k) - 1;
    int lim = (1 << n);
    while (x < lim) {
        f(x);
        int c = x & -x;
        int r = x + c;
        x = (((r ^ x) >> 2) / c) | r;
    }
}
