pair<bool, vector<int>> check_bipartite(const vector<vector<int>>& g) {
    int n = (int) g.size();
    vector<int> col(n, -1);
    queue<int> q;
    for (int s = 0; s < n; s++) {
        if (col[s] != -1) {
            continue;
        }
        col[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int to : g[v]) {
                if (col[to] == -1) {
                    col[to] = col[v] ^ 1;
                    q.push(to);
                } else {
                    if (col[to] == col[v]) {
                        return {false, {}};
                    }
                }
            }
        }
    }
    return {true, col};
}
