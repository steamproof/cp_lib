inline void iterate_supermasks(int m, int n, const function<void(int)>& f) {
    int all = (1 << n);
    for (int s = m; s < all; s = (s + 1) | m) {
        f(s);
    }
}
