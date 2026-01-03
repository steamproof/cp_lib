class upper_hull {
public:
    using coord_t = long long;

    map<coord_t, coord_t> pts;
    long long area;

    upper_hull() : area(0) {}

    inline int size() const {
        return (int) pts.size();
    }

    inline long long trapezoid_area(coord_t x1, coord_t y1, coord_t x2, coord_t y2) const {
        return (x2 - x1) * (y1 + y2);
    }

    inline long long triangle_area(coord_t x1, coord_t y1, coord_t x2, coord_t y2, coord_t x3, coord_t y3) const {
        return (x2 - x1) * (y2 - y3) - (y2 - y1) * (x2 - x3);
    }

    inline long long point_area(map<coord_t, coord_t>::iterator it) const {
        bool has_prev = (it != pts.begin());
        bool has_next = (next(it) != pts.end());
        if (has_prev && has_next) {
            auto a = *prev(it);
            auto b = *it;
            auto c = *next(it);
            return triangle_area(a.first, a.second, b.first, b.second, c.first, c.second);
        }
        long long s = 0;
        if (has_prev) {
            auto a = *prev(it);
            auto b = *it;
            s += trapezoid_area(a.first, a.second, b.first, b.second);
        }
        if (has_next) {
            auto a = *it;
            auto b = *next(it);
            s += trapezoid_area(a.first, a.second, b.first, b.second);
        }
        return s;
    }

    inline bool bad(map<coord_t, coord_t>::iterator it) const {
        if (it == pts.begin() || it == pts.end() || next(it) == pts.end()) {
            return false;
        }
        return point_area(it) <= 0;
    }

    inline void erase_it(map<coord_t, coord_t>::iterator it) {
        area -= point_area(it);
        pts.erase(it);
    }

    bool insert(coord_t x, coord_t y) {
        auto f = pts.find(x);
        if (f != pts.end()) {
            if (y <= f->second) {
                return false;
            }
            erase_it(f);
        }
        auto it = pts.insert({x, y}).first;
        if (bad(it)) {
            pts.erase(it);
            return false;
        }
        area += point_area(it);
        while (it != pts.begin() && bad(prev(it))) {
            erase_it(prev(it));
        }
        while (bad(next(it))) {
            erase_it(next(it));
        }
        return true;
    }

    // 1 inside, 0 border, -1 outside
    int contains(coord_t x, coord_t y) const {
        if (pts.empty()) {
            return -1;
        }
        auto first = pts.begin();
        auto last = prev(pts.end());
        if (x < first->first || x > last->first) {
            return -1;
        }
        if (x == first->first) {
            return (y <= first->second ? 0 : -1);
        }
        if (x == last->first) {
            return (y <= last->second ? 0 : -1);
        }
        auto it = pts.lower_bound(x);
        auto a = *prev(it);
        auto b = *it;
        long long t = triangle_area(a.first, a.second, x, y, b.first, b.second);
        if (t == 0) {
            return 0;
        }
        return (t < 0 ? 1 : -1);
    }
};

class online_hull {
public:
    upper_hull up;
    upper_hull down;

    inline long long area_doubled() const {
        return up.area + down.area;
    }

    inline bool insert(long long x, long long y) {
        bool a = up.insert(x, y);
        bool b = down.insert(x, -y);
        return a || b;
    }

    inline int contains(long long x, long long y) const {
        return min(up.contains(x, y), down.contains(x, -y));
    }
};
