vector<vector<int>> grid_bfs_dist(const vector<string>& a, int sr, int sc, char wall = '#') {
    int n = (int) a.size();
    int m = (int) a[0].size();
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int, int>> q;
    dist[sr][sc] = 0;
    q.push({sr, sc});
    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        for (int k = 0; k < 4; k++) {
            int nr = cur.first + dr[k];
            int nc = cur.second + dc[k];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) {
                continue;
            }
            if (a[nr][nc] == wall) {
                continue;
            }
            if (dist[nr][nc] != -1) {
                continue;
            }
            dist[nr][nc] = dist[cur.first][cur.second] + 1;
            q.push({nr, nc});
        }
    }
    return dist;
}
