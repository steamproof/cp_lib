class dsu_bipartite {
public:
    int n;
    vector<int> p;
    vector<int> sz;
    vector<int> xr;  // xor-to-parent (0/1)
    bool ok;

    dsu_bipartite(int _n) : n(_n), ok(true) {
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        sz.assign(n, 1);
        xr.assign(n, 0);
    }

    inline pair<int, int> get(int x) {
        if (x == p[x]) {
            return {x, 0};
        }
        auto r = get(p[x]);
        p[x] = r.first;
        xr[x] ^= r.second;
        return {p[x], xr[x]};
    }

    // add constraint: color(x) xor color(y) = w (w in {0,1})
    inline bool unite(int x, int y, int w) {
        auto rx = get(x);
        auto ry = get(y);
        int a = rx.first;
        int b = ry.first;
        int px = rx.second;
        int py = ry.second;
        if (a == b) {
            if ((px ^ py) != w) {
                ok = false;
                return false;
            }
            return true;
        }
        if (sz[a] < sz[b]) {
            swap(a, b);
            swap(px, py);
        }
        p[b] = a;
        sz[a] += sz[b];
        // want: (color(x) ^ px) == color(a), (color(y) ^ py) == color(b)
        // enforce: color(x) ^ color(y) = w
        // => (color(a) ^ px) ^ (color(b) ^ py) = w
        // => color(b) ^ color(a) = px ^ py ^ w
        xr[b] = px ^ py ^ w;
        return true;
    }

    inline bool is_ok() const {
        return ok;
    }

    inline int size(int x) {
        return sz[get(x).first];
    }

    inline int diff(int x, int y) {
        auto rx = get(x);
        auto ry = get(y);
        assert(rx.first == ry.first);
        return rx.second ^ ry.second;
    }
};
