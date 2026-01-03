template <typename T>
int longest_common_subsequence(const vector<T>& a, const vector<T>& b) {
    int n = (int) a.size();
    int m = (int) b.size();
    vector<int> dp(m + 1, 0);
    for (int i = 0; i < n; i++) {
        int prev = 0;
        for (int j = 0; j < m; j++) {
            int cur = dp[j + 1];
            if (a[i] == b[j]) {
                dp[j + 1] = prev + 1;
            } else {
                dp[j + 1] = max(dp[j + 1], dp[j]);
            }
            prev = cur;
        }
    }
    return dp[m];
}
