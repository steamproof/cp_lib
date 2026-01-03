template <typename T>
long long count_distinct_subsequences(const vector<T>& a) {
    int n = (int) a.size();
    vector<long long> dp(n + 1, 0);
    dp[0] = 1;
    unordered_map<T, int> last;
    for (int i = 0; i < n; i++) {
        dp[i + 1] = 2 * dp[i];
        auto it = last.find(a[i]);
        if (it != last.end()) {
            dp[i + 1] -= dp[it->second];
        }
        last[a[i]] = i;
    }
    return dp[n];
}
