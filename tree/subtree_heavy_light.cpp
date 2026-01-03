struct heavy_light {
    int n;
    vector<vector<int>> g;
    vector<int> p;
    vector<int> dep;
    vector<int> sz;
    vector<int> heavy;
    vector<int> head;
    vector<int> pos;
    int timer;

    heavy_light(int _n) : n(_n) {
        g.assign(n, {});
        p.assign(n, -1);
        dep.assign(n, 0);
        sz.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, 0);
        pos.assign(n, 0);
        timer = 0;
    }

    inline void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int dfs1(int v, int par) {
        p[v] = par;
        sz[v] = 1;
        int best = 0;
        for (int to : g[v]) {
            if (to == par) {
                continue;
            }
            dep[to] = dep[v] + 1;
            int got = dfs1(to, v);
            sz[v] += got;
            if (got > best) {
                best = got;
                heavy[v] = to;
            }
        }
        return sz[v];
    }

    void dfs2(int v, int h) {
        head[v] = h;
        pos[v] = timer++;
        if (heavy[v] != -1) {
            dfs2(heavy[v], h);
        }
        for (int to : g[v]) {
            if (to == p[v] || to == heavy[v]) {
                continue;
            }
            dfs2(to, to);
        }
    }

    void build(int root = 0) {
        timer = 0;
        dfs1(root, -1);
        dfs2(root, root);
    }

    inline int lca(int a, int b) const {
        while (head[a] != head[b]) {
            if (dep[head[a]] > dep[head[b]]) {
                a = p[head[a]];
            } else {
                b = p[head[b]];
            }
        }
        return dep[a] < dep[b] ? a : b;
    }

    // split path (u -> v) into O(log n) segments [l, r] in the base array.
    vector<pair<int, int>> get_path(int u, int v) const {
        vector<pair<int, int>> segs;
        while (head[u] != head[v]) {
            if (dep[head[u]] >= dep[head[v]]) {
                segs.push_back({pos[head[u]], pos[u]});
                u = p[head[u]];
            } else {
                segs.push_back({pos[head[v]], pos[v]});
                v = p[head[v]];
            }
        }
        int l = pos[u];
        int r = pos[v];
        if (l > r) {
            swap(l, r);
        }
        segs.push_back({l, r});
        return segs;
    }

    inline pair<int, int> get_subtree(int v) const {
        return {pos[v], pos[v] + sz[v] - 1};
    }
};
