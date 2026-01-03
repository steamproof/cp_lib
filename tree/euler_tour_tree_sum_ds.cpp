struct euler_tour {
    int n;
    vector<vector<int>> g;
    vector<int> tin;
    vector<int> tout;
    vector<int> order;
    int timer;

    euler_tour(int _n) : n(_n) {
        g.assign(n, {});
        tin.assign(n, -1);
        tout.assign(n, -1);
        timer = 0;
    }

    inline void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void build(int root = 0) {
        order.clear();
        order.reserve(n);
        timer = 0;
        function<void(int, int)> dfs = [&](int v, int p) {
            tin[v] = timer++;
            order.push_back(v);
            for (int to : g[v]) {
                if (to == p) {
                    continue;
                }
                dfs(to, v);
            }
            tout[v] = timer - 1;
        };
        dfs(root, -1);
    }
};
