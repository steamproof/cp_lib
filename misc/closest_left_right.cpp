template <typename T, typename F>
vector<int> closest_left(const vector<T>& a, F cmp) {
    int n = (int) a.size();
    vector<int> res(n);
    vector<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && !cmp(a[st.back()], a[i])) {
            st.pop_back();
        }
        res[i] = (st.empty() ? -1 : st.back());
        st.push_back(i);
    }
    return res;
}

template <typename T, typename F>
vector<int> closest_right(const vector<T>& a, F cmp) {
    int n = (int) a.size();
    vector<int> res(n);
    vector<int> st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && !cmp(a[st.back()], a[i])) {
            st.pop_back();
        }
        res[i] = (st.empty() ? n : st.back());
        st.push_back(i);
    }
    return res;
}
