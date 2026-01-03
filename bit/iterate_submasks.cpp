inline void iterate_submasks(int m, const function<void(int)>& f) {
    for (int s = m; ; s = (s - 1) & m) {
        f(s);
        if (s == 0) {
            break;
        }
    }
}
