template <typename T, typename F>
long long count_pairs(vector<T>& a, F ok_pair) {
    int n = (int) a.size();
    vector<T> tmp(n);

    function<long long(int, int)> solve = [&](int l, int r) -> long long {
        if (r - l <= 1) {
            return 0;
        }
        int m = (l + r) >> 1;
        long long ans = solve(l, m) + solve(m, r);

        int i = l;
        for (int j = m; j < r; j++) {
            while (i < m && ok_pair(a[i], a[j])) {
                i++;
            }
            ans += i - l;
        }

        int p = l, q = m, t = l;
        while (p < m || q < r) {
            if (q == r || (p < m && a[p] <= a[q])) {
                tmp[t++] = a[p++];
            } else {
                tmp[t++] = a[q++];
            }
        }
        for (int k = l; k < r; k++) {
            a[k] = tmp[k];
        }
        return ans;
    };

    return solve(0, n);
}
