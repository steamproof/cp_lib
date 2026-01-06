template <typename T>
vector<int> bfs_dist(const undigraph<T> &g, int s) {
    int n = g.n;
    vector<int> dist(n, -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int i = q.front();
        q.pop();
        for (int id : g.g[v]) {
            const auto &e = g.edges[id];
            int to = e.from ^ e.to ^ i;
            if (dist[to] == -1) {
                dist[to] = dist[v] + 1;
                q.push(to);
            }
        }
    }
    return dist;
}
