struct trie {
    static const int A = 26;
    vector<array<int, A>> next;
    vector<int> term;

    trie() {
        next.push_back({});
        next[0].fill(-1);
        term.push_back(0);
    }

    int add(const string& s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (next[v][c] == -1) {
                next[v][c] = (int) next.size();
                next.push_back({});
                next.back().fill(-1);
                term.push_back(0);
            }
            v = next[v][c];
        }
        term[v]++;
        return v;
    }
};
