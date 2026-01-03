template <typename T, typename U = int>
pair<vector<U>, vector<T>> compress_array(const vector<T>& a) {
    int n = (int) a.size();
    vector<pair<T, int>> b(n);
    for (int i = 0; i < n; i++) {
        b[i] = {a[i], i};
    }
    sort(b.begin(), b.end(), [&](const auto& x, const auto& y) {
        return x.first < y.first;
    });
    vector<U> id(n);
    vector<T> vals;
    vals.reserve(n);
    int cur = 0;
    for (int i = 0; i < n; ) {
        int j = i;
        while (j < n && b[j].first == b[i].first) {
            id[b[j].second] = (U) cur;
            j++;
        }
        vals.push_back(b[i].first);
        cur++;
        i = j;
    }
    return {id, vals};
}
