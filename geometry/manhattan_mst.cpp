using P64 = TPoint<int64_t>;

inline int64_t manhattan_dist(const P64& a, const P64& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

struct manhattan_edge {
    int a;
    int b;
    int64_t w;

    bool operator<(const manhattan_edge& other) const {
        return w < other.w;
    }
};

static inline P64 rot90(P64 p) {
    swap(p.x, p.y);
    p.x = -p.x;
    return p;
}

static inline void rot_all(vector<P64>& a) {
    for (auto& p : a) {
        p = rot90(p);
    }
}

static inline void swap_all(vector<P64>& a) {
    for (auto& p : a) {
        swap(p.x, p.y);
    }
}

vector<manhattan_edge> manhattan_mst_edges(vector<P64> a) {
    int n = (int) a.size();
    for (int i = 0; i < n; i++) {
        a[i].id = i;
    }

    vector<P64> buf(n);
    vector<P64> best(n);
    vector<P64> best_buf(n);

    auto yx_cmp = [&](const P64& x, const P64& y) {
        return (x.y < y.y || (x.y == y.y && x.x < y.x));
    };

    auto has_better = [&](const P64& x, const P64& y) {
        if (x.id < 0) {
            return false;
        }
        if (y.id < 0) {
            return true;
        }
        return x.x + x.y < y.x + y.y;
    };

    function<void(vector<P64>&, vector<P64>&, int, int)> solve =
    [&](vector<P64>& pts, vector<P64>& closest, int l, int r) {
        if (r - l <= 1) {
            return;
        }
        int m = (l + r) >> 1;
        solve(pts, closest, l, m);
        solve(pts, closest, m, r);

        int right = m;
        int k = 0;
        P64 mn;
        mn.id = -1;

        for (int i = l; i < m; i++) {
            while (right < r && pts[right].y - pts[right].x <= pts[i].y - pts[i].x) {
                buf[k] = pts[right];
                best_buf[k] = closest[right];
                if (has_better(pts[right], mn)) {
                    mn = pts[right];
                }
                k++;
                right++;
            }
            if (has_better(mn, closest[i])) {
                closest[i] = mn;
            }
            buf[k] = pts[i];
            best_buf[k] = closest[i];
            k++;
        }
        for (int i = 0; i < k; i++) {
            pts[l + i] = buf[i];
            closest[l + i] = best_buf[i];
        }
    };

    vector<manhattan_edge> edges;
    edges.reserve(8 * n);

    for (int rep = 0; rep < 4; rep++) {
        sort(a.begin(), a.end(), yx_cmp);
        for (int i = 0; i < n; i++) {
            best[i].id = -1;
            best[i].x = 0;
            best[i].y = 0;
        }

        solve(a, best, 0, n);

        for (int i = 0; i < n; i++) {
            if (best[i].id >= 0) {
                edges.push_back({a[i].id, best[i].id, manhattan_dist(a[i], best[i])});
            }
        }

        if (rep % 2 == 0) {
            swap_all(a);
        } else {
            rot_all(a);
        }
    }

    sort(edges.begin(), edges.end());
    dsu d(n);
    vector<manhattan_edge> mst;
    mst.reserve(n - 1);
    for (auto& e : edges) {
        if (d.unite(e.a, e.b)) {
            mst.push_back(e);
        }
    }
    return mst;
}
