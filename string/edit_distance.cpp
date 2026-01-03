template <typename T>
int edit_distance(const vector<T>& a, const vector<T>& b) {
    int n = (int) a.size();
    int m = (int) b.size();
    vector<int> dp(m + 1);
    for (int j = 0; j <= m; j++) {
        dp[j] = j;
    }
    for (int i = 0; i < n; i++) {
        int prev = dp[0];
        dp[0] = i + 1;
        for (int j = 0; j < m; j++) {
            int cur = dp[j + 1];
            int cost = (a[i] == b[j] ? 0 : 1);
            dp[j + 1] = min({dp[j + 1] + 1, dp[j] + 1, prev + cost});
            prev = cur;
        }
    }
    return dp[m];
}
