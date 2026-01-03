struct mo_query {
    int l;
    int r;
    int id;
};

inline vector<int> mo_order(int n, vector<mo_query> q) {
    int b = max(1, (int) sqrt(n));
    sort(q.begin(), q.end(), [&](const mo_query& a, const mo_query& bq) {
        int ba = a.l / b;
        int bb = bq.l / b;
        if (ba != bb) {
            return ba < bb;
        }
        if (ba & 1) {
            return a.r > bq.r;
        }
        return a.r < bq.r;
    });
    vector<int> ord;
    ord.reserve(q.size());
    for (auto& qq : q) {
        ord.push_back(qq.id);
    }
    return ord;
}
