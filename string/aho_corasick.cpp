struct aho_corasick {
    static const int A = 26;

    struct node {
        array<int, A> next;
        int link;
        int out;

        node() : link(-1), out(0) {
            next.fill(-1);
        }
    };

    vector<node> t;

    aho_corasick() {
        t.push_back(node());
        t[0].link = 0;
    }

    int add(const string& s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (t[v].next[c] == -1) {
                t[v].next[c] = (int) t.size();
                t.push_back(node());
            }
            v = t[v].next[c];
        }
        t[v].out++;
        return v;
    }

    void build() {
        queue<int> q;
        for (int c = 0; c < A; c++) {
            int u = t[0].next[c];
            if (u == -1) {
                t[0].next[c] = 0;
            } else {
                t[u].link = 0;
                q.push(u);
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            int p = t[v].link;
            t[v].out += t[p].out;
            for (int c = 0; c < A; c++) {
                int u = t[v].next[c];
                if (u == -1) {
                    t[v].next[c] = t[p].next[c];
                } else {
                    t[u].link = t[p].next[c];
                    q.push(u);
                }
            }
        }
    }

    inline int step(int v, char ch) const {
        return t[v].next[ch - 'a'];
    }

    inline int match_count(int v) const {
        return t[v].out;
    }
};
