pair<long long, vector<int>> max_weight_closure(
const vector<long long>& w,
const vector<pair<int, int>>& edges) {

    int n = (int) w.size();
    int s = n;
    int t = n + 1;
    long long sum_pos = 0;
    long long inf = 1;
    for (int i = 0; i < n; i++) {
        inf += abs(w[i]);
        if (w[i] > 0) {
            sum_pos += w[i];
        }
    }
    inf *= 2;

    flow_graph<long long> g(n + 2, s, t);
    for (int i = 0; i < n; i++) {
        if (w[i] > 0) {
            g.add(s, i, w[i], 0);
        } else if (w[i] < 0) {
            g.add(i, t, -w[i], 0);
        }
    }
    for (auto e : edges) {
        g.add(e.first, e.second, inf, 0);
    }

    dinic<long long> d(g);
    d.max_flow();

    vector<int> q(n + 2);
    vector<int> vis(n + 2, 0);
    int beg = 0, end = 0;
    q[end++] = s;
    vis[s] = 1;
    while (beg < end) {
        int v = q[beg++];
        for (int id : g.g[v]) {
            auto& e = g.edges[id];
            if (!vis[e.to] && e.c - e.f > 0) {
                vis[e.to] = 1;
                q[end++] = e.to;
            }
        }
    }

    vector<int> take;
    for (int i = 0; i < n; i++) {
        if (vis[i]) {
            take.push_back(i);
        }
    }
    long long best = sum_pos - g.flow;
    return {best, take};
}
