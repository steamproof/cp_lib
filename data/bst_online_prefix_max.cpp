template <typename K, typename V, bool is_max = true>
class online_prefix_opt {
public:
    map<K, V> best;
    V neutral;

    online_prefix_opt(V neutral_) : neutral(neutral_) {}

    inline int size() const {
        return (int) best.size();
    }

    inline bool better(const V& a, const V& b) const {
        return (is_max ? b < a : a < b);
    }

    // best value among keys < key_limit
    inline V query(const K& key_limit) const {
        auto it = best.lower_bound(key_limit);
        if (it == best.begin()) {
            return neutral;
        }
        return prev(it)->second;
    }

    inline void insert(const K& key, const V& val) {
        auto it = best.upper_bound(key);
        if (it != best.begin() && !better(val, prev(it)->second)) {
            return;
        }
        if (it != best.begin() && prev(it)->first == key) {
            best.erase(prev(it));
        }
        while (it != best.end() && !better(it->second, val)) {
            it = best.erase(it);
        }
        best.insert(it, {key, val});
    }
};
